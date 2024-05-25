#include "LogicalFunctions.h"
#include "TruthTable.h"
#include "VeitchKarnoMap.h"
using namespace std;

int main() {

	/*(!a | b | c) & (a | !b | c) & (a | b | !c) & (!a | !b | c)*/
	/* (!a&!b&c)|(!a&b&!c)|(!a&b&c)|(a&b&!c)*/
	//LogicalFunctions A("(a&b&c)|(!a&b&c)|(a&!b&c)|(a&b&!c)|(!a&!b&c)");
	/*LogicalFunctions A("(a|b|c)&(!a|b|c)&(a|!b|c)&(a|b|!c)&(!a|!b|c)");*/
	LogicalFunctions A("(!a&!b&!c&!d)|(!a&!b&!c&d)|(!a&b&!c&!d)|(!a&b&!c&d)|(a&!b&!c&!d)|(a&!b&!c&d)");
	/*TruthTable B("(!a&!b&c)|(!a&b&!c)|(!a&b&c)|(a&b&!c)");*/

	/*VeitchKarnoMap Z("(a&b&c)|(!a&b&c)|(a&!b&c)|(a&b&!c)|(!a&!b&c)");*/
	/*VeitchKarnoMap Z("(!a&!b&c)|(!a&b&!c)|(!a&b&c)|(a&b&!c)");*/
	/*VeitchKarnoMap Z("(a|b|c)&(!a|b|c)&(a|!b|c)&(a|b|!c)&(!a|!b|c)");*/
	VeitchKarnoMap Z("(!a|!b|c|d)&(!a|b|!c|!d)&(!a|b|c|d)&(a|b|!c|d)");
	/*VeitchKarnoMap Z("(!a&!b&c)|(!a&b&!c)|(!a&b&c)|(a&b&!c)");*/
	A.Show();

	cout << "calculation method :" << '\n' << A.MinimizeByCalculationMethod() << endl;
	cout << "calculation-table method :" << '\n' << A.MinimizeByCalculationTableMethod() << endl;
	cout << "veitch-karno map:" << '\n' << Z.GetMinimization() << endl;

	TruthTable tab("!(a|b)~c");
	LogicalFunctions B(tab.GetSDNF());
	LogicalFunctions C(tab.GetSKNF());

	cout << "calculation method :" << '\n' << B.MinimizeByCalculationMethod() << endl;
	cout << "calculation-table method :" << '\n' << C.MinimizeByCalculationTableMethod() << endl;
	/*B.Show();*/
}