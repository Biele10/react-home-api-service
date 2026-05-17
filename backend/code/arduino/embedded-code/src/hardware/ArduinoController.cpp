#include <Arduino.h>
#include "hardware-components/UltrasonicSensor.hpp"
#include "config/config.hpp"
#include "structures/HashTable.hpp"
#include "controller/ArduinoController.hpp"
#include "output/Result.hpp"

/**
 * Constructor
 */
ArduinoController::ArduinoController(int redLedPin, int greenLedPin, UltrasonicSensor& us) : redLed(redLedPin), greenLed(greenLedPin), onboardLed(), ultrasonicSensor(us) {}   // initialises all hardware being used and creates an object for each one

/**
 * Ran in setup function, sets up
 * all different pieces of hardware.
 */
void ArduinoController::setupHardware()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Config::RED_LED_PIN, OUTPUT);
  pinMode(Config::GREEN_LED_PIN, OUTPUT);
};

/**
 * Function that handles commands sent from server
 * and assigns them to the correct class and method.
 */
Result ArduinoController::handleCommand(HashTable* command_and_params)
{
  String module = command_and_params->getValue("module");   // fetches module to interact with
  if (module == "redLed")
  {
    return redLed.handler(command_and_params);
  }

  if (module == "onboardLed")
  {
    return onboardLed.handler(command_and_params);
  }

  return Result::Error(ErrorCode::MODULE_NOT_EXIST, "Module does not exist.");
};