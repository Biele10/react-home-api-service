#pragma once
#include <Arduino.h>
#include "structures/HashTable.hpp"

HashTable* parseCommand(const String& input);
void arrayExpander(String*& inputArray, size_t& originalSize);