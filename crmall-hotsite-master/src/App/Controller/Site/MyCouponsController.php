<?php

namespace App\Controller\Site;

use App\Services\CampaignService;
use App\Util\Csv;
use App\Util\StringUtil;
use BaseUnicaLib\Modules\Cnpj\Cnpj;
use BaseUnicaLib\Modules\Cnpj\CnpjModel;
use Crmall4Lib\Modules\Lottery\Lottery;
use Crmall4Lib\Modules\Lottery\LotteryNumberQtdModel;
use Crmall4Lib\Modules\Store\Store;
use Silex\Application;
use Symfony\Component\HttpFoundation\RedirectResponse;
use Symfony\Component\HttpFoundation\Response;

class MyCouponsController extends BaseController
{
    public function routes()
    {
        $this->route->get('/notas-enviadas', [$this, 'receiptAction']);
        $this->route->get('/cadastrar', [$this, 'newCouponAction']);
        $this->route->post('/send-invoice', [$this, 'sendInvoiceAction']);
        $this->route->get('/get-stores', [$this, 'getStoresAction']);
        $this->route->post('/date-campaign-interval', [$this, 'dateCampaignIntervalAction']);
        $this->route->get('/get-sent-image/{imageId}', [$this, 'getSentImageAction']);
        $this->route->get('/{qtd}/{page}', [$this, 'indexAction'])->value('qtd', 45)->value('page', 1);
    }

    public function indexAction($qtd, $page)
    {
        if (!$this->app['user']) {
            return  $this->app->redirect('/user/login');
        }

        $user = $this->app['user'];

        $document = StringUtil::numbersOnly($user->documentNumber);
        $numbers = $this->app[Lottery::class]->serviceGet("benefits/coupon/{$document}/{$this->app['crmall4CouponCampaign']}");

        $data = [];

        foreach ($numbers as $row) {
            if (!$row['isCanceled']) {
                $data[] = $row;
            }
        }

        $return = $this->fakePagination($data, $qtd, $page);

        if ($this->request->isXmlHttpRequest()) {
            return $this->json($return);
        }

        return $this->render('meus-cupons.twig', ['numbers' => $return]);
    }

    public function getSentImageAction($imageId)
    {
        $image = $this->app[CampaignService::class]->getImage($imageId);

        $f = finfo_open();
        $mimeType = finfo_buffer($f, $image, FILEINFO_MIME_TYPE);

        $response = new Response();
        $response->headers->set('Content-type', $mimeType);
        $response->setContent($image);

        return $response;
    }

    public function receiptAction()
    {
        $user = $this->app['user'];

        if (!$user) {
            return  $this->app->redirect('/user/login');
        }

        $receipts = $this->app[CampaignService::class]->getDocuments($user->getDocumentNumber(), $this->app['campaignBegins']);

        return $this->render('receipts.twig', [
            'receipts' => $receipts,
            'user' => $user->toArray()
        ]);
    }

    public function dateCampaignIntervalAction()
    {
        $date = date_create_from_format('d/m/Y', $this->request->get('date'));

        return $this->app->json((bool)($date < $this->app['generalCampaign']['campaignBegins'] || $date > $this->app['generalCampaign']['campaignEnds']));
    }

    public function newCouponAction()
    {
        if ($this->app['campaignFinished']) {
            return $this->app->redirect('/');
        }

        if (!$this->app['user']) {
            return  $this->app->redirect('/user/login');
        }

        return $this->render('novo-cupom.twig');
    }

    public function sendInvoiceAction()
    {
        try {
            $user = $this->app['user'];

            if ($this->app['campaignFinished'] || !$user) {
                return $this->json(false);
            }

            $invoice = $this->request->request->all();
            $invoice['documentNumber'] = $user->documentNumber;
            $invoice['image'] = $this->request->files->get('image');
            $invoice['newImage'] = $this->request->files->get('newImage');

            if ($invoice['newImage']) {
                $invoice['image'] = $invoice['newImage'];
            }

            try {
                $this->app[Store::class]->getByDocument($invoice['storeDocumentNumber']);
            } catch (\Exception $e) {
                $store = $this->getStoreInBaseUnica($invoice['storeDocumentNumber']);

                if (!$store) {
                    $store = [
                        'documentNumber' => StringUtil::numbersOnly($invoice['storeDocumentNumber']),
                        'tradeName' => $invoice['storeName'],
                        'name' => $invoice['storeName']
                    ];
                }

                $this->app[CampaignService::class]->saveStore($store);
            }

            $this->app[CampaignService::class]->sendDocument($invoice);

            return $this->json(true, 200);
        } catch (\Exception $e) {
            logger($e->getMessage(), 'teste-error');
            return $this->json(false, 400);
        }
    }

    public function getStoreInBaseUnica($document)
    {
        try {
            /** @var CnpjModel $storeInBaseUnica */
            $storeInBaseUnica = $this->app[Cnpj::class]->consult($document);

            $store = [
                'documentNumber' => StringUtil::numbersOnly($document),
                'name' => $storeInBaseUnica->getCompany(),
                'tradeName' => $storeInBaseUnica->getTrade(),
                'zipcode' => $storeInBaseUnica->getZipcode(),
                'addressNumber' => $storeInBaseUnica->getAddressNumber(),
                'city' => $storeInBaseUnica->getCity(),
                'complement' => $storeInBaseUnica->getComplement(),
                'neighborhood' => $storeInBaseUnica->getNeighborhood(),
                'address' => $storeInBaseUnica->getAddress(),
                'situation' => $storeInBaseUnica->getSituation(),
                'uf' => $storeInBaseUnica->getUf(),
            ];

            return $store;
        } catch (\Exception $e) {
            return false;
        }
    }

    public function getStoresAction()
    {
        if ($this->app['campaignFinished'] || !$this->app['user']) {
            return $this->json([]);
        }

        $result = $this->getStoresFromCrmall();
//        $result = $this->getStoresFromCsv();

        return $this->json($result);
    }

    private function getStoresFromCrmall()
    {
        $storesService = new Store();

        $stores = $storesService
            ->enableCache('stores')
            ->addFilter("(DocumentNumber ne null)")
            ->orderBy('tradeNameClean')
            ->setCacheExpiration(3600)
            ->getAll();

        $result = [];

        foreach ($stores as $store) {
            $result[] = [
                'id' => $store->getDocumentNumber(),
                'text' => StringUtil::mask($store->getDocumentNumber(), '##.###.###/####-##') . ' - ' . $store->getName() . ' - ' . $store->getTradeName()
            ];
        }

        return $result;
    }

    private function getStoresFromCsv()
    {
        $stores = \App\Util\Csv::read("files/stores.csv");

        usort($stores, function ($a, $b) {
            return trim($a[1]) <=> trim($b[1]);
        });

        $result = [];

        foreach ($stores as $store) {
            $documentNumber = StringUtil::numbersOnly($store[0]);

            if (!isset($result[$documentNumber]) && strlen($documentNumber) == 14) {
                $result[$documentNumber] = [
                    'id' => $documentNumber,
                    'text' => StringUtil::mask($documentNumber, '##.###.###/####-##') . ' - ' . trim($store[1]) . ' - ' . trim($store[2])
                ];
            }
        }

        return array_values($result);
    }
}
