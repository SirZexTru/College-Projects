<?php
$app['debug'] = env('APP_DEBUG', false);
$app['cacheEnabled'] = env('CACHE_ENABLED', true);
$app['env'] = env('APP_ENV', 'prod');

if ($app['debug']) {
    ini_set('display_errors', 1);
    error_reporting(E_ALL & ~E_NOTICE);
} else {
    ini_set('display_errors', 0);
    error_reporting(0);
}

// Local
$app['locale'] = 'pt-BR';
$app['session.default_locale'] = $app['locale'];
date_default_timezone_set('America/Sao_Paulo');

$app['cache.path'] = PATH_CACHE;
$app['twig.options.cache'] = $app['cache.path'] . '/twig';

$app['baseUnicaUrl'] = env('BASE_UNICA_URL');
$app['baseUnicaKey'] = env('BASE_UNICA_KEY');
$app['baseUnicaCache'] = $app['cache.path'].'/baseUnica';

$app['crmall4Url'] = env('CRMALL4_URL');
$app['crmall4Key'] = env('CRMALL4_KEY');
$app['crmall4Cache'] = $app['cache.path'].'/crmall';

$app['accessLevelId'] = env('CRMALL4_ACCESS_LEVEL_ID');
$app['lotteryCampaign'] = env('CRMALL4_LOTTERY_CAMPAIGN');
$app['campaignId'] = env('CRMALL4_CAMPAIGN_ID');

$app['hasAwardPage'] = env('HAS_AWARD_PAGE');

$app['mail'] = [
    'host' => env('MAIL_HOST'),
    'port' => env('MAIL_PORT'),
    'username' => env('MAIL_USERNAME'),
    'password' => env('MAIL_PASSWORD'),
    'crypt' => env('MAIL_CRYPT')
];

$app['campaign'] = [
    'url' => env('CAMPAIGN_URL'),
    'appId' => env('CAMPAIGN_APP_ID'),
    'appSecret' => env('CAMPAIGN_APP_SECRET'),
    'campaignId' => env('CAMPAIGN_ID'),
];

$app['campaignAuthorization'] = env('CAMPAIGN_AUTHORIZATION_NUMBER');
$app['campaignBegins'] = \DateTime::createFromFormat('d/m/Y', env('CAMPAIGN_BEGINS'));
$app['campaignEnds'] = \DateTime::createFromFormat('d/m/Y', env('CAMPAIGN_ENDS'));
$app['campaignDateLottery'] = \DateTime::createFromFormat('d/m/Y', env('CAMPAIGN_DATE_LOTTERY'));
$app['campaignFinished'] = (new \DateTime()) > $app['campaignEnds'];
$app['campaignMaxLuckyCounter'] = env('CAMPAIGN_MAX_LUCKY_COUNTER');
$app['campaignMaxLuckyByNote'] = env('CAMPAIGN_MAX_LUCKY_BY_NOTE');
$app['campaignMaxLuckyByNote'] = env('CAMPAIGN_MAX_LUCKY_BY_NOTE');
$app['campaignType'] = env('CAMPAIGN_TYPE');
$app['campaignName'] = env('CAMPAIGN_NAME');
$app['campaignSealedHasReceipt'] = env('CAMPAIGN_SEALED_HAS_RECEIPT');
$app['crmall4Env'] = env('CRMALL4_ENV_ID');
$app['campaignSendProducts'] = env('CAMPAIGN_SEND_PRODUCTS');

$app['crmall4SealedCampaign'] = env('CRMALL4_SEALED_CAMPAIGN');
$app['crmall4CouponCampaign'] = env('CRMALL4_COUPON_CAMPAIGN');

$app['registerFormFields'] = explode(',', env('REGISTER_FORM_FIELDS'));

$app['analyticsCode'] = env('ANALYTICS_CODE', false);

$app['brand'] = env('CAMPAIGN_BRAND', $_SERVER['HTTP_HOST']);

$app['couponFormUrl'] = $app['campaignType'] == 'sealed'? '/seladinha' :'/meus-cupons/cadastrar';

$app['recaptcha'] = [
    'secret' => env('GOOGLE_RECAPTCHA_SECRET'),
    'public' => env('GOOGLE_RECAPTCHA_PUBLIC'),
    'url' => 'https://www.google.com/recaptcha/api/siteverify'
];

$app['userSession'] = \App\Util\StringUtil::toAlphaNumeric($app['brand']) . 'LoggedUser';
