#pragma once
#include<cmath>
using namespace std;

class BinaryNumber
{
protected:

	bool straight_form[16];
	bool reverse_form[16];
	bool additional_form[16];


	int number_of_significant_numbers = 0;

	const int last_number = 15;
	const int point_index = 10;

public:

	int GetLastNumberIndex();
	void ReceivingReverseForm();
	void ReceivingAdditionalForm();

	BinaryNumber();
	BinaryNumber(int number);
	BinaryNumber(const BinaryNumber&);
	void Copy(const BinaryNumber& other);

	void ShiftLeft(bool number);
	bool operator>= (const BinaryNumber& other);
	BinaryNumber& operator= (const BinaryNumber& other);
	BinaryNumber operator+ (const BinaryNumber& other);
	BinaryNumber operator* (const BinaryNumber& other);
	BinaryNumber operator- (const BinaryNumber& other);
	BinaryNumber operator/ (const BinaryNumber& other);

	bool GetStraightForm(int i);
	bool GetReverseForm(int i);
	bool GetAdditionalForm(int i);
	int GetStandartForm();
	float GetStandartFormForFloating();

	void SetStraightForm(int i, bool value);
};

