#include <iostream>
#include <vector>
#include <string>

#include "HashTable.h"

int main() {
    HashTable hashTable(20);

    hashTable.Add("Everest", "The highest mountain on Earth, height 8848 meters.");
    hashTable.Add("Kilimanjaro", "The highest mountain in Africa, height 5895 meters.");
    hashTable.Add("Kilimanjaro", "The highest mountain in Africa.");
    hashTable.Add("Elbrus", "The highest peak of the Caucasus and Russia, height 5642 meters.");
    hashTable.Add("K2", "The second highest mountain on Earth, height 8611 meters.");
    hashTable.Add("Denali", "The highest mountain in North America, height 6190 meters.");
    hashTable.Add("Aconcagua", "The highest mountain in South America, height 6961 meters.");
    hashTable.Add("Mont Blanc", "The highest mountain in Western Europe, height 4810 meters.");
    hashTable.Add("Vinson Massif", "The highest mountain in Antarctica, height 4892 meters.");


    std::cout << hashTable.Find("Everest") << std::endl;
    std::cout << hashTable.Find("Kilimanjaro") << std::endl;
    std::cout << hashTable.Find("Elbrus") << std::endl;

   

    hashTable.ShowTable();

    hashTable.Remove("Kilimanjaro");
   
    std::cout << hashTable.Find("Kilimanjaro") << std::endl;
    std::cout << hashTable.GetTableSize() << std::endl;

    return 0;
}