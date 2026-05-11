#include <Arduino.h>
#include "config/config.hpp"
#include "structures/HashTable.hpp"
#include "controller/ArduinoController.hpp"
#include "output/Result.hpp"

int redLED = Config::RED_LED_PIN;

/**
 * Constructor
 */
ArduinoController::ArduinoController(){};

/**
 * Ran in setup function, sets up
 * all different pieces of hardware.
 */
void ArduinoController::setupHardware()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(redLED, OUTPUT);   // sets up red LED
};

/**
 * Function that handles commands sent from server
 * and assigns them to the correct class and method.
 */
Result ArduinoController::handleCommand(HashTable* command_and_params)
{
  String module = command_and_params->getValue("module");
  if (module == "")
  {
    Result result = Result::Error(ErrorCode::INVALID_MODULE, )
    return;   // error, module has to be defined
  }

  HardwareClasses moduleClass = getModuleClass(module);
  if (moduleClass == HardwareClasses::NONE)
  {

    return;   // class doesn't exist
  }

};

/**
 * Gets class by module string.
 */
HardwareClasses ArduinoController::getModuleClass(String& moduleString)
{
  if (moduleString == "led")
  {
    return HardwareClasses::Led;
  }

  return HardwareClasses::NONE;   // no matching class found
};