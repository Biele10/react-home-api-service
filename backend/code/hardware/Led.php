<?php
namespace Samaritan\hardware;

// This file handles any functionality in relation to LEDs.

Class Led
{
    private $pinNumber;

    public function __construct(int $pinNumber)
    {
        $this->pinNumber = $pinNumber;
    }

    public function getPin()
    {
        return $this->pinNumber;
    }

    public function power()
    {
        // insert logic like !currentState
    }
}