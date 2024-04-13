#pragma once

#include"BinaryNumber.h"

class BinNumbFloatingPoint
{
	bool straight_form[32];
	bool availability_of_unit = 0;

	const int last_exp_number = 8;
	const int last_mant_number = 31;

public:
	BinNumbFloatingPoint();
	BinNumbFloatingPoint(float number);
	BinNumbFloatingPoint(const BinNumbFloatingPoint&);

	BinNumbFloatingPoint operator+ (const BinNumbFloatingPoint& other);
	void MantisaShiftLeft();
	void MantisaShiftRight();
	void IncreaseExpByOne();
	void DecreaseExpByOne();
	bool ExpComparison(const BinNumbFloatingPoint& other);
	bool ExpEquality(const BinNumbFloatingPoint& other);
	void SetUnit();

	bool GetStraightForm(int i);
	float GetStandartForm();

	void SetStraightForm(int i, bool value);
};

