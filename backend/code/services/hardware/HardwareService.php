<?php

namespace App\services\hardware;


// base hardware class that contains functions other components may use often

abstract Class HardwareService extends \App\services\Service
{
    protected ?int $pin;

    public function __construct(?int $pin = null)
    {
        $this->pin = $pin;
    }

    public function getPin(): int
    {
        return $this->pin;
    }

    final protected function sendCommand(string $command, array $params = []): ?array
    {
        // if (!empty($params))
        // {
        //     $command .=  PARSER_SEPARATOR . $this->_parseParams($params);
        // }

        \App\arduino\ArduinoApi::_get($command);
        return ['success' => true];     // true for now until we get Arudino to send data back to server
    }

    /**
     * Takes associative array of parameters and parses into a string
     * @param array $params
     * @return void
     */
    private function _parseParams(array $params) : string
    {
        // add logic so if error, just return "" instead
        return "TEMP";
    }
}