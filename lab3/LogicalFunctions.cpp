#include "LogicalFunctions.h"
#include "TruthTable.h"

LogicalFunctions::LogicalFunctions(std::string formula)
{
	if (formula[2] == '&' || formula[3] == '&') function_type = 1;
	else function_type = 0;

	logical_formula = formula;
	unique_vars = formula;
	for (int i = 0; i < unique_vars.size(); i++) {
		for (int j = 0; j < unique_vars.size(); j++)
			if ((unique_vars[i] == unique_vars[j] && i != j) || !(unique_vars[j] >= 'a' && unique_vars[j] <= 'z')) {
				unique_vars.erase(j, 1);
				j--;
			}
	}
	for (int i = 0; i < formula.size(); i++) {
		if (formula[i] == '(') number_of_blocks++;
	}
	for (int i = 0; i < number_of_blocks; i++) logical_function.push_back(std::vector<int>());

	int block = 0;
	for (int i = 0; i < formula.size(); i++) {
		if (formula[i] == '(') {
			i++;
			for (int j = 0; j < formula.size(); j++) {
				if ((formula[i + j] >= 'a' && formula[i + j] <= 'z') && formula[i + j - 1] == '!') {
					logical_function[block].push_back(0);
				}
				else if (formula[i + j] >= 'a' && formula[i + j] <= 'z') {
					logical_function[block].push_back(1);
				}
				if (formula[i + j] == ')') break;
			}
			block++;
		}
	}
}

LogicalFunctions::LogicalFunctions(const LogicalFunctions&other)
{
	this->logical_formula = other.logical_formula;
	this->unique_vars = other.unique_vars;
	this->number_of_blocks = pow(2, unique_vars.size());
	for (int i = 0; i < this->number_of_blocks; i++) logical_function.push_back(std::vector<int>());
	this->number_of_blocks = 0;
	this->function_type = other.function_type;
}

void LogicalFunctions::Copying(const LogicalFunctions&other)
{
	this->logical_formula = other.logical_formula;
	this->unique_vars = other.unique_vars;
	this->number_of_blocks = other.number_of_blocks;
	this->logical_function = other.logical_function;
	this->function_type = other.function_type;
}

void LogicalFunctions::RemovingRepetitions()
{
	for (int i = 0; i < this->number_of_blocks - 1; i++) {
		for (int j = i + 1; j < this->number_of_blocks; j++) {
			int counter = 0;
			for (int value = 0; value < this->unique_vars.size(); value++) {
				if (this->logical_function[i][value] == this->logical_function[j][value]) counter++;
			}
			if (counter == this->unique_vars.size()) {
				this->logical_function.erase(logical_function.begin() + j - 1);
				number_of_blocks--;
			}
		}
	}
}

bool LogicalFunctions::MayStick()
{
	int sklei = 0;
	int neravn = 0;
	for (int i = 0; i < this->number_of_blocks - 1; i++) {
		for (int j = i + 1; j < this->number_of_blocks; j++) {
			int index = 0;
			for (int value = 0; value < this->unique_vars.size(); value++) {
				if ((this->logical_function[i][value] + this->logical_function[j][value]) == 1) {
					sklei++;
					index = value;
				}
				if (this->logical_function[i][value] != this->logical_function[j][value]) neravn++;
			}
			if (sklei == 1 && neravn == 1) return true;
			sklei = 0;
			neravn = 0;
		}
	}
	return false;
}

bool LogicalFunctions::BlockWithinBlock(int external_index, std::vector<int> interior)
{
	int include = true;

	for (int i = 0; i < unique_vars.size(); i++) {
		if (interior[i] != 2) {
			if (logical_function[external_index][i] != interior[i]) include = false;
		}
	}
	return include;
}

std::string LogicalFunctions::FormAFormula()
{
	char blocks;
	char connection;
	/*if (logical_formula[2] == '&' || logical_formula[3] == '&') {
		blocks = '&';
		connection = '|';
	}
	else {
		blocks = '|';
		connection = '&';
	}*/
	if (function_type == 1) {
		blocks = '&';
		connection = '|';
	}
	else {
		blocks = '|';
		connection = '&';
	}
	std::string formula;

	for (int j = 0; j < number_of_blocks; j++) {
		formula += '(';
		for (int i = 0; i < unique_vars.size(); i++) {
			if (logical_function[j][i] == 2) {
				continue;
			}
			else {
				if (logical_function[j][i] == 0) formula += '!';
				formula += unique_vars[i];
				formula += blocks;
			}
		}
		formula.pop_back();
		if (formula.back() != '|') {
			formula += ')';
			formula += connection;
		}
	}
	formula.pop_back();
	logical_formula = formula;
	return formula;
}

std::string LogicalFunctions::MinimizeByCalculationMethod()
{
	std::string DNF;
	LogicalFunctions buf(logical_formula);

	while (buf.MayStick())
	{
		LogicalFunctions buffer(buf);
		int sklei = 0;
		int neravn = 0;
		std::vector<bool> using_blocks;

		for (int i = 0; i < buf.number_of_blocks; i++) using_blocks.push_back(0);
		for (int i = 0; i < buf.number_of_blocks - 1; i++) {
			for (int j = i + 1; j < buf.number_of_blocks; j++) {
				int index = 0;
				for (int value = 0; value < buf.unique_vars.size(); value++) {
					if ((buf.logical_function[i][value] + buf.logical_function[j][value]) == 1) {
						sklei++;
						index = value;
					}
					if (buf.logical_function[i][value] != buf.logical_function[j][value]) neravn++;
				}
				if (sklei == 1 && neravn == 1) {
					for (int value = 0; value < buf.unique_vars.size(); value++) {
						buffer.logical_function[buffer.number_of_blocks].push_back(buf.logical_function[i][value]);
					}
					buffer.logical_function[buffer.number_of_blocks][index] = 2;
					buffer.number_of_blocks++;
					using_blocks[j] = 1;
					using_blocks[i] = 1;
				}
				sklei = 0;
				neravn = 0;
			}

		}
		buffer.RemovingRepetitions();
		for (int i = 0; i < buf.number_of_blocks; i++) {
			if (using_blocks[i] == 0) {
				for (int value = 0; value < buf.unique_vars.size(); value++) {
					buffer.logical_function[buffer.number_of_blocks].push_back(buf.logical_function[i][value]);
				}
				buffer.number_of_blocks++;
			}
		}
		DNF = buffer.FormAFormula();
		buf.Copying(buffer);

		if (!(buf.MayStick())) {

			TruthTable original_formula(buf.logical_formula);
			int number_of_original_units = original_formula.GetNumberOfUnits();
			int number_of_original_zeros = original_formula.GetNumberOfZeros();

			for (int i = 0; i < buf.number_of_blocks; i++) {
				LogicalFunctions additional("(a&b)");
				additional.Copying(buf);
				additional.logical_function.erase(additional.logical_function.begin() + i);
				additional.number_of_blocks--;
				additional.FormAFormula();
				TruthTable additional_formula(additional.logical_formula);
				int number_of_units = additional_formula.GetNumberOfUnits();
				int number_of_zeros = additional_formula.GetNumberOfZeros();

				if (number_of_original_units == number_of_units && number_of_original_zeros == number_of_zeros) {
					buffer.logical_function.erase(buffer.logical_function.begin() + i);
					buffer.number_of_blocks--;
					buffer.FormAFormula();
				}
			}
			DNF = buffer.FormAFormula();
			buf.Copying(buffer);
		}
	}
	return DNF;
}

std::string LogicalFunctions::MinimizeByCalculationTableMethod()
{
	std::string DNF;
	LogicalFunctions buf(logical_formula);

	while (buf.MayStick())
	{
		LogicalFunctions buffer(buf);
		int sklei = 0;
		int neravn = 0;
		std::vector<bool> using_blocks;

		for (int i = 0; i < buf.number_of_blocks; i++) using_blocks.push_back(0);
		for (int i = 0; i < buf.number_of_blocks - 1; i++) {
			for (int j = i + 1; j < buf.number_of_blocks; j++) {
				int index = 0;
				for (int value = 0; value < buf.unique_vars.size(); value++) {
					if ((buf.logical_function[i][value] + buf.logical_function[j][value]) == 1) {
						sklei++;
						index = value;
					}
					if (buf.logical_function[i][value] != buf.logical_function[j][value]) neravn++;
				}
				if (sklei == 1 && neravn == 1) {
					for (int value = 0; value < buf.unique_vars.size(); value++) {
						buffer.logical_function[buffer.number_of_blocks].push_back(buf.logical_function[i][value]);
					}
					buffer.logical_function[buffer.number_of_blocks][index] = 2;
					buffer.number_of_blocks++;
					using_blocks[j] = 1;
					using_blocks[i] = 1;
				}
				sklei = 0;
				neravn = 0;
			}

		}
		buffer.RemovingRepetitions();
		for (int i = 0; i < buf.number_of_blocks; i++) {
			if (using_blocks[i] == 0) {
				for (int value = 0; value < buf.unique_vars.size(); value++) {
					buffer.logical_function[buffer.number_of_blocks].push_back(buf.logical_function[i][value]);
				}
				buffer.number_of_blocks++;
			}
		}
		DNF = buffer.FormAFormula();
		buf.Copying(buffer);

		if (!(buf.MayStick())) {

			std::vector<std::vector<bool>> table_for_removing;
			for (int i = 0; i < buffer.number_of_blocks; i++) table_for_removing.push_back(std::vector<bool>());
			for (int i = 0; i < buffer.number_of_blocks; i++) {
				for (int j = 0; j < this->number_of_blocks; j++) {
					if (this->BlockWithinBlock(j, buffer.logical_function[i])) table_for_removing[i].push_back(1);
					else table_for_removing[i].push_back(0);
				}
			}

			std::vector<int> removing_array;
			for (int j = 0; j < this->number_of_blocks; j++) {
				removing_array.push_back(0);
				for (int i = 0; i < buffer.number_of_blocks; i++) {
					if (table_for_removing[i][j] == 1)  removing_array[j]++;
				}
			}

			for (int i = 0; i < this->number_of_blocks; i++) {
				if (removing_array[i] == 1) {
					for (int j = 0; j < buffer.number_of_blocks; j++) {
						if (table_for_removing[j][i] == 1) table_for_removing[j][0] = 1;
					}
				}
			}

			for (int i = buffer.number_of_blocks - 1; i >= 0; i--) {
				if (table_for_removing[i][0] == 0) {
					buffer.logical_function.erase(buffer.logical_function.begin() + i);
					buffer.number_of_blocks--;
					buffer.FormAFormula();
				}
			}

			DNF = buffer.FormAFormula();
			buf.Copying(buffer);
		}
	}
	return DNF;
}

void LogicalFunctions::Show()
{	
	/*logical_function.erase(logical_function.begin() + 2);
	number_of_blocks--;*/

	std::string buffer = FormAFormula();
	std::cout << '\n' << number_of_blocks << std::endl;
	std::cout << unique_vars << std::endl;
	std::cout << logical_formula << std::endl;
	std::cout << buffer << std::endl;
	for (int j = 0; j < number_of_blocks; j++) {
		for (int i = 0; i < unique_vars.size(); i++) {
			std::cout << logical_function[j][i];
		}
		std::cout << std::endl;
	}
}
