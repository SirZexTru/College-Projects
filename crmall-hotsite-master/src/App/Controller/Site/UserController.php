<?php

namespace App\Controller\Site;

use App\Traits\ReCaptcha;
use App\Util\StringUtil;
use Crmall4Lib\Modules\Base\Address\AddressModel;
use Crmall4Lib\Modules\Base\Crypt\Pwd;
use Crmall4Lib\Modules\Base\Email\EmailModel;
use Crmall4Lib\Modules\Base\Enum\EnumAccessEnvironment;
use Crmall4Lib\Modules\Base\Enum\EnumEmailType;
use Crmall4Lib\Modules\Base\Enum\EnumGender;
use Crmall4Lib\Modules\Base\Enum\EnumMaritalStatus;
use Crmall4Lib\Modules\Base\Enum\EnumPersonOrigin;
use Crmall4Lib\Modules\Base\Enum\EnumPersonType;
use Crmall4Lib\Modules\Base\Enum\EnumPhoneType;
use Crmall4Lib\Modules\Base\Phone\PhoneModel;
use Crmall4Lib\Modules\Person\Person;
use Crmall4Lib\Modules\Person\Person\PersonModel;
use Crmall4Lib\Modules\User\LoggedUser\LoggedUserModel;
use Crmall4Lib\Modules\User\User;
use Crmall4Lib\Service;
use Symfony\Component\HttpFoundation\RedirectResponse;
use Symfony\Component\HttpFoundation\Session\SessionInterface;
use Symfony\Component\Security\Core\Security;

class UserController extends BaseController
{
    use ReCaptcha;

    /** @var User */
    protected $userService;

    /** @var Person */
    protected $personService;

    public function routes()
    {
        $this->route->get('/login', function () {
            if ($this->app['user']) {
                return  $this->app->redirect('/meus-cupons');
            }

            return $this->render('login.twig');
        });

        $this->route->post('/login', array($this, 'loginAction'));
        $this->route->get('/logout', array($this, 'logoutAction'));

        $this->route->post('/forgot-password', array($this, 'forgotPasswordAction'));
        $this->route->get('/redefinir-senha/{token}', array($this, 'redefinePasswordAction'));
        $this->route->post('/new-password', array($this, 'newPasswordAction'));

        $this->route->get('/cadastro', array($this, 'newAccountAction'));
        $this->route->post('/new-user', array($this, 'newUserAction'));

        $this->route->get('/minha-conta', array($this, 'myAccountAction'));
        $this->route->post('/edit', array($this, 'editUserAction'));
    }

    public function loginAction()
    {
        $username = trim($this->app[Person::class]->numbersOnly($this->request->get('_username')));
        $password = $this->request->get('_password');

        if (empty($username) || empty($password)) {
            return $this->render('login.twig', ['login_error' => 'Os campos cpf e senha são obrigatórios']);
        }

        try {
            $user = $this->getCrmallUser($username, $password);

            if ($user) {
                $this->app['user'] = $user;

                $this->request->getSession()->start();
                $this->request->getSession()->remove($this->app['userSession']);
                $this->request->getSession()->set($this->app['userSession'], $user);

                return  $this->app->redirect('/meus-cupons');
            }
        } catch (\Exception $e) {
            return $this->render('login.twig', ['login_error' => 'Verifique seus dados e tente novamente.']);
        }

        return $this->render('index.twig', ['login_error' => 'Verifique seus dados e tente novamente']);
    }

    public function logoutAction()
    {
        if ($this->app['user']) {
            Service::destroyInstance();

            $this->app['user'] = null;

            $this->request->getSession()->remove($this->app['userSession']);
        }

        return  $this->app->redirect('/');
    }

    public function newAccountAction()
    {
        if ($this->app['campaignFinished']) {
            return $this->app->redirect('/');
        }

        if ($this->app['user']) {
            return  $this->app->redirect('/meus-cupons');
        }

        $this->clearSession();

        return $this->render('cadastro.twig', ['registerError' => '']);
    }

    public function myAccountAction()
    {
        $this->checkLoggedUserCrmall();

        if (!$this->app['user']) {
            return  $this->app->redirect('/');
        }

        $user = $this->app['user'];
        $person = $this->app[Person::class]->getByDocument($user->getDocumentNumber())->toArray();

        $person['phone'] = '';
        $person['cellPhone'] = '';

        foreach ($person['phones'] as $phone) {
            if ($phone['type'] == EnumPhoneType::CONTACT) {
                $person['phone'] = str_replace(' ', '', $phone['phoneNumber']);
            } elseif ($phone['type'] == EnumPhoneType::PERSONAL) {
                $person['cellPhone'] = str_replace(' ', '', $phone['phoneNumber']);
            }
        }

        $person['documentNumber'] = $this->mask($person['documentNumber'], '###.###.###-##');

        if ($person['day'] !== null && $person['month'] !== null) {
            $person['day'] = $person['day']<10?'0'.$person['day']:$person['day'];
            $person['month'] = $person['month']<10?'0'.$person['month']:$person['month'];
        }

        $person['address'] = [
            'zipCode' => '',
            'address' => '',
            'number' => '',
            'complement' => '',
            'neighborhood' => '',
            'state' => '',
            'city' => ''
        ];

        foreach ($person['addresses'] as $address) {
            if ($address['isDefault']) {
                $person['address'] = [
                    'zipCode' => $address['zipCode'],
                    'address' => $address['address'],
                    'number' => $address['number'],
                    'complement' => $address['complement'],
                    'neighborhood' => $address['neighborhood'],
                    'state' => $address['state'],
                    'city' => $address['city'],
                ];
            }
        }

        $person['passwordRecoveryEmail'] = $user->passwordRecoveryEmail;

        return $this->render('minha-conta.twig', ['person' => $person]);
    }

    public function editUserAction()
    {
        if (!$this->app['user']) {
            return  $this->app->redirect('/');
        }

        /** @var LoggedUserModel $user */
        $user = $this->app['user'];

        $post = $this->request->request->all();

        $documentNumber = $this->app[Person::class]->numbersOnly($this->app['user']->documentNumber);

        /** @var Person\PersonModel $person */
        $person = $this->app[Person::class]->getByDocument($documentNumber);

        try {
            $this->savePerson($post, $person);
            $user->name = $person->getName();

            $this->request->getSession()->set($this->app['userSession'], $user);
        } catch (\Throwable $e) {
            $this->app['session']->getFlashBag()->add('error', 'Não foi possível editar seus dados no momento, por favor, tente novamente mais tarde.');
            return  $this->app->redirect('/user/minha-conta');
        }

        try {
            if ($post['password'] && $post['confirmPassword'] && ($post['password'] == $post['confirmPassword'])) {
                $this->saveUser([
                    "userID" => $person->getId(),
                    "login" => $this->app['user']->documentNumber,
                    "password" => $post['password'],
                    "emailRecovery" => trim($post['email']),
                ]);

                $this->refreshUser($documentNumber, $post['password']);
            }
        } catch (\Throwable $t) {
            if ($t->getCode() === 401) {
                $this->clearSession();
                $this->app['session']->getFlashBag()->add('error', 'É necessário efetuar o login para editar as informações de cadastro.');
                return  $this->app->redirect('/');
            }
            $this->app['session']->getFlashBag()->add('error', 'Seus dados foram alterados, porém não foi possível alterar sua senha no momento, por favor, tente novamante.');
            return  $this->app->redirect('/user/minha-conta');
        }

        $this->app['session']->getFlashBag()->add('message', 'Seus dados foram alterados com sucesso!');
        return  $this->app->redirect('/user/minha-conta');
    }

    public function newUserAction()
    {
        if ($this->app['user']) {
            return  $this->app->redirect('/meus-cupons');
        }

        // $recaptchaResponse = $this->request->get('g-recaptcha-response');

        // if (!$this->validateCaptcha($recaptchaResponse)) {
        //     return $this->render('cadastro.twig', ['registerError' => 'Captcha inválido! Tente novamente.']);
        // }

        $post = $this->request->request->all();

        $requiredAnswers = $this->checkRequiredAnswers($post);

        if (!$requiredAnswers) {
            return $this->render('cadastro.twig', ['registerError' => 'É necessário ser maior de 18 anos e concordar com a Política de Privacidade e o Regulamento da promoção para continuar.']);
        }

        try {
            $person = $this->savePerson($post);
            $documentNumber = StringUtil::numbersOnly($post['cpf']);

            $this->saveUser([
                "userID" => $person->getId(),
                "login" => $documentNumber,
                "password" => $post['password'],
                "emailRecovery" => trim($post['email']),
            ], true);
        } catch (\Throwable $e) {
            return $this->render('index.twig', ['registerError' => 'Ocorreu um erro, por favor, tente novamente mais tarde.']);
        }

        $user = $this->getCrmallUser($documentNumber, $post['password']);

        if ($user) {
            $this->request->getSession()->start();
            $this->request->getSession()->remove($this->app['userSession']);
            $this->request->getSession()->set($this->app['userSession'], $user);

            $this->app['session']->getFlashBag()->add('newUserSuccess', 'Parabéns seu cadastro foi efetuado com sucesso!');
            
            return  $this->app->redirect('/meus-cupons');
        }

        return $this->render('cadastro.twig', ['registerError' => 'Ocorreu um erro, por favor, tente novamente mais tarde.']);
    }

    public function forgotPasswordAction()
    {
        if ($this->app['user']) {
            $redirect = '/meus-cupons';

            if ($this->app['campaignType'] != 'lotteryWithCrm') {
                $redirect = '/meus-cupons/enviados';
            }

            return  $this->app->redirect($redirect);
        }

        $email = $this->request->get('email');

        if (!$this->app[User::class]->checkEmailExists($email)) {
            return $this->render('esqueci-minha-senha.twig', [
                'message' => 'Email não cadastrado, por favor tente novamente!',
                'class' => 'danger'
            ]);
        }

        $token = $this->app[User::class]->getService()->post('user/passwordrecovery/token', $email);

        if (isset($token[0]['token'])) {
            $url = $this->app['baseUrl'] . '/user/redefinir-senha/' . $token[0]['token'];
            $date = date_create_from_format('Y-m-d H:i:s', $token[0]['expirationDate'])->format('d/m/Y H:i:s');
            $name = $token[0]['name'];

            $from = ['noreply@riogaleao.com.br' => $this->app['campaignName']];
            $to = [$email => $name];
            $body = $this->render('email/forgotPassword.twig', ['url' => $url, 'name' => $name, 'date' => $date, 'logo' => $this->app['baseUrl'].'/img/logo.svg']);

            if ($this->sendEmail($this->app['campaignName'] . ' - Redefinição de senha', $to, $from, $body)) {
                // Success response
                return $this->render('esqueci-minha-senha.twig', [
                    'message' => 'Um e-mail de recuperação de senha foi enviado para ' . $email,
                    'class' => 'success'
                ]);
            }
        }

        // Fail response
        throw new \Exception('Não foi possivel redefnir sua senha, por favor, tente novamente mais tarde', 500);
    }

    public function redefinePasswordAction($token)
    {
        return $this->render('redefinir-senha.twig', ['token' => $token]);
    }

    public function newPasswordAction()
    {
        $post = $this->request->request->all();

        $prepare = [
            'token' => $post['token'],
            'newPassword' => $post['newPassword'],
        ];

        $this->app[User::class]->getService()->post('user/passwordrecovery/changepassword', $prepare);

        return $this->render('redefinir-senha.twig', ['message' => 'Senha alterada com sucesso']);
    }

    public function refreshUser($username, $password)
    {
        $this->clearSession();

        $user = $this->getCrmallUser($username, $password, EnumAccessEnvironment::CUSTOMER);

        if ($user) {
            $this->app['user'] = $user;
            $this->request->getSession()->set($this->app['userSession'], $user);
        }
    }

    protected function checkRequiredAnswers($post)
    {
        if ((!isset($post['majority']) && $post['majority'] !== 'on')
            && (!isset($post['acceptPrivacyPolicy']) && $post['acceptPrivacyPolicy'] !== 'on')
            && (!isset($post['acceptPromotionRules']) && $post['acceptPromotionRules'] !== 'on')
        ) {
            return false;
        }

        return true;
    }

    protected function getAuthenticationErrorMessage()
    {
        $error = false;
        if ($this->request->getSession() instanceof SessionInterface) {
            $error = $this->request->getSession()->get(Security::AUTHENTICATION_ERROR, false);
            if ($error) {
                $error = $error->getMessage();
                $this->request->getSession()->remove(Security::AUTHENTICATION_ERROR);
            }
        }

        return $error;
    }

    /**
     * @param array $data
     * @param PersonModel|null $person
     * @return PersonModel
     * @throws \Exception
     */
    private function savePerson(array $data, PersonModel $person = null)
    {
        if (!$person) {
            $person = new PersonModel();
        }

        foreach ($data as &$row) {
            if (is_string($row)) {
                $row = trim($row);
            }
        }

        $birthDate = date_create_from_format('d/m/Y', $data['birthDate']);

        $person->clearLists();
        $person->setDocumentNumber($data['cpf']);
        $person->setName($data['personName']);
        $person->setOrigin(EnumPersonOrigin::APIAPP());
        $person->setPersonType(EnumPersonType::NATURAL());
        $person->setDay($birthDate->format('d'));
        $person->setMonth($birthDate->format('m'));
        $person->setYear($birthDate->format('Y'));
        $person->setOtherDocument($data['rg']);
//        $person->setOccupation($data['occupation']);

        if (in_array($data['gender'], [1,2])) {
            $person->setGender(EnumGender::getEnumByValue($data['gender']));
        } else {
            $person->setGender(null);
        }

        $person->setMaritalStatus(EnumMaritalStatus::getEnumByValue($data['maritalStatus']));

//        if ($data['phone']) {
//            $phoneModel = new PhoneModel();
//            $phoneModel->setPhoneNumber($phoneModel->numbersOnly($data['phone']));
//            $phoneModel->setIsDefault(true);
//            $phoneModel->setType(EnumPhoneType::CONTACT());y
//
//            $person->addPhone($phoneModel);
//        }

        if ($data['cellPhone']) {
            $phoneModel = new PhoneModel();
            $phoneModel->setPhoneNumber($phoneModel->numbersOnly($data['cellPhone']));
            $phoneModel->setIsDefault(true);
            $phoneModel->setType(EnumPhoneType::PERSONAL());

            $person->addPhone($phoneModel);
        }

        $address = new AddressModel();
        $address->setZipCode($data['cep']);
        $address->setAddress($data['streetName']);
        $address->setNumber($data['number']);
        $address->setComplement($data['complement']);
        $address->setNeighborhood($data['neighborhood']);
        $address->setState($data['state']);
        $address->setCity($data['city']);
        $address->setIsDefault(true);

        $person->clearAddresses();
        $person->addAddress($address);

        $email = new EmailModel();
        $email->setIsDefault(true);
        $email->setType(EnumEmailType::PERSONAL());
        $email->setEmail($data['email']);

        $person->addEmail($email);

        $this->app[Person::class]->save($person);

        $person = $this->app[Person::class]->getByDocument($data['cpf']);

        return $person;
    }

    private function saveUser($userData, $newUser = false)
    {
        $userData += [
            'environment' => EnumAccessEnvironment::CUSTOMER,
            'accessLevelID' => $this->app['accessLevelId']
        ];

        $userToken = base64_encode(Pwd::encodePWDEx($this->app['crmall4Env']));

        /** @var User $user */
        $user = $this->app[User::class];

        if ($newUser && $user->getById($userData['userID'])) {
            $user->activate($userData['userID'], EnumAccessEnvironment::CUSTOMER, $this->app['accessLevelId']);
        }

        $user->getService()->post('/user/v2/update/' . $userToken, $userData);
    }
}
