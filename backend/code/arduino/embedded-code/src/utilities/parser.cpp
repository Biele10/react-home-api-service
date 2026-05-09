#include <Arduino.h>
#include "config.hpp"
#include "errorHandler.hpp"
#include <stdint.h>

// TO-DO:
// - Implement a hash table, not in this file but somewhere
// - Handle error for if array is too large, do something with error handler

void arrayExpander(String*& inputArray, size_t& originalSize)
{
  size_t newSize = originalSize + Config::DEFAULT_ARRAY_ADDITION;

  String* updatedArray = new String[newSize];    // creates new array with new fixed size on the heap

  for (size_t i = 0; i < originalSize; i++)
  {
    updatedArray[i] = inputArray[i];
  }

  delete[] inputArray;

  originalSize = newSize;
  inputArray = updatedArray;
}

// Function used to parse user input by & and =.
// String inputs looks roughly like so:

// type=adjust&module=LED&method=power&state=1&silent=0
String* parseCommand(const String& input)
{
  uint8_t arrayIndex = 0;

  // heap pointers
  size_t baseSize = Config::BASE_ARRAY_SIZE;
  String* valueArray = new String[Config::BASE_ARRAY_SIZE];

  String curValName;      // string that will be appended to to form param name

  for (size_t index = 0; index < input.length(); index++)
  {
    if (input[index] != '&')
    {
        curValName += input[index];     // appends char to string
        continue;
    }

    // & found, we now know that value of curValName is the full name of the command/param
    
    if (arrayIndex >= baseSize)    // array values has surpassed base amount, expand array
    {
      arrayExpander(valueArray, baseSize);
    }

    valueArray[arrayIndex++] = curValName;
    curValName = "";
  }

  return valueArray;
}