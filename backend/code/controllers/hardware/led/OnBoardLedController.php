<?php

namespace Samaritan\controllers\hardware\led;

Class OnBoardLedController extends \Samaritan\controllers\hardware\HardwareController
{
    public function power() : \Samaritan\resources\Response
    {
        $onBoardLedService = new \Samaritan\services\hardware\led\OnBoardLedService();
        $result = $onBoardLedService->power();

        $this->data = $result['data'];

        if ($result['success'] !== true)
        {
            return $this->Error();
        }

        return $this->Success();
    }
}