<?php

namespace App\Controller\Site;

use Crmall4Lib\Config;
use Crmall4Lib\Modules\Base\Enum\EnumAccessEnvironment;
use Crmall4Lib\Modules\Person\Person;
use Crmall4Lib\Modules\User\User;
use Crmall4Lib\Service;
use GuzzleHttp\Client;
use Silex\Api\ControllerProviderInterface;
use Silex\Application;
use Crmall4Lib\Service as Crmall4LibService;
use Symfony\Component\HttpFoundation\Request;

abstract class BaseController implements ControllerProviderInterface
{
    /** @var $app Application */
    protected $app;

    /** @var \Silex\ControllerCollection  */
    protected $route;

    /** @var Request */
    protected $request;

    public function connect(Application $app)
    {
        $this->app = $app;

        $this->route = $app['controllers_factory'];
        $this->route->before(function (Request $request) {
            $this->request = $request;
        });

        $this->routes();

        return $this->route;
    }

    abstract public function routes();

    public function render($file, $data = [])
    {
        return $this->app['twig']->render('site/' . $file, $data);
    }

    protected function getCrmallUser($username, $password, $environment = EnumAccessEnvironment::CUSTOMER)
    {
        $config = $this->getBaseCrmallConfig();

        try {
            $config->userName = $username;
            $config->password = $password;
            $config->environment = $environment;

            Crmall4LibService::destroyInstance();

            $token = Crmall4LibService::initService($config, true);

            $userService = $this->app[User::class];
            $user = $userService->getLoggedUser();
            $user->token = $token->getToken();

            return $user;
        } catch (\Throwable $t) {
            $config->userName = null;
            $config->password = null;
            $config->environment = null;

            Crmall4LibService::initService($config);

            throw $t;
        }
    }

    protected function checkLoggedUserCrmall()
    {
        try {
            $userCrmall = $this->app[User::class];
            $userCrmall->getLoggedUser();
        } catch (\Throwable $t) {
            $this->clearSession();
            $this->app['session']->getFlashBag()->add('error', 'É necessário efetuar o login para editar as informações de cadastro.');
        }
    }

    public function json($data, $cod = 200, $message = '')
    {
        return $this->app->json(['cod' => $cod, 'message' => $message, 'data' => $data], $cod);
    }

    public function sendEmail($subject, $to, $from, $body)
    {
        if (!empty($to) && !empty($from)) {
            return $this->sendWithSwift($subject, $to, $from, $body);
        }

        return 0;
    }

    private function sendWithSwift($subject, $to, $from, $body)
    {
        $config = $this->app['mail'];

        $message = \Swift_Message::newInstance()
            ->setSubject($subject)
            ->setFrom($from)
            ->setTo($to)
            ->setBody($body, 'text/html');

        $context = [
            'ssl' => [
                'verify_peer' => false,
                'verify_peer_name' => false,
                'allow_self_signed' => true
            ]
        ];

        $transport = \Swift_SmtpTransport::newInstance($config['host'], $config['port'], $config['crypt'])
            ->setUsername($config['username'])
            ->setPassword($config['password'])
            ->setStreamOptions($context);

        $mailer = \Swift_Mailer::newInstance($transport);

        return $mailer->send($message);
    }

    public function mask($val, $mask)
    {
        $withMask = '';
        $k = 0;
        for ($i = 0; $i <= strlen($mask) - 1; ++$i) {
            if ($mask[$i] == '#') {
                if (isset($val[$k])) {
                    $withMask .= $val[$k++];
                }
            } else {
                if (isset($mask[$i])) {
                    $withMask .= $mask[$i];
                }
            }
        }

        return $withMask;
    }

    protected function clearSession()
    {
        Service::destroyInstance();

        $this->request->getSession()->start();
        $this->request->getSession()->remove($this->app['userSession']);
        $this->app['user'] = null;
    }

    protected function validateCaptcha($captchaResponse)
    {
        $client = new Client();
        $params = [
            'form_params' => [
                'secret' => $this->app['recaptcha']['secret'],
                'response' => $captchaResponse
            ]
        ];
        $response = $client->post($this->app['recaptcha']['url'], $params);

        $response = json_decode($response->getBody()->getContents());

        return $response->success;
    }

    /** @return Config */
    protected function getBaseCrmallConfig()
    {
        $config = new Config();

        $config->urlService = $this->app['crmall4Url'];
        $config->apiKey = $this->app['crmall4Key'];
        $config->cacheOptions = ['cacheDir' => $this->app['crmall4Cache']];
        $config->useSession = true;

        return $config;
    }

    protected function getRelations($documentNumber)
    {
        return $this->app[Person::class]->getRelations($documentNumber, $this->app['companyRelation']);
    }

    protected function fakePagination($data, $qtd = 50, $page = 1)
    {
        usort($data, function ($a, $b) {
            $dateStart = new \DateTime($a['createdDateTime']);
            $dateEnd = new \DateTime($b['createdDateTime']);

            return $dateEnd <=> $dateStart;
        });

        $dataSize = count($data);

        if ($page <= 0) {
            $page = 1;
        }

        $pieces = array_chunk($data, $qtd);

        if ($page > count($pieces)) {
            $page = count($pieces);
        }

        $paginator['total'] = $dataSize;
        $paginator['lastPage'] = count($pieces) == 0 ? 1 : count($pieces);
        $paginator['currentPage'] = (int) $page == 0 ? 1 : (int) $page;
        $paginator['limit'] = (int) $qtd;
        $paginator['data'] = empty($pieces) ? [] : $pieces[$page - 1];

        return $paginator;
    }
}
