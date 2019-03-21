<?php

namespace App\Controller\Site;

use Crmall4Lib\Modules\Lottery\Lottery;
use Crmall4Lib\Modules\Lottery\NumberBySealedModel;
use Crmall4Lib\Modules\Sealed\Sealed;
use Symfony\Component\HttpFoundation\RedirectResponse;

class SealedCampaignController extends BaseController
{
    public function routes()
    {
        $this->route->get('/', array($this, 'newCouponAction'));
        $this->route->get('/check-coupon/{coupon}', array($this, 'checkCouponAction'));
        $this->route->post('/send-coupons', array($this, 'sendCouponsAction'));
    }

    private function getLuckyNumbersCount()
    {
        return count($this->app[Lottery::class]->getLuckyNumbers($this->app['lotteryCampaign'], $this->app['user']->getDocumentNumber()));
    }

    public function newCouponAction()
    {
        if ($this->app['campaignFinished']) {
            return $this->app->redirect('/');
        }

        if (!$this->app['user']) {
            return  $this->app->redirect('/user/login');
        }

        $count = $this->getLuckyNumbersCount();
        return $this->render('sealed-form.twig', ['luckyNumbersCount' => $count]);
    }

    public function checkCouponAction($coupon)
    {
        $used = true;
        $coupon = strtoupper($coupon);

        try {
            $info = $this->app[Sealed::class]->getInfo($this->app['crmall4SealedCampaign'], $coupon);
            $used = $info['isUsed'];
        } catch (\Exception $e) {
        }

        return $this->json([
            'valid' => !$used,
            'message' => $used ? 'Cupom inválid ou já utilizado' : 'Cupom válido'
        ]);
    }

    public function sendCouponsAction()
    {
        if ($this->app['campaignFinished']) {
            return $this->json(false);
        }

        $invoiceData = $this->request->request->all();
        $personDocument = $this->app['user']->getDocumentNumber();

        $tokens = $invoiceData['coupons'];
        $invalidTokens = [];
        $luckNumbers = [];
        $response = null;

        foreach ($tokens as $token) {
            $response = $this->registerSealedToken(strtoupper($token), $personDocument, $invoiceData);
            !$response ? $invalidTokens[] = $token : $luckNumbers[] = $response;
        }

        if (!empty($luckNumbers)) {
//            $this->sendEmailLuckNumbers($luckNumbers);
        }

        return $this->json(['success' => !count($invalidTokens), 'invalidTokens' => $invalidTokens, 'couponsCount' => count($tokens)]);
    }

    private function registerSealedToken($token, $personDocument, $invoiceData)
    {
        try {
            return $this->generateLuckyNumber($token, $personDocument, $invoiceData);
        } catch (\Throwable $t) {
            return false;
        }
    }

    private function generateLuckyNumber($token, $personDocument, $invoiceData)
    {
        if (empty($token)) {
            return true;
        }

        $numberBySealed = new NumberBySealedModel();

        $numberBySealed->setSealedToken($token);
        $numberBySealed->setSealedCampaign($this->app['crmall4SealedCampaign']);
        $numberBySealed->setLotteryCampaign($this->app['lotteryCampaign']);
        $numberBySealed->setDocument($personDocument);

        if ($this->app['campaignSealedHasReceipt']) {
            $numberBySealed->setStoreName($invoiceData['storeName']);
            $numberBySealed->setStoreDocument($invoiceData['storeDocumentNumber']);
            $numberBySealed->setInvoiceNumber($invoiceData['code']);
            $numberBySealed->setInvoiceValue($this->getInterValueFromInvoice($invoiceData['receiptValue']));
            $numberBySealed->setInvoicePurchasedDate(date_create_from_format('d/m/Y', $invoiceData['date']));
        }

        return $this->app[Lottery::class]->generateLuckyNumberFromSealed($numberBySealed);
    }

    private function getInterValueFromInvoice($value)
    {
        $value = str_replace('.', '', $value);
        return (float)str_replace(',', '.', $value);
    }

    private function sendEmailLuckNumbers($luckNumbers)
    {
        $from = ['noreply@crmall.com.br' => 'Hotsite Crmall'];

        $name = $this->app['user']->name;
        $to = [$this->app['user']->passwordRecoveryEmail => $name];
        $body = $this->render('email/confirmLuckNumbers.twig', ['name' => $name, 'logo' => $this->logoEmail, 'luckNumbers' => $luckNumbers]);

        $this->sendEmail('Promoção Super Férias - Números da sorte', $to, $from, $body);
    }
}
