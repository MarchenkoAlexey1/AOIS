#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab3\TruthTable.h"
#include "..\lab3\TruthTable.cpp"
#include "..\lab3\LogicalFunctions.h"
#include "..\lab3\LogicalFunctions.cpp"
#include "..\lab3\VeitchKarnoMap.h"
#include "..\lab3\VeitchKarnoMap.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MinimizationTest1
{
	TEST_CLASS(MinimizationTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			LogicalFunctions A("(!a&!b&!c&!d)|(!a&!b&!c&d)|(!a&b&!c&!d)|(!a&b&!c&d)|(a&!b&!c&!d)|(a&!b&!c&d)");
			Assert::IsTrue(A.MinimizeByCalculationMethod() == "(!a&!c)");
		}

		TEST_METHOD(TestMethod2)
		{
			LogicalFunctions A("(!a&!b&c)|(!a&b&!c)|(!a&b&c)|(a&b&!c)");
			Assert::IsTrue(A.MinimizeByCalculationTableMethod() == "(!a&c)|(b&!c)");
		}

		TEST_METHOD(TestMethod3)
		{
			VeitchKarnoMap Z("(!a|!b|c|d)&(!a|b|!c|!d)&(!a|b|c|d)&(a|b|!c|d)");
			Assert::IsTrue(Z.GetMinimization() == "(a|b|!c|d)&(!a|c|d)&(!a|b|!c|!d)");
		}

		TEST_METHOD(TestMethod4)
		{
			VeitchKarnoMap Z("(a|b|c)&(!a|b|c)&(a|!b|c)&(a|b|!c)&(!a|!b|c)");
			LogicalFunctions A("(a|b|c)&(!a|b|c)&(a|!b|c)&(a|b|!c)&(!a|!b|c)");
			Assert::IsTrue(A.MinimizeByCalculationMethod() == "(c)&(a|b)");
			Assert::IsTrue(A.MinimizeByCalculationTableMethod() == "(c)&(a|b)");
			Assert::IsTrue(Z.GetMinimization() == "(a|b)&(c)");
		}

		TEST_METHOD(TestMethod5)
		{
			TruthTable A("!(a|b)~c");
			LogicalFunctions B(A.GetSDNF());
			LogicalFunctions C(A.GetSKNF());
			Assert::IsTrue(B.MinimizeByCalculationMethod() == "(b&!c)|(a&!c)|(!a&!b&c)");
			Assert::IsTrue(C.MinimizeByCalculationMethod() == "(!b|!c)&(!a|!c)&(a|b|c)");
		}

	};
}
