#include <Arduino.h>
#include "config/config.hpp"
#include "HCSR04.h"
#include "utilities/parser.hpp"
#include "structures/HashTable.hpp"
#include "controller/ArduinoController.hpp"
#include "hardware-components/UltrasonicSensor.hpp"
#include "output/Result.hpp"

UltrasonicSensor us = UltrasonicSensor(Config::US_TRIG_PIN, Config::US_ECHO_PIN);    // sets up ultrasonic sensor
ArduinoController ac = ArduinoController(Config::RED_LED_PIN, Config::GREEN_LED_PIN, us);       // main controller that handles requests from server


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

    if ((millis() - ac.ultrasonicSensor.lastRead) >= 500)      // check is done every 0.5 seconds
    {
        ac.ultrasonicSensor.lastRead = millis();

        size_t dist = ac.ultrasonicSensor.getDistance();
        if (dist < 200)
        {
            ac.greenLed.on();
        }

        else
        {
            ac.greenLed.off();
        }
    }
}