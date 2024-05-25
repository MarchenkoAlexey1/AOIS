#include <iostream>
#include <vector>
#include <string>

#include"..\lab6\Node.h"


class HashTable {

private:

    std::vector<Node> table;

    int HashFunction(std::string key);

public:

    HashTable(int size) : table(size) {}

    void Add(std::string key, std::string value);
    void Remove(std::string key);
    std::string Find(std::string key);
    void Replace(std::string key, std::string newValue);

    int GetTableSize();

    void ShowTable();
};