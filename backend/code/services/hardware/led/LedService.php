<?php

namespace Samaritan\services\hardware\led;

Class LedService extends \Samaritan\services\hardware\HardwareService
{
    public function power() : array
    {
        $command = \Samaritan\arduino\Commands::RED_LED_POWER;
        $result = $this->sendCommand($command);

        if ($result['success'] !== true)
        {
            return ['success' => false, 'data' => ['message' => 'Failed to send command.']];
        }

        return ['success' => true, 'data' => ['message' => 'This worked!']];
    }
}