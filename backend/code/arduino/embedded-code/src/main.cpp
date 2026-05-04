#include <Arduino.h>

bool onBoardLedState = false;   // keeps track of the state of the on board led

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
      digitalWrite(LED_BUILTIN, onBoardLedState ? HIGH: LOW);
    }
    
    else
    {
      Serial.println("Unknown command: " + command);
    }
  }
}