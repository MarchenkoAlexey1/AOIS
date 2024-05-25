#include "HashTable.h"

void HashTable::Add(std::string key, std::string value)
{
    int index = HashFunction(key);
    int originalIndex = index;
    bool collisionOccurred = false;

    while (table[index].isOccupied) {
        collisionOccurred = true;
        index = (index + 1) % table.size();
        if (index == originalIndex) {
            std::cout << "Hash table is full, unable to insert element!" << std::endl;
            return;
        }
    }

    if (collisionOccurred) {
        std::cout << "Collision occurred while inserting key: " << key << std::endl;
    }

    table[index].key = key;
    table[index].value = value;
    table[index].isOccupied = true;
}

void HashTable::Remove(std::string key)
{
    int index = HashFunction(key);
    int originalIndex = index;

    while (table[index].isOccupied) {
        if (table[index].key == key) {
            table[index].isOccupied = false;
            table[index].key = "";
            table[index].value = "";
            return;
        }
        index = (index + 1) % table.size();
        if (index == originalIndex) {
            break;
        }
    }

    std::cout << "Element with key " << key << " not found." << std::endl;
}

std::string HashTable::Find(std::string key)
{
    int index = HashFunction(key);
    int originalIndex = index;

    while (table[index].isOccupied) {
        if (table[index].key == key) {
            return table[index].value;
        }
        index = (index + 1) % table.size();
        if (index == originalIndex) {
            break;
        }
    }

    return "Element with key " + key + " not found.";
}

void HashTable::Replace(std::string key, std::string newValue)
{
    int index = HashFunction(key);
    int originalIndex = index;

    while (table[index].isOccupied) {
        if (table[index].key == key) {
            table[index].value = newValue;
            return;
        }
        index = (index + 1) % table.size();
        if (index == originalIndex) {
            std::cout << "Element with key " << key << " not found." << std::endl;
            return;
        }
    }

    std::cout << "Element with key " << key << " not found." << std::endl;
}

int HashTable::GetTableSize()
{
    int count = 0;
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].isOccupied) {
            count++;
        }
    }
    return count;
}

void HashTable::ShowTable()
{
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].isOccupied) {
            std::cout << "Index " << i << ": Key = " << table[i].key << ", Value = " << table[i].value << std::endl;
        }
        else {
            std::cout << "Index " << i << ": Empty" << std::endl;
        }
    }
}

int HashTable::HashFunction(std::string key)
{
    int hash = 0;
    for (char c : key) {
        hash += c;
        hash += c;
    }
    return hash % table.size();
}
