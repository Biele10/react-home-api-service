<?php

namespace App\hardware;
use App\arduino\ArduinoApi;
// This is where all hardware related requests are sent to then use the correct class

Class Hardware
{
    static public function _powerOnBoardLed()
    {
        $result = ArduinoApi::_get("onBoardLedPower");
        echo json_encode($result);
        exit;
    }
}