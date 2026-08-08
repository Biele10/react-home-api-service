<?php

namespace App\services\hardware\led;

Class OnBoardLedService extends \App\services\hardware\HardwareService
{
    public function power() : array
    {
        $command = 'module=onBoardLed&method=power';
        $result = $this->sendCommand($command);

        if ($result['success'] !== true)
        {
            return ['success' => false, 'data' => ['message' => 'Failed to send command.']];
        }

        return ['success' => true, 'data' => ['message' => 'This worked!']];
    }
}