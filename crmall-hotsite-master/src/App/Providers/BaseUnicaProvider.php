<?php

namespace App\Providers;

use BaseUnicaLib\Modules\Address\Address;
use BaseUnicaLib\Modules\Cnpj\Cnpj;
use BaseUnicaLib\Modules\Cpf\Cpf;
use BaseUnicaLib\Service;
use Pimple\Container;
use Pimple\ServiceProviderInterface;

class BaseUnicaProvider implements ServiceProviderInterface
{
    public function register(Container $app)
    {
        try {
            Service::setConfig($app['baseUnicaUrl'], $app['baseUnicaKey'], $app['baseUnicaCache']);

            $app[Cpf::class] = function () {
                return new Cpf();
            };

            $app[Cnpj::class] = function () {
                return new Cnpj();
            };

            $app[Address::class] = function () {
                return new Address();
            };
        } catch (\Throwable $t) {
        }
    }
}
