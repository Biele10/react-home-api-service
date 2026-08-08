#include <Arduino.h>
#include "hardware-components/OnboardLed.hpp"
#include "output/Result.hpp"
#include "structures/HashTable.hpp"
#include "config/config.hpp"

OnboardLed::OnboardLed(bool initialState) : state(initialState) {};

/**
 * Handles all functions in relation to the onboard LED.
 */
Result OnboardLed::handler(HashTable* command_and_params)
{
    String method = command_and_params->getValue("method");
    if (method == "power")
    {
        return this->power(command_and_params);
    }

    return Result::Error(ErrorCode::INVALID_COMMAND, "No such method found.");
}


Result OnboardLed::power(HashTable* command_and_params)
{
    if ((this->state) == false)
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }

    else if ((this->state) == true)
    {
        digitalWrite(LED_BUILTIN, LOW);
    }

    this->state = !(this->state);
    return Result::Success("Changed state of onboard LED.");
}