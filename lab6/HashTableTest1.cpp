#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab6\HashTable.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTest1
{
	TEST_CLASS(HashTableTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			HashTable hashTable(20);
			hashTable.Add("Everest", "The highest mountain on Earth, height 8848 meters.");
			hashTable.Add("Kilimanjaro", "The highest mountain in Africa, height 5895 meters.");
			Assert::IsTrue(hashTable.GetTableSize() == 2);
		}

	};
}
