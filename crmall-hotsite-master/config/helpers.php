<?php

if (!function_exists('env')) {
    function env($key, $default = null)
    {
        $value = getenv($key);

        if ($value === false) {
            return $default;
        }

        switch (strtolower($value)) {
            case 'true':
            case '(true)':
                return true;

            case 'false':
            case '(false)':
                return false;

            case 'empty':
            case '(empty)':
                return '';

            case 'null':
            case '(null)':
                return null;
        }

        if (strlen($value) > 1 && preg_match('/^"/', $value) && preg_match('/"$/', $value)) {
            return substr($value, 1, -1);
        }

        return $value;
    }
}

if (!function_exists('redirectTo')) {
    function redirectTo($url)
    {
    }
}

if (!function_exists('isCampaignStarted')) {
    function isCampaignStarted()
    {
        global $app;
        static $campaignStarted;

        if (!isset($campaignStarted)) {
            $campaignStarted = (new \DateTime()) >= $app['campaignBegins'];
        }

        return $campaignStarted;
    }
}

if (!function_exists('isCampaignFinished')) {
    function isCampaignFinished()
    {
        global $app;
        static $campaignFinished;

        if (!isset($campaignFinished)) {
            $campaignFinished = (new \DateTime()) >= $app['campaignEnds'];
        }

        return $campaignFinished;
    }
}

if (!function_exists('isCampaignHappening')) {
    function isCampaignHappening()
    {
        return isCampaignStarted() && !isCampaignFinished();
    }
}

if (!function_exists('logger')) {
    function logger($message, $title = '', $action = '')
    {
        if (!is_dir(PATH_LOG)) {
            mkdir(PATH_LOG, 0775, true);
        }

        $file = PATH_LOG . '/log.log';
        $date = date('d-m-Y H:i:s');
        $ip = $_SERVER['REMOTE_ADDR'];

        if (is_array($message)) {
            $message = "\n" . print_r($message, true);
        }

        if ($title) {
            $title = " title:[{$title}] ";
        }

        if ($action) {
            $action = " action:[{$action}] ";
        }

        $message = "[{$date}] - from:[{$ip}] {$title} {$action} \n". $message;

        $log = fopen($file, 'a+') or die('Could not open log file.');

        fwrite($log, $message) or die('Could not write file!');
        fclose($log);
    }
}
