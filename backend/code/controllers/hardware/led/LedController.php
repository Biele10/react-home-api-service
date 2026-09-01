<?php

namespace Samaritan\controllers\hardware\led;

Class LedController extends \Samaritan\controllers\hardware\HardwareController
{
    public function power() : \Samaritan\resources\Response
    {
        $ledService = new \Samaritan\services\hardware\led\LedService();
        $result = $ledService->power();

        $this->data = $result['data'];

        if ($result['success'] !== true)
        {
            return $this->Error();
        }

        return $this->Success();
    }
}