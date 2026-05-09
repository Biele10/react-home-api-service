#include <Arduino.h>
#include <stdint.h>
#include "config.hpp"

class hashTable
{
    private:

        struct entry
        {
            String key;
            String value;
            entry* nextEntry;       // linked list
        };

        entry** initializeHashTable(size_t size) const
        {
            return new entry*[size]();   // safely creates fixed array and initializes all values to nullptr
        }

    public:

        entry** ht;     // hash table itself

        const size_t size;

        size_t hash(const String& key) const
        {
            size_t hashKey = 0;
            for (size_t i=0; i < key.length(); i++)
            {
                hashKey = (hashKey * 31 + key[i]);
            }

            return hashKey % size;
        }

        // void insert(String& key, String& value)
        // {
        //     const size_t hashKey = this->hash(key);
        // }

        hashTable(size_t size = Config::BASE_HASH_TABLE_SIZE) : size(size), ht(initializeHashTable(size))
        {}
};