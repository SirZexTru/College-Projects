<?php

namespace App\Services;

use App\Util\StringUtil;
use GuzzleHttp\Client;
use Silex\Application;
use Symfony\Component\HttpFoundation\File\UploadedFile;

class CampaignService
{
    /** @var CacheService */
    protected $cache;

    /** @var Client */
    protected $client;

    /** @var Application */
    protected $app;

    protected $requestTentatives = 0;

    public function __construct($app)
    {
        $this->app = $app;
        $this->client = new Client();
        $this->cache = $app[CacheService::class];
    }

    public function getToken()
    {
        $appId = $this->app['campaign']['appId'];
        $appSecret = $this->app['campaign']['appSecret'];

        try {
            $token = $this->cache->get("campaignToken");

            if ($token) {
                return $token;
            }

            $response = $this->client->request(
                'GET',
                $this->app['campaign']['url'] . '/v2/oauth/token',
                ['auth' => [$appId, $appSecret]]
            );

            $result = json_decode($response->getBody());

            if ($result->access_token) {
                $this->cache->delete("campaignToken");
                $this->cache->save("campaignToken", $result->access_token, 3600);
            }

            return $result->access_token;
        } catch (\Throwable $t) {
            return $t->getMessage();
        }
    }

    public function sendDocument($invoice)
    {
        $ownerKey = StringUtil::numbersOnly($invoice['documentNumber']);
        $id = StringUtil::toAlphaNumeric($this->app['campaignName']);
        $totalValue = isset($invoice['value'])?$invoice['value']:0;
        $totalValue = str_replace('.', '', $totalValue);
        $totalValue = (float)str_replace(',', '.', $totalValue);

        $imageName = uniqid('img_');
        $invoice['image']->move(PATH_CACHE . '/temp', $imageName . '.jpg');

        $transcription  = [
            'id' => $imageName,
            'type' => 'receipt',
            'purchaseDate' => $invoice['date'],
            'number' => $invoice['code'],
            'storeDocument' => StringUtil::numbersOnly($invoice['storeDocumentNumber']),
            'storeName' => $invoice['storeName'],
            'consumer' => $ownerKey,
            'seller' => $invoice['flight']
        ];

        if ($this->app['campaignSendProducts']) {
            $products = [];

            $invoice['products'] = json_decode($invoice['products'], true);

            foreach ($invoice['products'] as $product) {
                $products[] = [
                    "unit" => "UN",
                    "quantity" => $product['qtd'],
                    "code" => $product['productBarCode'],
                    "total_price" => number_format((float)$product['productValue'], 2, ',', ''),
                    "unit_price" => number_format((float)$product['productValue'] / $product['qtd'], 2, ',', ''),
                    "ncm_code" => "",
                    "description" => $product['productName'],
                    "productId" => $product['productBarCode']
                ];

                $totalValue += $product['productValue'];
            }

            $transcription['items'] = $products;
        }

        $transcription['value'] = number_format($totalValue, 2, '.', '');

        $protocolToken = $this->getProtocolToken($ownerKey);

        $document = [
            'campaign' => $this->app['campaign']['campaignId'],
            'ownerKey' => $ownerKey,
            'protocolToken' => $protocolToken,
            'documents[]' => json_encode($transcription),
            'senderId' => 'hotsite-' . $id,
            'files[]' => fopen(PATH_CACHE . '/temp/' . $imageName . '.jpg', 'r')
        ];

        $prepare = [];

        foreach ($document as $key => $row) {
            $prepare[] = [
                'name' => $key,
                'contents' => $row,
            ];
        }

        $request = [
            'headers' => [
                'Authorization' => 'Bearer ' . $this->getToken(),
            ],
            'multipart' => $prepare,
            'exceptions' => false,
        ];

        $response = $this->client->request('POST', $this->app['campaign']['url'] .  '/v2/document/create', $request);

        @unlink(PATH_CACHE . '/temp/' . $imageName . '.jpg');

        if ($response->getStatusCode() == 200) {
            $response = json_decode($response->getBody()->getContents());

            if ($response->code == 200) {
                $this->closeProtocol($ownerKey, $protocolToken);
                $this->cache->delete("protocol-.{$ownerKey}");

                return true;
            }
        }

        $error = json_decode($response->getBody()->getContents(), true);

        throw new \Exception($error['message'], 500);
    }

    public function getDocuments($ownerKey, \DateTime $startDate, \DateTime $endDate = null)
    {
        $campaignId = $this->app['campaign']['campaignId'];
        $ownerKey = StringUtil::numbersOnly($ownerKey);
        $startDate = $startDate->format('d/m/Y');

        $url = "/v2/document/?campaign={$campaignId}&ownerKey={$ownerKey}&startDate={$startDate}";

        if ($endDate) {
            $endDate = $endDate->format('d/m/Y');
            $url .= '&endDate=' . $endDate;
        }

        $response = $this->requestFromCampanhas($url);

        $result = [];

        if ($response->code == 200) {
            foreach ($response->data as $protocol) {
                foreach ($protocol->invoices as $invoice) {
                    $invoice->protocol = $protocol->protocol;

                    if ($invoice->value) {
                        $invoice->value = number_format($invoice->value, 2, ',', '.');
                    }

                    if ($invoice->purchaseDate) {
                        $invoice->purchaseDate = (new \DateTime($invoice->purchaseDate))->format('d/m/Y');
                    }

                    $invoice->created = (new \DateTime($invoice->created))->format('d/m/Y');
                    $invoice->storeDocument = StringUtil::mask($invoice->storeDocument, '##.###.###/####-##');

                    $result[] = $invoice;
                }
            }
        }

        return $result;
    }

    public function saveStore($store)
    {
        $store['campaign'] = $this->app['campaign']['campaignId'];
        $prepare = [];

        foreach ($store as $key => $row) {
            $prepare[] = [
                'name' => $key,
                'contents' => $row,
            ];
        }

        $request = [
            'headers' => [
                'Authorization' => 'Bearer ' . $this->getToken(),
            ],
            'multipart' => $prepare,
            'exceptions' => false,
        ];

        $this->client->request('POST', $this->app['campaign']['url'] .  '/v2/store/add', $request);
    }

    public function getImage($imageId)
    {
        return $this->requestFromCampanhas('/document/image/' . $imageId, false);
    }

    private function getProtocolToken($ownerKey)
    {
        $tokenKey = "protocol-.{$ownerKey}";
        $protocolToken = $this->cache->get($tokenKey);

        if ($protocolToken) {
            return $protocolToken;
        }

        $sendData = [
            [
                'name' => 'campaign',
                'contents' => $this->app['campaign']['campaignId'],
            ],
            [
                'name' => 'ownerKey',
                'contents' => $ownerKey,
            ]
        ];

        $request = [
            'headers' => [
                'Authorization' => 'Bearer ' . $this->getToken(),
            ],
            'multipart' => $sendData,
            'exceptions' => false,
        ];

        $response = $this->client->request('POST', $this->app['campaign']['url'] . '/v2/protocol/create', $request);

        if ($response->getStatusCode() == 200) {
            $response = json_decode($response->getBody());

            if ($response->code == 200) {
                $this->requestTentatives = 0;
                $this->cache->save($tokenKey, $response->data->protocolToken, 300);

                return $response->data->protocolToken;
            }
        } elseif ($this->requestTentatives < 3) {
            $this->requestTentatives++;
            $this->cache->delete($tokenKey);

            return $this->getProtocolToken($ownerKey);
        }

        $error = json_decode($response->getBody()->getContents(), true);

        throw new \Exception($error['message'], 500);
    }

    private function closeProtocol($ownerKey, $protocolToken)
    {
        $document = [
            'campaign' => $this->app['campaign']['campaignId'],
            'ownerKey' => $ownerKey,
            'protocolToken' => $protocolToken,
        ];

        $prepare = [];

        foreach ($document as $key => $row) {
            $prepare[] = [
                'name' => $key,
                'contents' => $row,
            ];
        }

        $request = [
            'headers' => [
                'Authorization' => 'Bearer ' . $this->getToken(),
            ],
            'multipart' => $prepare,
            'exceptions' => false,
        ];

        $this->client->request('POST', $this->app['campaign']['url'] .  '/v2/protocol/close', $request);

        return;
    }

    private function requestFromCampanhas($url, $decodeReturn = true)
    {
        $response = $this->client->request(
            'GET',
            $this->app['campaign']['url'] . $url,
            [
                'headers' => [
                    'Authorization' => 'Bearer ' . $this->getToken(),
                ],
                'exceptions' => false,
            ]
        );

        if ($decodeReturn) {
            return json_decode($response->getBody()->getContents());
        }

        return $response->getBody()->getContents();
    }
}
