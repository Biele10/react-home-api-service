#include <Arduino.h>
#include "hardware-components/Led.hpp"
#include "output/Result.hpp"
#include "structures/HashTable.hpp"
#include "config/config.hpp"

Led::Led(int pinNumber, bool initialState) : pin(pinNumber), state(initialState) {};

/**
 * Handles all functions in relation to the LED.
 */
Result Led::handler(HashTable* command_and_params)
{
    String method = command_and_params->getValue("method");
    if (method == "power")
    {
        return this->power(command_and_params);
    }

    return Result::Error(ErrorCode::INVALID_COMMAND, "No such method found.");
}


Result Led::power(HashTable* command_and_params)
{
    if ((this->state) == false)
    {
        digitalWrite(pin, HIGH);
    }

    else if ((this->state) == true)
    {
        digitalWrite(pin, LOW);
    }

    this->state = !(this->state);
    return Result::Ok("Changed state of LED.");
}