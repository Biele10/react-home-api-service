#include <Arduino.h>
#include "config.hpp"
#include "errorHandler.hpp"
#include <stdint.h>

// TO-DO:
// - Implement a hash table, not in this file but somewhere
// - Handle error for if array is too large, do something with error handler

void arrayExpander(String*& inputArray, uint8_t& originalSize)
{
  if ((uint16_t)(originalSize + Config::BASE_ARRAY_SIZE) > 255)    // array is too large, we will return an error
  {
    inputArray = nullptr;   // sets to null ptr to let parser know that array is too large
    return;
  }

  uint8_t newSize = originalSize + Config::DEFAULT_ARRAY_ADDITION;    // updates size of array

  String* updatedArray = new String[newSize];    // creates new array with new fixed size on the heap

  for (uint8_t i = 0; i < originalSize; i++)
  {
    updatedArray[i] = inputArray[i];
  }

  delete[] inputArray;   // free old memory

  originalSize = newSize;  // updates original size
  inputArray = updatedArray; // replaces the old one array with new array values but maintains same pointer
}

// Function used to parse user input by & and =.
// String inputs looks roughly like so:

// type=adjust&module=LED&method=power&state=1&silent=0
String* parseCommand(const String& input)
{
  uint8_t arrayIndex = 0;   // keeps track of num of values to then add to array

  // heap pointers
  uint8_t baseSize = Config::BASE_ARRAY_SIZE;   // creates baseSize pointer, updated dynamically later on if array size needs to increase
  String* valueArray = new String[Config::BASE_ARRAY_SIZE];   // creates array that is moved onto heap

  String curValName;      // string that will be appended to to form param name

  for (int index = 0; index < input.length(); index++)
  {
    if (input[index] != '&')
    {
        curValName += input[index];     // appends char to string
        continue;
    }

    // & found, we now know that value of curValName is the full name of the command/param
    
    if (arrayIndex >= baseSize)    // array values has surpassed base amount, expand array
    {
      arrayExpander(valueArray, baseSize);      // expands the array size
    }

    valueArray[arrayIndex++] = curValName;
    curValName = "";  // empties the string
  }

  return valueArray;    // returns the array
}