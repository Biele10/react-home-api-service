#include <Arduino.h>
#include "config.hpp"
#include "hashStruct.hpp"

int redLED = Config::RED_LED_PIN;

/**
 * Ran in setup function, sets up
 * all different pieces of hardware.
 */
void setupHardware()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(redLED, OUTPUT);   // sets up red LED
};

/**
 * Function that handles commands sent from server
 * and assigns them to the correct class and method.
 */
void handleCommand(hashTable* command_and_params)
{
}