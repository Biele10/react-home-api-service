<?php

namespace App\hardware;

// This is where all hardware related requests are sent to then use the correct class

Class HardwareHandler
{
    static public function _command(string $commandToSend)
    {
       return \App\arduino\ArduinoApi::_get($commandToSend);
    }
}