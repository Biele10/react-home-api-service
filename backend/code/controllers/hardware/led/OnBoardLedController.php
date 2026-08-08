<?php

namespace App\controllers\hardware\led;

Class OnBoardLedController extends \App\controllers\hardware\HardwareController
{
    public function power() : \App\resources\Response
    {
        $onBoardLedService = new \App\services\hardware\led\OnBoardLedService();
        $result = $onBoardLedService->power();

        $this->data = $result['data'];

        if ($result['success'] !== true)
        {
            return $this->error();
        }

        return $this->success();
    }
}