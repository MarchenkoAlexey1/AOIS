#pragma once

#include <iostream>
#include <algorithm>

#include "vector"
#include "string"

#include "TruthTable.h"

class VeitchKarnoMap
{
private:
	std::vector<std::vector<bool>> veitch_karno_map;
	std::vector<std::vector<int>> improved_veitch_karno_map;
	std::string horizontal_variables;
	std::string vertical_variables;
	std::vector<std::vector<bool>> horizontal_vars;
	std::vector<std::vector<bool>> vertical_vars;

	bool search_value;
	std::string logical_formula;

public:

	VeitchKarnoMap(std::string formula);
	std::string GetMinimization();
	std::vector<std::vector<int>> RemovingRepetitions(std::vector<std::vector<int>> original);
	std::string FormAFormula(std::vector<std::vector<int>> minimization);
	std::string FormABlock(std::vector<int>);
};

