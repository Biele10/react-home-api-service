#pragma once
#include "structures/HashTable.hpp"
#include "output/Result.hpp"

class Led
{
    public:
        Led(int pinNumber, bool initialState = false);
        Result power(uint16_t* args, uint8_t count);

    private:
        int pin;
        bool state;     // represents whether the LED is on or off
        Result on();
        Result off();
};