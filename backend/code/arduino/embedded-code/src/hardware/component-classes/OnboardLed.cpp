#include <Arduino.h>
#include "hardware-components/OnboardLed.hpp"
#include "output/Result.hpp"
#include "structures/HashTable.hpp"
#include "config/config.hpp"

OnboardLed::OnboardLed(bool initialState) : state(initialState) {};

Result OnboardLed::power(uint16_t* args, uint8_t count)
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