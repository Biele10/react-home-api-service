#pragma once
#include "structures/HashTable.hpp"
#include "output/Result.hpp"

class Led
{
    public:
        Led(int pinNumber, bool initialState = false);
        Result handler(HashTable* command_and_params);       // function that handles what to do with user input
        Result power();
        Result on();
        Result off();

    private:
        int pin;
        bool state;     // represents whether the LED is on or off
};