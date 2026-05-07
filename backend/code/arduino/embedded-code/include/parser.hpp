#pragma once
#include <Arduino.h>
#include <stdint.h>

String* parseCommand(String input);
void arrayExpander(String*& inputArray, uint8_t*& originalSize);