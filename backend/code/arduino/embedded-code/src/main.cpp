#include <Arduino.h>
#include "config.hpp"
#include "parser.hpp"
#include "hashStruct.hpp"

bool onBoardLedState = false;   // keeps track of the state of the on board led
bool redLedState = false;
int redLED = Config::RED_LED_PIN;

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

String input = "";

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
        String input = Serial.readStringUntil('\n');  // read full line

        hashTable* ht = parseCommand(input);
        for (size_t i=0; i < ht->size; i++)
        {
          if (ht->getByIndex(i) == nullptr)
          {
            continue;
          }

          Serial.print("Index: ");
          Serial.println(i);
          Serial.print("Key: ");
          Serial.println(ht->getByIndex(i)->key);
          Serial.print("Value: ");
          Serial.println(ht->getByIndex(i)->value);
        }
    }
}