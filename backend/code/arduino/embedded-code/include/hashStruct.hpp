#pragma once
#include <Arduino.h>
#include "config.hpp"

class hashTable
{
    private:

        struct entry
        {
            String key;
            String value;
            entry* nextEntry;
        };

        hashTable::entry** initializeHashTable(size_t size) const;
        entry* createEntry(const String& key, const String& value);

    public:

        entry** ht;
        const size_t size;

        size_t hash(const String& key) const;

        void insert(const String& key, const String& value);
        entry* get(const String& key);
        entry* getByIndex(const size_t index);

        ~hashTable();
        hashTable(size_t size = Config::BASE_HASH_TABLE_SIZE);
};