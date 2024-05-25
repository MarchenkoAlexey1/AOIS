#include "VeitchKarnoMap.h"

VeitchKarnoMap::VeitchKarnoMap(std::string formula)
{
	if (formula[2] == '&' || formula[3] == '&') search_value = 1;
	else search_value = 0;
	this->logical_formula = formula;
	TruthTable truth_table(formula);
	this->vertical_variables = truth_table.GetUniqueVars();
	for (int i = truth_table.GetUniqueVars().size() - 1; i > truth_table.GetUniqueVars().size() / 2 - 0.5; i--) {
		horizontal_variables = vertical_variables[i] + horizontal_variables;
		vertical_variables.pop_back();
	}
	for (int i = 0; i < horizontal_variables.size(); i++) {
		horizontal_vars.push_back(std::vector<bool>());
		for (int j = 0; j < pow(2, horizontal_variables.size()); j++) {
			horizontal_vars[i].push_back(0);
		}
	}
	for (int i = 0; i < vertical_variables.size(); i++) {
		vertical_vars.push_back(std::vector<bool>());
		for (int j = 0; j < pow(2, vertical_variables.size()); j++) {
			vertical_vars[i].push_back(0);
		}
	}
	
	for (int i = 0; i < horizontal_variables.size(); i++) {
		if (i > 0) {
			for (int j = i; j > 0; j--) {
				int counter = pow(2, i) - 1;
				for (int k = 0; k < pow(2, i); k++) {
					horizontal_vars[j][k] = horizontal_vars[j - 1][k];
					horizontal_vars[j][pow(2, i) + counter] = horizontal_vars[j - 1][k];
					counter--;
				}
			}
		}
		for (int j = 0; j < pow(2, i + 1); j++) {
			if (j + 1 <= pow(2, i)) horizontal_vars[0][j] = 0;
			else horizontal_vars[0][j] = 1;
		}
	}
	for (int i = 0; i < vertical_variables.size(); i++) {
		if (i > 0) {
			for (int j = i; j > 0; j--) {
				int counter = pow(2, i) - 1;
				for (int k = 0; k < pow(2, i); k++) {
					vertical_vars[j][k] = vertical_vars[j - 1][k];
					vertical_vars[j][pow(2, i) + counter] = vertical_vars[j - 1][k];
					counter--;
				}
			}
		}
		for (int j = 0; j < pow(2, i + 1); j++) {
			if (j + 1 <= pow(2, i)) vertical_vars[0][j] = 0;
			else vertical_vars[0][j] = 1;
		}
	}

	for (int i = 0; i < pow(2, vertical_variables.size()); i++) {
		veitch_karno_map.push_back(std::vector<bool>());
		improved_veitch_karno_map.push_back(std::vector<int>());
		for (int j = 0; j < pow(2, horizontal_variables.size()); j++) {
			std::vector<bool> buffer;
			for (int formula_size = 0; formula_size < vertical_variables.size(); formula_size++) buffer.push_back(vertical_vars[formula_size][i]);
			for (int formula_size = 0; formula_size < horizontal_variables.size(); formula_size++) buffer.push_back(horizontal_vars[formula_size][j]);
			veitch_karno_map[i].push_back(truth_table.GetResultByIndex(buffer));
			improved_veitch_karno_map[i].push_back(j + (i * pow(2, horizontal_variables.size())));
		}
	}
}

std::string VeitchKarnoMap::GetMinimization()
{
	std::string DNF;
	std::vector<std::vector<bool>> extension;
	std::vector<std::vector<int>> improved_extension;
	std::vector<std::vector<int>> minimization;
	for (int doubling = 0; doubling < 2; doubling++) {
		for (int i = 0; i < pow(2, vertical_variables.size()); i++) {
			extension.push_back(veitch_karno_map[i]);
			improved_extension.push_back(improved_veitch_karno_map[i]);
		}
	}
	for (int i = 0; i < pow(2, vertical_variables.size() + 1); i++) {
		for (int j = 0; j < pow(2, horizontal_variables.size()); j++) {
			int buffer = i;
			if (i > pow(2, vertical_variables.size()) - 1) buffer -= pow(2, vertical_variables.size());
			extension[i].push_back(veitch_karno_map[buffer][j]);
			improved_extension[i].push_back(improved_veitch_karno_map[buffer][j]);
		}
	}
	for (int i = 0; i < pow(2, vertical_variables.size() + 1); i++) {
		for (int j = 0; j < pow(2, horizontal_variables.size() + 1); j++) {
			if (extension[i][j] == search_value) {
				for (int rows_degree = 1; rows_degree <= pow(2, vertical_variables.size()); rows_degree *= 2) {
					for (int cols_degree = 1; cols_degree <= pow(2, horizontal_variables.size()); cols_degree *= 2) {
						std::vector<int> cluster;
						bool identificator = 1;
						for (int di = 0; di < rows_degree; di++) {
							for (int dj = 0; dj < cols_degree; dj++) {
								int ni = i + di;
								int nj = j + dj;
								if (!(ni >= 0 && ni < pow(2, vertical_variables.size() + 1) && nj >= 0 && nj < pow(2, horizontal_variables.size() + 1) && extension[ni][nj] == search_value)) {
									identificator = 0;
								}
							}
						}

						if (identificator == 1) {
							for (int di = 0; di < rows_degree; di++) {
								for (int dj = 0; dj < cols_degree; dj++) {
									int ni = i + di;
									int nj = j + dj;
									if (ni >= 0 && ni < pow(2, vertical_variables.size() + 1) && nj >= 0 && nj < pow(2, horizontal_variables.size() + 1) && extension[ni][nj] == search_value) {
										cluster.push_back(improved_extension[ni][nj]);
									}
								}
							}
							minimization.push_back(cluster);
						}
					}
				}
			}
		}
	}
	minimization = RemovingRepetitions(minimization);

	DNF = FormAFormula(minimization);
	return DNF;
}

std::vector<std::vector<int>> VeitchKarnoMap::RemovingRepetitions(std::vector<std::vector<int>> original)
{
	for (int i = 0; i < original.size(); i++) {
		for (int j = i + 1; j < original.size(); j++) {
			if (original[i] == original[j]) {
				original.erase(original.begin() + j);
				j--;
			}
		}
	}

	for (int i = 0; i < original.size(); i++) {
		bool deletion_contour = 1;
		for (int varsi = 0; varsi < original[i].size(); varsi++) {
			bool deletion_element = 0;
			for (int j = 0; j < original.size(); j++) {
				if (i != j) {
					for (int varsj = 0; varsj < original[j].size(); varsj++) {
						if (original[i][varsi] == original[j][varsj] && original[i].size() <= original[j].size()) deletion_element = 1;
					}
				}
			}
			if (deletion_element == 0) deletion_contour = 0;
		}
		if (deletion_contour == 1) {
			original.erase(original.begin() + i);
			i--;
		}
	}
	for (auto& cluster : original) {
		std::sort(cluster.begin(), cluster.end());
	}
	return original;
}

std::string VeitchKarnoMap::FormAFormula(std::vector<std::vector<int>> minimization)
{
	std::string formula;
	for (int i = 0; i < minimization.size(); i++) {
		formula += FormABlock(minimization[i]);
		if (search_value == 1) formula += '|';
		else formula += '&';
	}
	formula.pop_back();
	return formula;
}

std::string VeitchKarnoMap::FormABlock(std::vector<int> contur)
{
	std::string block;
	std::string variables;
	std::vector<std::vector<int>> additional_table;

	variables = vertical_variables + horizontal_variables;
	for (int i = 0; i < variables.size(); i++) additional_table.push_back(std::vector<int>());
	
	block += '(';
	for (int i = 0; i < contur.size(); i++) {
		for (int vertical = 0; vertical < vertical_vars[0].size(); vertical++) {
			for (int horizontal = 0; horizontal < horizontal_vars[0].size(); horizontal++) {
				if (improved_veitch_karno_map[vertical][horizontal] == contur[i]) {
					for (int vertical_letters = 0; vertical_letters < vertical_variables.size(); vertical_letters++) {
						additional_table[vertical_letters].push_back(vertical_vars[vertical_letters][vertical]);
					}
					for (int horizontal_letters = 0; horizontal_letters < horizontal_variables.size(); horizontal_letters++) {
						additional_table[vertical_variables.size() + horizontal_letters].push_back(horizontal_vars[horizontal_letters][horizontal]);
					}
				}
			}
		}
	}
	for (int i = 0; i < variables.size(); i++) {
		int summa = 0;
		for (int j = 0; j < additional_table[0].size(); j++) {
			summa += additional_table[i][j];
		}
		if (search_value == 1) {
			if (summa == additional_table[0].size()) {
				block += variables[i];
				if (search_value == 1) block += '&';
				else block += '|';
			}
			if (summa == 0) {
				block += '!';
				block += variables[i];
				if (search_value == 1) block += '&';
				else block += '|';
			}
		}
		else {
			if (summa == 0) {
				block += variables[i];
				if (search_value == 1) block += '&';
				else block += '|';
			}
			if (summa == additional_table[0].size()) {
				block += '!';
				block += variables[i];
				if (search_value == 1) block += '&';
				else block += '|';
			}
		}
	}
	block.pop_back();
	block += ')';
	return block;
}
