#pragma once
#include <Arduino.h>
#include <stdint.h>
#include "hashStruct.hpp"

hashTable* parseCommand(const String& input);
void arrayExpander(String*& inputArray, size_t& originalSize);