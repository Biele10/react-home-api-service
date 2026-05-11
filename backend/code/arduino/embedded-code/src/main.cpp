#include <Arduino.h>
#include "config/config.hpp"
#include "utilities/parser.hpp"
#include "structures/HashTable.hpp"
#include "controller/ArduinoController.hpp"
#include "output/Result.hpp"

String input = "";
ArduinoController ac = ArduinoController(Config::RED_LED_PIN);       // main controller that handles requests from server

void setup()
{
  Serial.begin(9600);      // must match Python baud rate
  ac.setupHardware();
}

// Main program loop, commands are read from serial.
void loop()
{
    if (Serial.available() > 0)
    {
        String input = Serial.readStringUntil('\n');    // read full line
        HashTable* params = parseCommand(input);        // stores params passed through as a hashtable object

        Result result = ac.handleCommand(params);   // command sent from Python is handled, result is stored from here
    }
}