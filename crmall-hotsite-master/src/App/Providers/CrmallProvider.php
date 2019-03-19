<?php

namespace App\Providers;

use Crmall4Lib\Config;
use Crmall4Lib\Modules\Lottery\Lottery;
use Crmall4Lib\Modules\Person\Person;
use Crmall4Lib\Modules\Store\Store;
use Crmall4Lib\Modules\Survey\Survey;
use Crmall4Lib\Modules\User\User;
use Crmall4Lib\Service;
use Pimple\Container;
use Pimple\ServiceProviderInterface;
use Symfony\Component\HttpFoundation\Session\Session;

class CrmallProvider implements ServiceProviderInterface
{
    public function register(Container $app)
    {
        try {
            $config = new Config();

            $config->urlService = $app['crmall4Url'];
            $config->apiKey = $app['crmall4Key'];
            $config->cacheOptions = ['cacheDir' => $app['crmall4Cache']];
            $config->useSession = true;

            /** @var Session $session */
            $session = $app['session'];
            $loggedUser = $session->get($app['userSession'], false);

            $app['user'] = null;

            if ($session && $loggedUser) {
                $config->cacheKey = $loggedUser->token->cacheKey;
                $app['user'] = $loggedUser;
            }

            Service::initService($config);

            $app[Person::class] = $app->factory(function ($c) {
                return new Person();
            });

            $app[User::class] = $app->factory(function ($c) {
                return new User();
            });

            $app[Lottery::class] = $app->factory(function ($c) {
                return new Lottery();
            });

            $app[Survey::class] = $app->factory(function ($c) {
                return new Survey();
            });

            $app[Store::class] = $app->factory(function ($c) {
                return new Store();
            });
        } catch (\Throwable $t) {
        }
    }
}
