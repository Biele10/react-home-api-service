#pragma once
#include <Arduino.h>
#include "hashStruct.hpp"
#include "led.hpp"

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
        void handleCommand(HashTable* command_and_params);
        HardwareClasses getModuleClass(String& moduleString);
        ArduinoController();
    private:
        HashTable result;       // where results of operation are stored
        HashTable errors;       // if errors occur, information about them is stored here
        
        // size_t Hardware::getErrorCount();
};