#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab1\BinNumbFloatingPoint.h"
#include "..\lab1\BinaryNumber.cpp"
#include "..\lab1\BinNumbFloatingPoint.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryNumberTests
{
	TEST_CLASS(BinaryNumberTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BinaryNumber x(10);
			BinaryNumber y(2);
			BinaryNumber a(x + y);
			Assert::IsTrue(a.GetStandartForm() == 12);
		}

		TEST_METHOD(TestMethod2)
		{
			BinaryNumber x(23);
			BinaryNumber y(7);
			BinaryNumber b(x - y);
			Assert::IsTrue(b.GetStandartForm() == 16);
		}

		TEST_METHOD(TestMethod3)
		{
			BinaryNumber x(3);
			BinaryNumber y(14);
			BinaryNumber c(x * y);
			Assert::IsTrue(c.GetStandartForm() == 42);
		}

		TEST_METHOD(TestMethod4)
		{
			BinaryNumber x(13);
			BinaryNumber y(3);
			BinaryNumber d(x / y);
			Assert::IsTrue(d.GetStandartFormForFloating() == 4.3125);
		}

		TEST_METHOD(TestMethod5)
		{
			BinNumbFloatingPoint A(4.75);
			BinNumbFloatingPoint B(12.625);
			BinNumbFloatingPoint C(A + B);
			Assert::IsTrue(C.GetStandartForm() == 17.375);
		}
	};
}
