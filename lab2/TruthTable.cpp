#include "TruthTable.h"

TruthTable::TruthTable(std::string formula)
{
	std::string postfix_formula;
	std::stack<char> buffer;

	for (const char c : formula) {
		if (c >= 'a' && c <= 'z') postfix_formula += c;
		if (c == '(') buffer.push(c);
		if (c == '~' || c == '>' || c == '|' || c == '&' || c == '!') {
			if (buffer.empty() || Priority(buffer.top()) < Priority(c)) buffer.push(c);
			else {
				while (!(buffer.empty()) && Priority(buffer.top()) >= Priority(c)) {
					postfix_formula += buffer.top();
					buffer.pop();
				}
				buffer.push(c);
			}
		}
		if (c == ')') {
			while (buffer.top() != '(') {
				postfix_formula += buffer.top();
				buffer.pop();
			}
			buffer.pop();
		}
	}
	while (!(buffer.empty())) {
		postfix_formula += buffer.top();
		buffer.pop();
	}
	FillingOutTheTable(postfix_formula);
}

void TruthTable::FillingOutTheTable(std::string postfix_formula)
{
	unique_vars = postfix_formula;
	for (int i = 0; i < unique_vars.size(); i++) {
		for (int j = 1; j < unique_vars.size(); j++)
			if ((unique_vars[i] == unique_vars[j] && i != j) || !(unique_vars[j] >= 'a' && unique_vars[j] <= 'z')) {
				unique_vars.erase(j, 1);
				j--;
			}
	}
	for (int i = 0; i < unique_vars.size() + 1; i++) truth_table.push_back(std::vector<bool>());
	for (int i = 0; i < unique_vars.size(); i++) {
		int counter = 0;
		for (int j = 0; j < pow(2, unique_vars.size()); j++) {
			if (counter < pow(2, unique_vars.size() - i - 1)) {
				truth_table[i].push_back(0);
				counter++;
			}
			else if (counter < pow(2, unique_vars.size() - i)){
				truth_table[i].push_back(1);
				counter++;
			}
			else {
				truth_table[i].push_back(0);
				counter = 1;
			}
		}
	}

	for (int i = 0; i < pow(2, unique_vars.size()); i++) {
		std::stack<bool> solution;
		for (const char c : postfix_formula) {
			if (c >= 'a' && c <= 'z') {
				int num = 0;
				while (c != unique_vars[num]) num++;
				solution.push(truth_table[num][i]);
			}
			else {
				bool buffer = solution.top();
				solution.pop();
				switch (c) {
				case '!': 
					if (buffer == 0) solution.push(1);
					else solution.push(0);
					continue;
				case '&':
					if (buffer == 1 && solution.top() == 1)solution.top() = 1;
					else solution.top() = 0;
					continue;
				case '|':
					if (buffer == 1 || solution.top() == 1) solution.top() = 1;
					else solution.top() = 0;
					continue;
				case '>': 
					if (buffer == 0 && solution.top() == 1) solution.top() = 0;
					else solution.top() = 1;
					continue;
				case '~':
					if (buffer == solution.top())solution.top() = 1;
					else solution.top() = 0;
					continue;
				}
			}
		}
		truth_table[unique_vars.size()].push_back(solution.top());
	}
}

void TruthTable::ConstructionOfSDNFandSKNF()
{
	for (int i = 0; i < pow(2, unique_vars.size()); i++) {
		if (truth_table[unique_vars.size()][i] == 1) {
			SDNF += '(';
			for (int j = 0; j < unique_vars.size(); j++) {
				if (truth_table[j][i] == 0) SDNF = SDNF + '!' + unique_vars[j];
				else SDNF += unique_vars[j];
				if (j != unique_vars.size() - 1) SDNF += '&';
			}
			SDNF += ')';
			SDNF += '|';
		}
		else {
			SKNF += '(';
			for (int j = 0; j < unique_vars.size(); j++) {
				if (truth_table[j][i] == 1) SKNF = SKNF + '!' + unique_vars[j];
				else SKNF += unique_vars[j];
				if (j != unique_vars.size() - 1) SKNF += '|';
			}
			SKNF += ')';
			SKNF += '&';
		}

	}
	SDNF.pop_back();
	SKNF.pop_back();
	ShowNumericForm();
}

std::string TruthTable::GetSDNF()
{
	return SDNF;
}

std::string TruthTable::GetSKNF()
{
	return SKNF;
}

int TruthTable::GetIndexForm()
{
	int index = 0;

	for (int i = 0; i < pow(2, unique_vars.size()); i++) {
		std::cout << truth_table[unique_vars.size()][i];
		if (truth_table[unique_vars.size()][i] == 1) index += pow(2, i);
	}
	std::cout << '-';
	return index;
}

bool TruthTable::GetResult(int index)
{
	return truth_table[unique_vars.size()][index];
}

int TruthTable::Priority(char ch)
{
	switch (ch) {
	case '!': return 6;
	case '&': return 5;
	case '|': return 4;
	case '>': return 3;
	case '~': return 2;
	case '(': return 1;
	}
}

void TruthTable::Show()
{
	std::cout << std::endl;
	for (int j = 0; j < pow(2, unique_vars.size()); j++) {
		for (int i = 0; i < unique_vars.size() + 1; i++) {
			if (i == unique_vars.size()) std::cout << "|";
			std::cout << truth_table[i][j];
		}
		std::cout << std::endl;
	}
}

void TruthTable::ShowNumericForm()
{
	int buffer = 0;
	std::cout << std::endl << '(';
	for (int j = 0; j < pow(2, unique_vars.size()); j++) {
		if (truth_table[unique_vars.size()][j] == 0) {
			if (buffer > 0) std::cout << ',';
			std::cout << j;
			buffer++;
		}
	} 
	std::cout << ")&" << std::endl;
	buffer = 0;
	std::cout << '(';
	for (int j = 0; j < pow(2, unique_vars.size()); j++) {
		if (truth_table[unique_vars.size()][j] == 1) {
			if (buffer > 0) std::cout << ',';
			std::cout << j;
			buffer++;
		}
	}
	std::cout << ")|" << std::endl;
}
