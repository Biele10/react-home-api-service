#include <Arduino.h>
#include "config.hpp"
#include "parser.hpp"
#include "hashStruct.hpp"
#include "hardware.hpp"

String input = "";

void setup()
{
  Serial.begin(9600);      // must match Python baud rate
  setupHardware();
}

// Main program loop, commands are read from serial.
void loop()
{
    if (Serial.available() > 0)
    {
        String input = Serial.readStringUntil('\n');    // read full line
        hashTable* params = parseCommand(input);
    }
}