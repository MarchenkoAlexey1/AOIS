#include "TableSearch.h"

std::vector<int> TableSearch::GetWordByIndex(int index)
{
	std::vector<int> word;
	for (int i = 0; i < 16; i++) {
		word.push_back(Matrix[(i + index) % 16][index]);
	}
	return word;
}

std::vector<int> TableSearch::GetAddressColumn(int index)
{
	std::vector<int> word;
	for (int i = 0; i < 16; i++) {
		word.push_back(Matrix[(i + index) % 16][i]);
	}
	return word;
}

void TableSearch::SetWordByIndex(std::vector<int> additional, int index)
{
	for (int i = 0; i < 16; i++) {
		Matrix[(i + index) % 16][index] = additional[i];
	}
}

std::vector<int> TableSearch::GetTheProhibitionOfTheSecond(std::vector<int> frst_wrd, std::vector<int> sec_wrd, int index)
{
	std::vector<int> result;
	for (int i = 0; i < 16; i++) {
		if (frst_wrd[i] == 0 && sec_wrd[i] == 1) result.push_back(1);
		else result.push_back(0);

		Matrix[(i + index) % 16][index] = result[i];
	}
	return result;
}

std::vector<int> TableSearch::GetImplicationFromTheSecondArgumentToTheFirst(std::vector<int> frst_wrd, std::vector<int> sec_wrd, int index)
{
	std::vector<int> result;
	for (int i = 0; i < 16; i++) {
		if (frst_wrd[i] == 0 && sec_wrd[i] == 1) result.push_back(0);
		else result.push_back(1);

		Matrix[(i + index) % 16][index] = result[i];
	}
	return result;
}

std::vector<int> TableSearch::GetNonequivalence(std::vector<int> frst_wrd, std::vector<int> sec_wrd, int index)
{
	std::vector<int> result;
	for (int i = 0; i < 16; i++) {
		if (frst_wrd[i] != sec_wrd[i]) result.push_back(1);
		else result.push_back(0);

		Matrix[(i + index) % 16][index] = result[i];
	}
	return result;
}

std::vector<int> TableSearch::GetEquivalence(std::vector<int> frst_wrd, std::vector<int> sec_wrd, int index)
{
	std::vector<int> result;
	for (int i = 0; i < 16; i++) {
		if (frst_wrd[i] == sec_wrd[i]) result.push_back(1);
		else result.push_back(0);

		Matrix[(i + index) % 16][index] = result[i];
	}
	return result;
}

void TableSearch::AddingFieldsByKey(std::string key)
{
	for (int i = 0; i < 16; i++) {
		int counter = 0;
		for (int k = 0; k < key.size(); k++) {
			if (key[k] - 48 == Matrix[(i + k) % 16][i])counter++;
		}
		if (key.size() == counter) {
			Matrix[(11 + i) % 16][i] = 0;
			for (int j = 0; j < 4; j++) {
				Matrix[(12 + i + j) % 16][i] = Matrix[(3 + i + j) % 16][i];
			}
			int buf = 0;
			for (int j = 4; j >= 0; j--) {
				if (buf == 1) {
					if (Matrix[(11 + i + j) % 16][i] == 1) {
						if (Matrix[(6 + i + j) % 16][i] == 1) {
							buf = 1;
							Matrix[(11 + i + j) % 16][i] = 1;
						}
						else {
							buf = 1;
							Matrix[(11 + i + j) % 16][i] = 0;
						}
					}
					else {
						if (Matrix[(6 + i + j) % 16][i] == 1) {
							buf = 1;
							Matrix[(11 + i + j) % 16][i] = 0;
						}
						else {
							buf = 0;
							Matrix[(11 + i + j) % 16][i] = 1;
						}
					}
				}
				else {
					if (Matrix[(11 + i + j) % 16][i] == 1) {
						if (Matrix[(6 + i + j) % 16][i] == 1) {
							buf = 1;
							Matrix[(11 + i + j) % 16][i] = 0;
						}
						else {
							buf = 0;
							Matrix[(11 + i + j) % 16][i] = 1;
						}
					}
					else {
						if (Matrix[(6 + i + j) % 16][i] == 1) {
							buf = 0;
							Matrix[(11 + i + j) % 16][i] = 1;
						}
						else {
							buf = 0;
							Matrix[(11 + i + j) % 16][i] = 0;
						}
					}
				}
			}
		}
	}
}

void TableSearch::Sort(bool func)
{
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 15; j++) {
			if (func == 1) {
				if (WordComparison(GetWordByIndex(j + 1), GetWordByIndex(j))) {
					std::vector<int> buffer;
					buffer = GetWordByIndex(j + 1);
					SetWordByIndex(GetWordByIndex(j), j + 1);
					SetWordByIndex(buffer, j);
				}
			}
			else {
				if (WordComparison(GetWordByIndex(j), GetWordByIndex(j + 1))) {
					std::vector<int> buffer;
					buffer = GetWordByIndex(j + 1);
					SetWordByIndex(GetWordByIndex(j), j + 1);
					SetWordByIndex(buffer, j);
				}
			}
			
		}
	}
}

bool TableSearch::WordComparison(std::vector<int> frst_wrd, std::vector<int> sec_wrd)
{
	for (int i = 0; i < 16; i++) {
		if (frst_wrd[i] == 1 && sec_wrd[i] == 0) return true;
		if (frst_wrd[i] == 0 && sec_wrd[i] == 1) return false;
	}
	return true;
}

void TableSearch::ShowWord(std::vector<int> word)
{
	std::cout << std::endl;
	for (int i = 0; i < 16; i++) {
		std::cout << word[i];
	}
	std::cout << std::endl;
}

void TableSearch::ShowTable()
{
	std::cout << std::endl;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			std::cout << Matrix[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
