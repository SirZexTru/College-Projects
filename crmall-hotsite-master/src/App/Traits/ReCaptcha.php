<?php
namespace App\Traits;

use GuzzleHttp\Client;

trait ReCaptcha
{
    public function validateCaptcha($captchaResponse)
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
}
