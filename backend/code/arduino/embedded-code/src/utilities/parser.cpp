#include <Arduino.h>
#include "config/config.hpp"
#include "utilities/errorHandler.hpp"
#include "structures/HashTable.hpp"

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
HashTable* parseCommand(const String& input)
{
  String currentKey;
  String currentValue;

  HashTable* ht = new HashTable();    // creates hash table object which we will store items in

  String curValName;      // string that will be appended to either currentKey or currentValue

  for (size_t index = 0; index < input.length(); index++)
  {
    if (input[index] == Config::PARSER_VALUE_ASSIGNATION)    // we have dealt with a key
    {
      currentKey = curValName;
      curValName = "";
      continue;
    }

    else if (input[index] == Config::PARSER_SEPARATOR && currentKey != "")   // we have dealt with value, now we have both key and value we can assign to hash table
    {
      currentValue = curValName;
      ht->insert(currentKey, currentValue);   // adds new entry to the hash table

      curValName = currentValue = currentKey = "";   // reset all values
      continue;
    }

    curValName += input[index];     // appends char to string
  }

  // accounts for last value
  if (currentKey.length() > 0 && curValName.length() > 0)
  {
    ht->insert(currentKey, curValName);
  }

  return ht;
}