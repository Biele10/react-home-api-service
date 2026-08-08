<?php

namespace App\hardware;

// Hardware class that child classes inherit which contains some basic functions that hardware may need

abstract Class Hardware
{
    protected int $pin;

    public function __construct(int $pin)
    {
        $this->pin = $pin;
    }

    public function getPin(): int
    {
        return $this->pin;
    }

    final protected function sendCommand(string $command, array $params = []): ?array
    {
        if (!empty($params))
        {
            $command .=  PARSER_SEPARATOR . $this->_parseParams($params);
        }

        return \App\arduino\ArduinoApi::_get($command);
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