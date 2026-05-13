#include <Arduino.h>
#include "config/config.hpp"
#include "structures/HashTable.hpp"

/**
 * Constructor that initializes all values.
 */
HashTable::HashTable(size_t size) : ht(initializeHashTable(size)), size(size)
{};

HashTable::entry** HashTable::initializeHashTable(size_t size) const
{
    return new entry*[size]();   // safely creates fixed array and initializes all values to nullptr
};

HashTable::entry* HashTable::createEntry(const String& key, const String& value)
{
    entry* e = new entry;
    e->key = key;
    e->value = value;
    e->nextEntry = nullptr;

    return e;
};

/**
 * Function that hashes the key to generate the key/values
 * place inside the hash table.
 */
size_t HashTable::hash(const String& key) const
{
    size_t hashKey = 0;
    for (size_t i=0; i < key.length(); i++)
    {
        hashKey = (hashKey * 31 + key[i]);
    }

    return hashKey % size;
};

/**
 * Deconstructor that clears up all memory being
 * used by the class.
 */
HashTable::~HashTable()
{
    for (size_t i = 0; i < size; i++)
    {
        entry* current = ht[i];

        while (current != nullptr)
        {
            entry* next = current->nextEntry;
            delete current;
            current = next;
        }
    }

    delete[] ht;
}

void HashTable::insert(const String& key, const String& value)
{
    entry* e = createEntry(key, value);
    const size_t hashKey = this->hash(key);

    if (this->ht[hashKey] == nullptr)       // no other key stored here
    {
        this->ht[hashKey] = e;
        return;
    }

    // another value already stored there, loop through linked list to find next empty node

    entry* next = this->ht[hashKey];
    while(next->nextEntry != nullptr)
    {
        if (next->key == key)
        {
            next->value = value;        // if keys match, value is just overwritten
            return;
        }

        next = next->nextEntry;
    }

    next->nextEntry = e;     // assigns the newly created entry
};

HashTable::entry* HashTable::get(const String& key)
{
    const size_t hashKey = this->hash(key);
    entry* fetchedEntry = this->ht[hashKey];

    while (fetchedEntry != nullptr && fetchedEntry->key != key)
    {
        fetchedEntry = fetchedEntry->nextEntry;
    }

    return fetchedEntry;        // if found, found entry returned, if not nullptr returned
};

String HashTable::getValue(const String& key)
{
    entry* e = HashTable::get(key);
    if (e == nullptr)
    {
        return "";      // indicates that key/value-pair does not exist
    }

    return e->value;
};

/**
 * Function that gets an item from the
 * hash table by a direct index number
 * rather than using a key.
 */
HashTable::entry* HashTable::getByIndex(const size_t index)
{
    return this->ht[index];     // if value there, entry is returned if not nullptr is
}