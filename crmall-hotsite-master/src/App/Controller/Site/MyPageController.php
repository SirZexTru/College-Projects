<?php

// criar nova rota "Minha Página"
// criar um controller e um arquivo do twig novo

namespace App\Controller\Site;

class MyPageController extends BaseController
{
    public function routes()
    {
        $this->route->get('/', array($this, 'indexAction'));
    }

    public function indexAction()
    {
        return $this->render('my-page.twig');
    }
}
