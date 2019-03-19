<?php

namespace App\Controller\Site;

class IndexController extends BaseController
{
    public function routes()
    {
        $this->route->get('/', array($this, 'indexAction'));
    }

    public function indexAction()
    {
        return $this->render('index.twig');
    }
}
