#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab2\TruthTable.h"
#include "..\lab2\TruthTable.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TruthTableTests
{
	TEST_CLASS(TruthTableTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			TruthTable A("a~!a");
			Assert::IsTrue(A.GetIndexForm() == 0);
			Assert::IsTrue(A.GetResult(0) == 0);
			Assert::IsTrue(A.GetResult(1) == 0);
		}

		TEST_METHOD(TestMethod2)
		{
			TruthTable A("(a>b)&a");
			A.ConstructionOfSDNFandSKNF();
			Assert::IsTrue(A.GetSDNF() == "(a&!b)|(a&b)");
			Assert::IsTrue(A.GetSKNF() == "(a|b)&(a|!b)");
		}

		TEST_METHOD(TestMethod3)
		{
			TruthTable A("!a&(b|c)");
			A.ConstructionOfSDNFandSKNF();
			Assert::IsTrue(A.GetIndexForm() == 14);
		}
	};
}
