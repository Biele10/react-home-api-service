#include <Arduino.h>
#include "config.hpp"

// Function used to parse user input by & and =.
// String inputs looks roughly like so:

// type=adjust&module=LED&method=power&state=1&silent=0
void parseCommand(String input)
{
  int arrayIndex = 0;   // keeps track of num of values to then add to array
  String valueArray[Config::BASE_ARRAY_SIZE];   // sets default size

  String curValName;      // string that will be appended to to form param name

  for (int index = 0; index < input.length(); index++)
  {
    if (input[index] != '&')
    {
        curValName += input[index];     // appends char to string
        continue;
    }

    // & found, we now know that value of curValName is the full name of the command/param
    
    if (arrayIndex >= Config::BASE_ARRAY_SIZE)    // array values has surpassed base amount, expand array
    {
      int size = sizeof(valueArray) / sizeof(String);
      arrayExpander(valueArray, size);  // directly expands the array size
    }

    valueArray[arrayIndex] = curValName;


    curValName = "";  // empties the string
  }

}

void arrayExpander(String*& inputArray, int& size)
{
  int newSize = size + Config::DEFAULT_ARRAY_ADDITION;    // updates size of array

  String* tempArray = new String[newSize];

  for (int i = 0; i < size; i++)
  {
      tempArray[i] = inputArray[i];
  }

  delete[] inputArray;   // free old memory

  inputArray = tempArray; // update caller pointer
  size = newSize;
}
