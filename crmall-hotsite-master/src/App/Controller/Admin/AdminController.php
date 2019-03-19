<?php

namespace App\Controller\Admin;

use App\Services\CampaignService;
use App\Util\Csv;
use App\Util\StringUtil;
use Crmall4Lib\Modules\Lottery\Lottery;
use Silex\Api\ControllerProviderInterface;
use Silex\Application;
use Symfony\Component\HttpFoundation\RedirectResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpFoundation\Session\Session;

class AdminController implements ControllerProviderInterface
{
    /** @var $app Application */
    protected $app;

    /** @var \Silex\ControllerCollection  */
    protected $route;

    /** @var Request */
    protected $request;

    public function __construct(Application $app)
    {
        $this->app = $app;
        $this->app['admin'] = null;

        /** @var Session $session */
        $session = $app['session'];
        $loggedAdmin = $session->get('loggedAdmin', false);

        if ($session && $loggedAdmin) {
            $this->app['admin'] = $loggedAdmin;
        }
    }

    public function connect(Application $app)
    {
        $this->route = $app['controllers_factory'];
        $this->route->before(function (Request $request) {
            $this->request = $request;
        });

        $this->routes();

        return $this->route;
    }

    public function routes()
    {
        $this->route->get('/', array($this, 'indexAction'));
        $this->route->match('/login', array($this, 'loginAction'));
        $this->route->get('/logout', array($this, 'logoutAction'));

        $this->route->get('/ganhadores/{campaignSelected}/{winnerIndex}', array($this, 'winnersAction'))
            ->value('winnerIndex', null)
            ->value('campaignSelected', null);
        $this->route->post('/adicionar-ganhador', array($this, 'addWinnerAction'));
        $this->route->post('/remover-ganhador', array($this, 'removeWinnerAction'));

        $this->route->get('/notas-por-sorteio', [$this, 'receiptsByLuckyNumberAction']);
        $this->route->get('/find-receipts/{campaign}/{documentNumber}', [$this, 'findReceiptsAction']);

        $this->route->get('/export/{campaign}/{documentNumber}', [$this, 'exportReceiptsAction']);
    }

    public function indexAction()
    {
        return $this->app->redirect('/adm/login');
    }

    public function loginAction()
    {
        if ($this->app['admin']) {
            return $this->app->redirect('/adm/ganhadores');
        }

        if ($this->request->isMethod('post')) {
            $username = $this->request->get('_username');
            $password = $this->request->get('_password');

            if (empty($username) || empty($password)) {
                return $this->app['twig']->render('admin/login.twig', ['login_error' => 'Os campos usuário e senha são obrigatórios.']);
            }

            if ($username === $this->app['adminUser'] &&
                $password === $this->app['adminPassword']) {
                $this->app['admin'] = [
                    'admin' => true
                ];

                $this->request->getSession()->invalidate();
                $this->request->getSession()->clear();
                $this->request->getSession()->start();

                $this->request->getSession()->set('loggedAdmin', $this->app['admin']);

                return  $this->app->redirect('/adm/ganhadores');
            } else {
                return $this->app['twig']->render('admin/login.twig', ['login_error' => 'Usuário e/ou senha inválidos!']);
            }
        }

        return $this->app['twig']->render('admin/login.twig');
    }

    public function logoutAction()
    {
        if (!$this->app['admin']) {
            return  $this->app->redirect('/adm/login');
        }

        $this->request->getSession()->invalidate();
        $this->request->getSession()->clear();
        $this->request->getSession()->start();

        $this->request->getSession()->remove('loggedAdmin');
        $this->app['admin'] = null;

        return  $this->app->redirect('/adm/login');
    }

    public function findReceiptsAction($campaign, $documentNumber)
    {
        return $this->app->json($this->getReceiptsByDocument($campaign, $documentNumber), 200);
    }

    public function exportReceiptsAction($campaign, $documentNumber)
    {
        $data = $this->getReceiptsByDocument($campaign, $documentNumber);

        $header = [
            'CNPJ da loja',
            'Valor da nota',
            'Data da compra',
            'Número da nota',
            'Data de envio',
            'Detalhes da nota'
        ];

        if ($this->app['campaignType'] !== 'withCrm') {
            array_unshift($header, 'Numero da sorte');
        }

        $response = new Response(Csv::createCsv($data['data'], $header));
        $response->headers->set('Content-Type', 'text/csv;charset=UTF-8');
        $response->headers->set('Content-Disposition', 'filename="' . $campaign . '-' . StringUtil::numbersOnly($documentNumber) .'.csv"');

//        echo "\xEF\xBB\xBF";

        return $response;
    }

    public function receiptsByLuckyNumberAction()
    {
        if (!$this->app['admin']) {
            return  $this->app->redirect('/adm/login');
        }

        $campaigns = [];

        foreach ($this->app['lotteryCampaigns'] as $campaign) {
            $campaigns[$campaign['id']] = $campaign['prize'] . ' | ' . $campaign['campaignBegins']->format('d/m/Y') . ' - ' . $campaign['campaignEnds']->format('d/m/Y');
        }

        $campaigns[$this->app['generalCampaign']['id']] = $this->app['generalCampaign']['prize'] . ' | ' . $this->app['generalCampaign']['campaignBegins']->format('d/m/Y') . ' - ' . $this->app['generalCampaign']['campaignEnds']->format('d/m/Y');

        return $this->app['twig']->render('admin/audit-winners.twig', [
            'campaigns' => $campaigns
        ]);
    }

    public function winnersAction($campaignSelected, $winnerIndex)
    {
        if (!$this->app['admin']) {
            return  $this->app->redirect('/adm/login');
        }

        $winners = [];
        $now = new \DateTime("now");
        $winnerIndexToHighlight = -1;

        $tableStructure = Csv::read("files/ganhadores/estrutura-tabela.csv")[0];

        foreach ($this->app['lotteryCampaigns'] as $campaign) {
            $current = ($now >= $campaign['campaignBegins'] && $now <= $campaign['campaignEnds']);
            if (!$campaignSelected && $current) {
                $campaignSelected = (int)$campaign['id'];
            }

            $winnersTable = Csv::read("files/ganhadores/ganhadores-{$campaign['id']}.csv");

            $winnersTable = array_map(function ($row) use ($tableStructure) {
                $sizeRow = sizeof($row);
                $sizeStructure = sizeof($tableStructure);

                if ($sizeRow < $sizeStructure) {
                    $row = $row + array_fill($sizeRow, $sizeStructure - $sizeRow, '');
                }

                return $row;
            }, $winnersTable);

            $winners[$campaign['id']] = array_merge($campaign, [
                'current' => $current,
                'generalCampaign' => false,
                'table' => $winnersTable
            ]);
        }

        $winners[$this->app['generalCampaign']['id']] = array_merge($this->app['generalCampaign'], [
            'current' => false,
            'generalCampaign' => true,
            'table' => Csv::read("files/ganhadores/ganhadores-{$this->app['generalCampaign']['id']}.csv")
        ]);

        if (isset($winnerIndex)) {
            $winnerIndexToHighlight = $winnerIndex - 1;
        }

        return $this->app['twig']->render('admin/manage-winners.twig', [
            'winners' => $winners,
            'tableStructure' => $tableStructure,
            'winnerIndexToHighlight' => (int)$winnerIndexToHighlight,
            'campaignSelected' => $campaignSelected,
        ]);
    }

    public function addWinnerAction()
    {
        try {
            $post = $this->request->request->all();
            $index = $post['lineIndex'] ?? null;
            $campaignId = $post['campaignId'];
            unset($post['lineIndex']);
            unset($post['campaignId']);

            $post = array_map(function ($row) {
                return trim($row);
            }, $post);

            $dataToInsert = "";
            foreach ($post as $param) {
                $dataToInsert .= $param.",";
            }
            $dataToInsert = substr($dataToInsert, 0, -1);

            $fileName = PATH_PUBLIC."/files/ganhadores/ganhadores-{$campaignId}.csv";

            $arrLines = $this->removeBreakLines(file($fileName));

            if ($index !== null) {
                $positionToInsert = (int)$index - 1;
                $result = $this->arrayInsert($arrLines, $positionToInsert, $dataToInsert);
                $resultStr = implode("\n", $result);
                file_put_contents($fileName, $resultStr);
            } else {
                $index = sizeof($arrLines) + 1;
                $dataToInsert = $index !== 1 ? "\n" . $dataToInsert : $dataToInsert;

                file_put_contents($fileName, $dataToInsert, FILE_APPEND);
            }

            return $this->app->json(['cod' => 200, 'success' => true, 'index' => $index, 'campaignId' => $campaignId], 200);
        } catch (\Throwable $t) {
            return $this->app->json(['cod' => $t->getCode(), 'success' => false, 'message' => 'Ocorreu um erro ao adicionar o ganhador. Tente novamente.'], $t->getCode());
        }
    }

    public function removeWinnerAction()
    {
        try {
            $post = $this->request->request->all();

            $index = $post['lineIndex'] ?? null;
            $campaignId = $post['campaignId'];
            unset($post['lineIndex']);
            unset($post['campaignId']);

            $fileName = PATH_PUBLIC."/files/ganhadores/ganhadores-{$campaignId}.csv";
            $fileArray = file($fileName);
            unset($fileArray[$index - 1]);

            $arrLines = $this->removeBreakLines($fileArray);
            $resultStr = implode("\n", $arrLines);

            file_put_contents($fileName, $resultStr);

            return $this->app->json(['cod' => 200, 'success' => true, 'index' => $index, 'campaignId' => $campaignId], 200);
        } catch (\Throwable $t) {
            return $this->app->json(['cod' => $t->getCode(), 'success' => false, 'message' => 'Ocorreu um erro ao remover o ganhador. Tente novamente.'], $t->getCode());
        }
    }

    private function getReceiptsByDocument($campaign, $documentNumber)
    {
        if (!$this->app['admin']) {
            return $this->app->json([], 406);
        }

        $return = [
            'type' => $this->app['campaignType'],
            'data' => []
        ];

        if ($this->app['campaignType'] == 'withCrm') {
            $receipts = $this->app[CampaignService::class]->getDocuments($documentNumber, $this->app['campaignBegins']);

            foreach ($receipts as $receipt) {
                $return['data'][] = [
                    'storeDocument' => $receipt->storeDocument,
                    'invoiceValue' => $receipt->value,
                    'invoicePurchasedDate' => $receipt->purchaseDate,
                    'invoiceNumber' => $receipt->number,
                    'sentDate' => $receipt->created,
                    'message' => $receipt->message?$receipt->message:''
                ];
            }
        } else {
            /** @var Lottery $service */
            $service = $this->app[Lottery::class];
            $data = [
                'personDocument' => StringUtil::numbersOnly($documentNumber)
            ];

            $invoices = $service->serviceGet("campaign/lottery/{$campaign}/transactioninfo", $data);

            usort($invoices, function ($a, $b) {
                return (new \DateTime($b['createdDateTime'])) <=> (new \DateTime($a['createdDateTime']));
            });

            foreach ($invoices as &$invoice) {
                $value = $invoice['invoiceValue'];

                if (strlen($value) >= 3) {
                    $value = $value / 100;
                }

                $products = '';

                foreach (json_decode($invoice['extraInfo'], true) as $code => $item) {
                    $products .= $item['name'] .' (' . $item['quantity']  . ')<br>';
                }

                $invoice = [
                    'luckyNumber' => $invoice['luckNumber'],
                    'storeDocument' => StringUtil::mask($invoice['storeDocument'], '##.###.###/####-##'),
                    'invoiceValue' => $value,
                    'invoicePurchasedDate' => (new \DateTime($invoice['invoicePurchasedDate']))->format('d/m/Y'),
                    'invoiceNumber' => $invoice['invoiceNumber'],
                    'sentDate' => (new \DateTime($invoice['createdDateTime']))->format('d/m/Y'),
                    'message' => $products
                ];
            }

            $return['data'] = $invoices;
        }

        return $return;
    }

    private function arrayInsert($array, $pos, $val)
    {
        $array2 = array_splice($array, $pos);
        $array[] = $val;
        $array = array_merge($array, $array2);

        return $array;
    }

    private function removeBreakLines($array)
    {
        foreach ($array as &$item) {
            $item = preg_replace('/\n/', '', $item);
        }

        return $array;
    }
}
