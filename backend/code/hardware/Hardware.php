<?php

namespace Samaritan\hardware;

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