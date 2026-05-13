#pragma once
#include "structures/HashTable.hpp"
#include "output/Result.hpp"

class OnboardLed
{
    public:
        OnboardLed(bool initialState = false);
        Result handler(HashTable* command_and_params);       // function that handles what to do with user input
        Result power(HashTable* command_and_params);

    private:
        bool state;     // represents whether the LED is on or off
};