#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab7\TableSearch.h"
#include "..\lab7\TableSearch.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AutomatTest1
{
	TEST_CLASS(AutomatTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			TableSearch A;
			std::vector<int> prov = { 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };
			Assert::IsTrue(A.GetWordByIndex(1) == prov);
		}

		TEST_METHOD(TestMethod2)
		{
			TableSearch A;
			std::vector<int> prov = { 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0 };
			Assert::IsTrue(A.GetAddressColumn(3) == prov);
		}

		TEST_METHOD(TestMethod3)
		{
			TableSearch A;
			std::vector<int> prov = { 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };
			A.SetWordByIndex(prov, 4);
			Assert::IsTrue(A.GetWordByIndex(4) == prov);
		}

		TEST_METHOD(TestMethod4)
		{
			TableSearch A;
			std::vector<int> prov1 = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
			std::vector<int> prov2 = { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 };
			Assert::IsTrue(A.GetTheProhibitionOfTheSecond(A.GetWordByIndex(4), A.GetAddressColumn(6), 15) == prov1);
			Assert::IsTrue(A.GetImplicationFromTheSecondArgumentToTheFirst(A.GetWordByIndex(4), A.GetAddressColumn(6), 15) == prov2);
		}

		TEST_METHOD(TestMethod5)
		{
			TableSearch A;
			std::vector<int> prov1 = { 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1 };
			std::vector<int> prov2 = { 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1 };
			Assert::IsTrue(A.GetEquivalence(A.GetWordByIndex(7), A.GetAddressColumn(9), 15) == prov1);
			Assert::IsTrue(A.GetNonequivalence(A.GetWordByIndex(7), A.GetAddressColumn(9), 15) == prov2);
		}

		TEST_METHOD(TestMethod6)
		{
			TableSearch A;
			std::vector<int> prov = { 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1 };
			A.Sort(1);
			Assert::IsTrue(A.GetWordByIndex(0) == prov);
		}

		TEST_METHOD(TestMethod7)
		{
			TableSearch A;
			std::vector<int> prov1 = { 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1 };
			std::vector<int> prov2 = { 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0 };
			A.Sort(1);
			Assert::IsTrue(A.GetWordByIndex(0) == prov1);
			A.AddingFieldsByKey("111");
			Assert::IsTrue(A.GetWordByIndex(0) == prov2);

		}
	};
}
