#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <vector>

class TruthTable
{
private:
	std::vector<std::vector<bool>> truth_table;
	std::string unique_vars;
	std::string SDNF;
	std::string SKNF;

public:

	TruthTable(std::string formula);

	void FillingOutTheTable(std::string postfix_formula);
	void ConstructionOfSDNFandSKNF();

	std::string GetSDNF();
	std::string GetSKNF();
	int GetIndexForm();
	bool GetResult(int index);

	int Priority(char ch);

	void Show();
	void ShowNumericForm();
};

