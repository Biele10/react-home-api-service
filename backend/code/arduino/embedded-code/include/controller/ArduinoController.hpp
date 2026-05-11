#pragma once
#include <Arduino.h>
#include "structures/HashTable.hpp"
#include "output/Result.hpp"
#include "hardware-components/Led.hpp"

class ArduinoController
{
    public:
        void setupHardware();
        Result handleCommand(HashTable* command_and_params);
        ArduinoController(int redLedPin);
    private:
        Led redLed;
};