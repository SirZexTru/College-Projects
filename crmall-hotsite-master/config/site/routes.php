<?php

$app->mount('/user', new App\Controller\Site\UserController());
$app->mount('/search', new App\Controller\Site\SearchController());
$app->mount('/meus-cupons', new App\Controller\Site\MyCouponsController());
$app->mount('/seladinha', new App\Controller\Site\SealedCampaignController());
$app->mount('/minha-pagina', new App\Controller\Site\MyPageController());
$app->mount('/', new App\Controller\Site\IndexController());

$app->get('/regulamento', function () use ($app) {
    $stores = \App\Util\Csv::read("files/stores-regulation.csv");

    return $app['twig']->render('site/regulamento.twig', ['stores' => $stores]);
});

$app->get('/fale-conosco', function () use ($app) {
    return $app['twig']->render('site/fale-conosco.twig');
});

$app->get('/ganhadores', function () use ($app) {
    $winners = [];

    if (is_file(PATH_PUBLIC . '/files/winners.csv')) {
        $winners = \App\Util\Csv::read(PATH_PUBLIC . '/files/winners.csv');
    }

    // echo "<pre>";
    // var_export($winners);
    // echo "</pre>";
    // exit;

    return $app['twig']->render('site/ganhadores.twig', ['winners' => $winners]);
});

$app->get('/get-occupations', function () use ($app) {
    $occupations = array_filter(explode("\n", file_get_contents('files/occupations.csv')));
    sort($occupations);

    return $app->json($occupations);
});

$app->get('/duvidas', function () use ($app) {
    $questions = explode("\n\n\n", file_get_contents('files/perguntas.txt'));
    foreach ($questions as &$question) {
        $question = explode("\n", $question);

        $aux[0] = $question[0];
        $aux[1] = '';
        unset($question[0]);
        foreach ($question as $index) {
            $aux[1] .= "<span>{$index}</span><br>";
        }

        $question = $aux;
    }

    return $app['twig']->render('site/duvidas.twig', ['questions' => $questions]);
});

$app->get('/esqueci-minha-senha', function () use ($app) {
    return $app['twig']->render('site/esqueci-minha-senha.twig');
});
