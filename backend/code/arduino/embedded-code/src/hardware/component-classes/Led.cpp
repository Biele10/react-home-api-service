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
    if (method == "on")
    {
        return this->on();
    }

    return Result::Error(ErrorCode::INVALID_COMMAND, "No such method found.");
}

/**
 * Function that turns the LED on or off, this
 * is only used via the website because the website does not
 * have a way of tracking the state of the LED.
 */
Result Led::power()
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
    return Result::Ok("Changed state of the LED");
}

// The on and off functions are used internally for specific behaviour
// as current state of the LED can easily be tracked

/**
 * Turns LED on.
 */
Result Led::on()
{
    if ((this->state) == false)             // these state checks are done to avoid unecessary digitalWrites
    {
        digitalWrite(pin, HIGH);
    }

    this->state = !(this->state);
    return Result::Ok("Turned LED on.");
}

/**
 * Turns LED off.
 */
Result Led::off()
{
    if ((this->state) == true)
    {
        digitalWrite(pin, LOW);
    }

    this->state = !(this->state);
    return Result::Ok("Turned LED off.");
}