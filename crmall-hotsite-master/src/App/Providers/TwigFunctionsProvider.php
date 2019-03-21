<?php

namespace App\Providers;

use App\Util\Commons;
use Pimple\Container;
use Pimple\ServiceProviderInterface;
use Silex\Application;

class TwigFunctionsProvider implements ServiceProviderInterface
{
    public function register(Container $app)
    {
        $app->extend('twig', function (\Twig_Environment $twig, Application $app) {
            $twig->addGlobal('fileIsEmpty', filesize(PATH_PUBLIC . '/files/perguntas.txt') === 0);
            $twig->addGlobal('hasWinners', is_file(PATH_PUBLIC . '/files/winners.csv') && filesize(PATH_PUBLIC . '/files/winners.csv') !== 0);

            $twig->addFunction(new \Twig_SimpleFunction('webpackAsset', function ($file) {
                static $manifest;
                if (is_null($manifest)) {
                    $manifest = json_decode(file_get_contents(PATH_PUBLIC . '/mix-manifest.json'), true);
                }
                if (isset($manifest[$file])) {
                    return '/'.trim($manifest[$file], '/');
                }
                throw new \InvalidArgumentException("File {$file} not defined in asset manifest.");
            }));

            $twig->addFunction(new \Twig_SimpleFunction('maxLuckyCounter', function () use ($app) {
                $user = $app['user'];

                if ($user && $app['campaignMaxLuckyCounter']) {
                    try {
                        $documentNumber = $user->getDocumentNumber();

                        if ($user->relatedCompany) {
                            $documentNumber = $user->relatedCompany['documentNumber'];
                        }

                        return count($app[\Crmall4Lib\Modules\Lottery\Lottery::class]->getLuckyNumbers($app['lotteryCampaign'], $documentNumber)) >= $app['campaignMaxLuckyCounter'];
                    } catch (\Exception $e) {
                        return false;
                    }
                }

                return false;
            }));

            $twig->addFilter(new \Twig_SimpleFilter('phone', function ($num) {
                if (strlen($num) <= 8) {
                    $num = "62".$num;
                }

                return ($num)?'('.substr($num, 0, 2).') '.substr($num, 2, 4).'-'.substr($num, 6, 4):'&nbsp;';
            }));

            $twig->addFunction(new \Twig_SimpleFunction('svgImage', function ($path, $className = null, $isLocal = true) use ($app) {
                if ($isLocal) {
                    $path = PATH_PUBLIC . $path;
                }

                $svgTypes = [
                    'image/svg+xml',
                    'image/svg',
                    'text/html',
                    'text/plain',
                ];

                if (file_exists($path)) {
                    $mimeType = mime_content_type($path);
                } else {
                    $ch = curl_init($path);
                    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
                    curl_exec($ch);
                    $mimeType = curl_getinfo($ch, CURLINFO_CONTENT_TYPE);
                }

                if (in_array($mimeType, $svgTypes)) {
                    $content = str_replace('{{ className }}', $className, file_get_contents($path));
                    $content = preg_replace('/<style(.*?)\/style>/s', '', $content);

                    return $content;
                } else {
                    if ($className) {
                        $className = "class=\"{$className}\"";
                    }

                    return "<img src=\"{$path}\" {$className}>";
                }
            }));

            $twig->addFilter(new \Twig_SimpleFilter('slug2title', function ($value) use ($app) {
                return ucwords(str_replace('-', ' ', $value));
            }));

            $twig->addFunction(new \Twig_SimpleFunction('isCampaignStarted', function () {
                return isCampaignStarted();
            }));

            $twig->addFunction(new \Twig_SimpleFunction('isCampaignFinished', function () {
                return isCampaignFinished();
            }));

            $twig->addFunction(new \Twig_SimpleFunction('isCampaignHappening', function () {
                return isCampaignHappening();
            }));

            $twig->addFunction(new \Twig_SimpleFunction('getRemainingCampaignDays', function () use ($app) {
                return $app['campaignEnds']->diff(new \DateTime(), true)->days;
            }));

            $twig->addGlobal('statesAllowed', Commons::getStatesAllowed());

            $twig->addGlobal('maritalStatus', [
                1 => 'Solteiro(a)',
                2 => 'Casado(a)',
                3 => 'Viúvo(a)',
                4 => 'Divorciado(a)',
            ]);

            $twig->addGlobal('gender', [
                3 => 'Outros',
                1 => 'Masculino',
                2 => 'Feminino'
            ]);

            return $twig;
        });
    }
}
