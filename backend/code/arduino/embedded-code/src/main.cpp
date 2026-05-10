#include <Arduino.h>
#include "config.hpp"
#include "parser.hpp"
#include "hashStruct.hpp"
#include "arduinoController.hpp"

String input = "";

void setup()
{
  Serial.begin(9600);      // must match Python baud rate
  ArduinoController::setupHardware();
}

// Main program loop, commands are read from serial.
void loop()
{
    if (Serial.available() > 0)
    {
        String input = Serial.readStringUntil('\n');    // read full line
        HashTable* params = parseCommand(input);        // stores params passed through as a hashtable object

        ArduinoController ac;       // main controller that handles requests from server
        ac.handleCommand(params);   // command sent from Python is handled
    }
}