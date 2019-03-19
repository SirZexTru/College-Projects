<?php

// Errors Exception
function error_handler(\Throwable $e, $code)
{
    global $app;
    $file = pathinfo($e->getFile());

    $code = ($code ?: $e->getTraceAsString());
    $request = new \Symfony\Component\HttpFoundation\Request();

    if ($request->isXmlHttpRequest()) {
        return $app->json([
            'success' => false,
            'message' => 'Error',
            'error' => $e->getMessage(),
            'serverror' => $code,
            'source' => $file['filename'],
            'line' => $e->getLine(),
        ], $code);
    }

    $code = $code . ' - ' . $e->getCode();

    if ($app['debug']) {
        $code = $e->getMessage() . ' - ' . $e->getCode() . ' - ' . $code;
    }

    if ($e instanceof \Symfony\Component\HttpKernel\Exception\HttpException && $e->getStatusCode() === 404) {
        return $app['twig']->render('site/errors/404.twig');
    }

    if ($e instanceof \Crmall4Lib\Exceptions\Crmall4LibException && $e->getCode() === 401) {
        return $app->redirect('/');
    }

    return $app['twig']->render('site/errors/error.twig', ['code' => $code]);
}

/** @var \Silex\Application $app */
$app->register(new Silex\Provider\HttpCacheServiceProvider());
$app->register(new Silex\Provider\SessionServiceProvider());
$app->register(new Silex\Provider\ValidatorServiceProvider());
$app->register(new \App\Providers\CrmallProvider());
$app->register(new \App\Providers\BaseUnicaProvider());
$app->register(new Silex\Provider\TwigServiceProvider(), array(
    'twig.options' => array(
        'cache' => $app['cacheEnabled'] ? $app['twig.options.cache'] : false,
        'strict_variables' => true,
        'debug' => $app['debug'],
    ),
    'twig.path' => array(PATH_VIEWS),
));

$app->register(new \App\Providers\TwigFunctionsProvider());

$app->register(new Silex\Provider\MonologServiceProvider(), array(
    'monolog.logfile' => PATH_LOG.'/app.log',
    'monolog.name' => 'app',
    'monolog.level' => 300
));

$app->error('error_handler');

$app[\Crmall4Lib\Modules\Lottery\Lottery::class] = function () {
    return new \Crmall4Lib\Modules\Lottery\Lottery();
};

$app[\App\Services\CacheService::class] = function () {
    return new \App\Services\CacheService([
        'cacheDir' => PATH_CACHE . '/campaign',
        'tempPath' => PATH_CACHE . '/campaign/temp'
    ]);
};

$app[\App\Services\CampaignService::class] = function () use ($app) {
    return new \App\Services\CampaignService($app);
};

$app['baseUrl'] = 'http'.(isset($_SERVER['HTTPS']) ? 's' : '').'://'.$_SERVER['HTTP_HOST'];
