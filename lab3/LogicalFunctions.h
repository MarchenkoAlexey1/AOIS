#pragma once

#include <iostream>

#include "vector"
#include "string"

class LogicalFunctions
{
private:

	bool function_type;
	int number_of_blocks = 0;
	std::string unique_vars;

	std::string logical_formula;
	std::vector<std::vector<int>> logical_function;

public:

	LogicalFunctions(std::string formula);
	LogicalFunctions(const LogicalFunctions&);
	void Copying(const LogicalFunctions&);

	void RemovingRepetitions();
	bool MayStick();
	bool BlockWithinBlock(int external_index, std::vector<int> interior);
	std::string FormAFormula();
	std::string MinimizeByCalculationMethod();
	std::string MinimizeByCalculationTableMethod();

	void Show();
};

