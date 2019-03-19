<?php

$arrayCampaigns = [];

$winnersDir = PATH_PUBLIC . "/files/ganhadores/";

if (!is_dir($winnersDir)) {
    mkdir($winnersDir, 0775, true);
}

if (!env('CRMALL4_SINGLE_CAMPAIGN', true)) {
    if (env('CRMALL4_GENERAL_LOTTERY_CAMPAIGN', false)) {
        //CAMPAIGNS PARAMETERS
        $app['generalCampaign'] = [
            'id' => env('CRMALL4_GENERAL_LOTTERY_CAMPAIGN'),
            'campaignBegins' => \DateTime::createFromFormat('d/m/Y', env('CAMPAIGN_GENERAL_BEGINS')),
            'campaignEnds' => \DateTime::createFromFormat('d/m/Y', env('CAMPAIGN_GENERAL_ENDS')),
            'prize' => env('CAMPAIGN_GENERAL_PRIZE'),
        ];

        if (!file_exists($winnersDir . "ganhadores-{$app['generalCampaign']['id']}.csv")) {
            file_put_contents($winnersDir . "ganhadores-{$app['generalCampaign']['id']}.csv", '');
        }
    }

    $break = false;
    $i = 1;

    while (!$break) {
        $id = env("CRMALL4_LOTTERY_CAMPAIGN_{$i}");

        if (!$id) {
            $break = true;
        }

        $arrayCampaigns[] = [
            'id' => $id,
            'campaignBegins' => \DateTime::createFromFormat('d/m/Y', env("CAMPAIGN_{$i}_BEGINS")),
            'campaignEnds' => \DateTime::createFromFormat('d/m/Y', env("CAMPAIGN_{$i}_ENDS")),
            'prize' => env("CAMPAIGN_{$i}_PRIZE"),
        ];

        if (!file_exists(PATH_PUBLIC."/files/ganhadores/ganhadores-{$id}.csv")) {
            file_put_contents(PATH_PUBLIC."/files/ganhadores/ganhadores-{$id}.csv", '');
        }

        $i++;
    }
} else {
    //CAMPAIGNS PARAMETERS
    $app['generalCampaign'] = [
        'id' => $app['campaignType'] != 'withCrm'?env('CRMALL4_LOTTERY_CAMPAIGN', false):$app['campaign']['campaignId'],
        'campaignBegins' => \DateTime::createFromFormat('d/m/Y', env('CAMPAIGN_BEGINS')),
        'campaignEnds' => \DateTime::createFromFormat('d/m/Y', env('CAMPAIGN_ENDS')),
        'prize' => env('CRMALL4_CAMPAIGN_PRIZE'),
    ];

    if (!file_exists(PATH_PUBLIC."/files/ganhadores/ganhadores-{$app['generalCampaign']['id']}.csv")) {
        file_put_contents(PATH_PUBLIC."/files/ganhadores/ganhadores-{$app['generalCampaign']['id']}.csv", '');
    }
}

$app['lotteryCampaigns'] = $arrayCampaigns;

$app["adminUser"] = env("ADMIN_USER");
$app["adminPassword"] = env("ADMIN_PASSWORD");
