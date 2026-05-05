#include <Arduino.h>
#include "config.hpp"

bool onBoardLedState = false;   // keeps track of the state of the on board led
bool redLedState = false;
int redLED = Config::RED_LED_PIN;

// Function used to parse user input by & and =.
// String inputs looks roughly like so:

// type=adjust&module=LED&method=power&state=1&silent=0
void parseCommand(String input)
{
  while (input.length() > 0)
  {
    int ampIndex = input.indexOf('&');
    String pair;

    if (ampIndex == -1)
    {
      pair = input;
      input = "";
    }

    else
    {
      pair = input.substring(0, ampIndex);
      input = input.substring(ampIndex + 1);
    }

    int eqIndex = pair.indexOf('=');
    if (eqIndex == -1) continue;

    String key = pair.substring(0, eqIndex);
    String value = pair.substring(eqIndex + 1);

    if (key == "module" && value == "LED")
    {
      // do something with values
    }
  }
}

// ---- blink helper ----
void blinkLED()
{
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}

void setup()
{
  Serial.begin(9600);      // must match Python baud rate
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(redLED, OUTPUT);   // sets up red LED
}

// Main program loop, commands are read from serial.
void loop()
{
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');  // read one line
    command.trim(); // remove whitespace / newline

    if (command == "LED_ON")
    {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("LED turned ON");
    } 
    else if (command == "LED_OFF")
    {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("LED turned OFF");
    }
    else if (command == "BLINK")
    {
      blinkLED();
    }

    else if (command == "onBoardLedPower")
    {
      onBoardLedState = !onBoardLedState;   // flips values
      digitalWrite(LED_BUILTIN, onBoardLedState ? HIGH : LOW);
    }

    else if (command == "LED")    // updates RED led
    {
      redLedState = !redLedState;
      digitalWrite(redLED, redLedState ? HIGH : LOW);
    }
    
    else
    {
      Serial.println("Unknown command: " + command);
    }
  }
}