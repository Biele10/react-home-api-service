#include <Arduino.h>
#include <stdint.h>
#include "config.hpp"

class hashTable
{
    private:

        /**
         * Structure for a hash table entry.
         */
        struct entry
        {
            String key;
            String value;
            entry* nextEntry;       // allows for a linked list
        };

        static const uint8_t size = Config::BASE_HASH_TABLE_SIZE;
        entry table[size];

        uint8_t hash(hashTable& ht, const String& key);
}

uint8_t hash(hashTable& ht, const String& key)
{
    uint8_t hash = 0;
    for (uint8_t i=0; i < key.length(); i++)
    {
        hash = (hash * 31 + key[i] % ht.size);
    }

    return hash;
}

void insert()