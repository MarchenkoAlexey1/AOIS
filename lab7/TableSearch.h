#pragma once

#include <iostream>
#include <vector>
#include <string>

class TableSearch
{
private:

    int Matrix[16][16] = {
       {1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
       {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0},
       {1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
       {1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0},
       {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1},
       {1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1},
       {0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0},
       {0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0},
       {1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
       {1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1},
       {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1},
       {1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0},
       {0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
       {1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
       {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
       {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}
    };

public:
    std::vector<int> GetWordByIndex(int index);
    std::vector<int> GetAddressColumn(int index);

    void SetWordByIndex(std::vector<int>, int index);
    
    std::vector<int> GetTheProhibitionOfTheSecond(std::vector<int> frst_wrd, std::vector<int> sec_wrd, int index);
    std::vector<int> GetImplicationFromTheSecondArgumentToTheFirst(std::vector<int> frst_wrd, std::vector<int> sec_wrd, int index);
    std::vector<int> GetNonequivalence(std::vector<int> frst_wrd, std::vector<int> sec_wrd, int index);
    std::vector<int> GetEquivalence(std::vector<int> frst_wrd, std::vector<int> sec_wrd, int index);
    
    void AddingFieldsByKey(std::string key);
    void Sort(bool func);

    bool WordComparison(std::vector<int> frst_wrd, std::vector<int> sec_wrd);

    void ShowWord(std::vector<int> word);
    void ShowTable();
};

