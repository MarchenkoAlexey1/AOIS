#include "pch.h"
#include "CppUnitTest.h"
#include "..\laba6\HashTable.h"
#include "..\laba6\HashTable.cpp"
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

		TEST_METHOD(TestMethod2)
		{
			HashTable hashTable(20);
			hashTable.Add("Everest", "The highest mountain on Earth, height 8848 meters.");
			hashTable.Add("Kilimanjaro", "The highest mountain in Africa, height 5895 meters.");
			hashTable.Add("Mont Blanc", "The highest mountain in Western Europe, height 4810 meters.");
			hashTable.Add("Vinson Massif", "The highest mountain in Antarctica, height 4892 meters.");
			hashTable.Remove("Kilimanjaro");
			Assert::IsTrue(hashTable.GetTableSize() == 3);
		}

		TEST_METHOD(TestMethod3)
		{
			HashTable hashTable(20);
			hashTable.Add("Everest", "The highest mountain on Earth, height 8848 meters.");
			hashTable.Add("Kilimanjaro", "The highest mountain in Africa, height 5895 meters.");
			hashTable.Add("Elbrus", "The highest peak of the Caucasus and Russia, height 5642 meters.");
			Assert::IsTrue(hashTable.Find("Kilimanjaro") == "The highest mountain in Africa, height 5895 meters.");
			hashTable.Remove("Kilimanjaro");
			Assert::IsTrue(hashTable.Find("Kilimanjaro") == "Element with key Kilimanjaro not found.");
		}

		TEST_METHOD(TestMethod4)
		{
			HashTable hashTable(20);
			hashTable.Add("Everest", "The highest mountain on Earth, height 8848 meters.");
			hashTable.Add("Kilimanjaro", "The highest mountain in Africa, height 5895 meters.");
			hashTable.Add("Kilimanjaro", "The highest mountain in Africa.");
			hashTable.Add("Elbrus", "The highest peak of the Caucasus and Russia, height 5642 meters.");
			hashTable.Add("K2", "The second highest mountain on Earth, height 8611 meters.");
			hashTable.Add("Denali", "The highest mountain in North America, height 6190 meters.");
			hashTable.Add("Aconcagua", "The highest mountain in South America, height 6961 meters.");
			hashTable.Add("Mont Blanc", "The highest mountain in Western Europe, height 4810 meters.");
			hashTable.Add("Vinson Massif", "The highest mountain in Antarctica, height 4892 meters.");

			hashTable.Replace("K2", "Mountain");

			Assert::IsTrue(hashTable.Find("K2") == "Mountain");
		}
	};
}
