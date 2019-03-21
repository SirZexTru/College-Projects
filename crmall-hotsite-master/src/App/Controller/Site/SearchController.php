<?php

namespace App\Controller\Site;

use App\Util\Csv;
use App\Util\StringUtil;
use BaseUnicaLib\Modules\Address\Address;
use BaseUnicaLib\Modules\Cnpj\Cnpj;
use BaseUnicaLib\Modules\Cpf\Cpf;
use Crmall4Lib\Modules\Person\Person;
use Crmall4Lib\Modules\Store\Store;
use Crmall4Lib\Modules\User\User;

class SearchController extends BaseController
{
    public function routes()
    {
        $this->route->get('/cpf/{cpf}', [$this, 'cpfAction']);
        $this->route->get('/cep/{zipCode}', [$this, 'cepAction']);
        $this->route->post('/email-exists', [$this, 'checkEmailAction']);
        $this->route->post('/check-cpf', [$this, 'checkCpfAction']);
        $this->route->get('/search-cpf/{documentNumber}/{birthDate}', [$this, 'searchCpfAction']);
        $this->route->get('/search-cnpj/{documentNumber}', [$this, 'searchCnpjAction']);
        $this->route->get('/products', [$this, 'searchProductsAction']);
    }

    public function searchProductsAction()
    {
        if (!file_exists(PATH_PUBLIC . '/files/products.csv')) {
            return $this->app->json(['results' => []]);
        }

        $search = StringUtil::withoutAccent($this->request->query->get('term'));

        $result = [];
        $products = Csv::read(PATH_PUBLIC . '/files/products.csv');

        array_walk($products, function ($a) use ($search, &$result) {
            if (strpos(mb_strtolower($a[0]), mb_strtolower($search)) !== false || strpos(mb_strtolower($a[1]), mb_strtolower($search)) !== false) {
                $result[] = [
                    'id' => $a[0] . '_' . $a[1],
                    'text' => $a[0] . ' - ' . $a[1],
                ];
            }
        });

        if (empty($result)) {
            $searchOriginal = $this->request->query->get('term');

            $result[] = [
                'id' => bin2hex($search) . '_' . $searchOriginal,
                'text' => bin2hex($search) . ' - ' . $searchOriginal,
            ];
        }

        return $this->app->json(['results' => $result]);
    }

    public function searchCnpjAction($documentNumber)
    {
        try {
            $personStore = $this->app[Store::class]->getByDocument($documentNumber);

            return $this->json([
                'storeName' => $personStore->getName()
            ], 200);
        } catch (\Exception $e) {
        }

        try {
            $personStore = $this->app[Cnpj::class]->consult($documentNumber);

            return $this->json([
                'storeName' => $personStore->getCompany()
            ], 200);
        } catch (\Exception $e) {
        }
        
        return $this->json([], 404);
    }

    public function searchCpfAction($documentNumber, $birthDate)
    {
        $result = [];
        $cod = 200;

        $service = $this->app[Cpf::class];

        try {
            $date = date_create_from_format('d-m-Y', $birthDate);

            if ($date) {
                $result = $service->consult($documentNumber, $date)->toArray();
                $cod = 200;
            }
        } catch (\Exception $e) {
            $cod = 404;
        }

        return $this->json($result, $cod);
    }

    public function cpfAction($cpf)
    {
        $personService = $this->app[Person::class];
        $person = null;

        try {
            $person = $personService->getByDocument($cpf)->toArray();
        } catch (\Exception $e) {
            return $this->json([], 404);
        }

        return $this->json($person);
    }

    public function checkEmailAction()
    {
        $email = $this->request->request->get('email');

        $userService = $this->app[User::class];
        $loggedUser = $this->app['user'];

        if ($loggedUser && strtolower($loggedUser->passwordRecoveryEmail) == strtolower($email)) {
            return $this->json(false);
        }

        return $this->json($userService->checkEmailExists($email));
    }

    public function checkCpfAction()
    {
        /** @var Person $personService */
        $personService = $this->app[Person::class];

        /** @var User $userService */
        $userService = $this->app[User::class];

        $cpf = $personService->numbersOnly($this->request->request->get('cpf'));

        try {
            $person = $personService->getByDocument($cpf)->toArray();
        } catch (\Exception $e) {
            return $this->json(false);
        }

        if ($user = $userService->getById($person['id'])) {
            return $this->json([
                'credentials' => strtolower($user->getCredentials()),
                'recoveryEmail' => $user->recoveryEmail
            ]);
        }

        return $this->json(false);
    }

    public function cepAction($zipCode)
    {
        try {
            $address = $this->app[Address::class]->search($zipCode);

            return $this->json(!empty($address)?$address[0]:[]);
        } catch (\Exception $e) {
            return $this->json([], 404);
        }
    }
}
