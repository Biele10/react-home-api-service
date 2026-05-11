#pragma once
#include <Arduino.h>
#include "structures/HashTable.hpp"
#include "hardware-components/Led.hpp"
#include "output/Result.hpp"

// enum table that stores links to classes, the class to
// use is determined through this enum
enum class HardwareClasses
{
    Led,
    NONE
};

class ArduinoController
{
    public:
        static void setupHardware();
        Result handleCommand(HashTable* command_and_params);
        HardwareClasses getModuleClass(String& moduleString);
        ArduinoController();
};