#include <iostream>
#include <vector>
#include <string>

#include"TableSearch.h"

int main() {
    int ind = 3;
    TableSearch A;
    A.ShowWord(A.GetWordByIndex(ind));
    A.ShowWord(A.GetAddressColumn(ind));
    A.ShowWord(A.GetTheProhibitionOfTheSecond(A.GetWordByIndex(ind), A.GetAddressColumn(ind), 15));
    A.ShowWord(A.GetImplicationFromTheSecondArgumentToTheFirst(A.GetWordByIndex(ind), A.GetAddressColumn(ind), 14));

    A.ShowWord(A.GetEquivalence(A.GetWordByIndex(7), A.GetAddressColumn(9), 15));
    A.ShowWord(A.GetNonequivalence(A.GetWordByIndex(7), A.GetAddressColumn(9), 14));
    A.ShowTable();
    
    A.ShowTable();
    A.Sort(1);
    A.AddingFieldsByKey("111");

    std::cout << "After sort:" << std::endl;

    A.ShowTable();
    return 0;
}