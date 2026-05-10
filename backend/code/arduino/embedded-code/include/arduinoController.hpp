#pragma once
#include <Arduino.h>
#include "hashStruct.hpp"
#include "led.hpp"

// enum table that stores links to classes, the class to
// use is determined through this enum
enum class HardwareClasses
{
    Led,
    NONE
};

class ArduinoController
{
    public:
        static void setupHardware();
        void handleCommand(HashTable* command_and_params);
        HardwareClasses getModuleClass(String& moduleString);
        ArduinoController();
    private:
        HashTable result;       // where results of operation are stored
        HashTable errors;       // if errors occur, information about them is stored here
        
        // size_t Hardware::getErrorCount();
};

// class hashTable
// {
//     private:

//         struct entry
//         {
//             String key;
//             String value;
//             entry* nextEntry;
//         };

//         hashTable::entry** initializeHashTable(size_t size) const;
//         entry* createEntry(const String& key, const String& value);

//     public:

//         entry** ht;
//         const size_t size;

//         size_t hash(const String& key) const;

//         void insert(const String& key, const String& value);
//         entry* get(const String& key);
//         String hashTable::getValue(const String& key);
//         entry* getByIndex(const size_t index);

//         ~hashTable();
//         hashTable(size_t size = Config::BASE_HASH_TABLE_SIZE);
// };