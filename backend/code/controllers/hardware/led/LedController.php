<?php

namespace App\controllers\hardware\led;

Class LedController extends \App\controllers\hardware\HardwareController
{
    public function power() : \App\resources\Response
    {
        $ledService = new \App\services\hardware\led\LedService(11);
        $result = $ledService->power();

        $this->data = $result['data'];

        if ($result['success'] !== true)
        {
            return $this->error();
        }

        return $this->success();
    }
}