#include "BinNumbFloatingPoint.h"

BinNumbFloatingPoint::BinNumbFloatingPoint()
{
	for (int i = 0; i <= last_mant_number; i++) {
		straight_form[i] = 0;
	}
}

BinNumbFloatingPoint::BinNumbFloatingPoint(float number)
{
	if (number < 0) this->straight_form[0] = 1;
	else this->straight_form[0] = 0;

	int power_of_two = -5;

	while (pow(2, power_of_two + 1) <= number) power_of_two++;
	BinaryNumber transform_exp(power_of_two + 127);
	for (int i = 1; i < 9; i++) this->straight_form[i] = transform_exp.GetStraightForm(i + 7);

	int mantisa = pow(2, 23) * (number - pow(2, power_of_two)) / (pow(2, power_of_two + 1) - pow(2, power_of_two));
	int original_value = abs(mantisa);
	int number_of_numbers = 0;

	while (original_value + 1 > pow(2, number_of_numbers)) {
		straight_form[last_mant_number - number_of_numbers] = mantisa % 2;
		number_of_numbers++;
		mantisa /= 2;
	}
	availability_of_unit = 1;
	for (int i = 0; i <= last_mant_number; i++) if(straight_form[i] == 204) straight_form[i] = 0;
}

BinNumbFloatingPoint::BinNumbFloatingPoint(const BinNumbFloatingPoint& other)
{
	this->availability_of_unit = other.availability_of_unit;
	for (int i = 0; i <= last_mant_number; i++)	this->straight_form[i] = other.straight_form[i];
}

BinNumbFloatingPoint BinNumbFloatingPoint::operator+(const BinNumbFloatingPoint& other)
{
	BinNumbFloatingPoint result;
	BinNumbFloatingPoint dop;
	result.SetUnit();
	dop.SetUnit();
	int buffer = 0;

	if (this->ExpComparison(other)) {
		for (int i = 0; i <= last_mant_number; i++) result.straight_form[i] = this->straight_form[i];
		for (int i = 0; i <= last_mant_number; i++) dop.straight_form[i] = other.straight_form[i];
	}
	else {
		for (int i = 0; i <= last_mant_number; i++) result.straight_form[i] = other.straight_form[i];
		for (int i = 0; i <= last_mant_number; i++) dop.straight_form[i] = this->straight_form[i];
	}
	while (!(result.ExpEquality(dop))) dop.MantisaShiftRight();
	for (int i = 0; i < 2; i++) {
		result.MantisaShiftRight();
		dop.MantisaShiftRight();
	}

	for (int i = last_mant_number; i > last_exp_number; i--) {
		buffer += result.GetStraightForm(i) + dop.GetStraightForm(i);
		if (buffer % 2 == 0) {
			result.SetStraightForm(i, 0);
			if (buffer == 2) buffer = 1;
			else buffer = 0;
		}
		else {
			result.SetStraightForm(i, 1);
			if (buffer == 3) buffer = 1;
			else buffer = 0;
		}
	}
	if (result.straight_form[last_exp_number + 1] == 0) {
		result.MantisaShiftLeft();
		result.DecreaseExpByOne();
	}
	result.MantisaShiftLeft();
	result.DecreaseExpByOne();
	result.SetUnit();
	return result;
}

void BinNumbFloatingPoint::MantisaShiftLeft()
{
	availability_of_unit = straight_form[last_exp_number + 1];
	for (int i = 9; i < last_mant_number; i++) straight_form[i] = straight_form[i + 1];
	straight_form[last_mant_number] = 0;
}

void BinNumbFloatingPoint::MantisaShiftRight()
{
	for (int i = last_mant_number; i > last_exp_number + 1; i--) straight_form[i] = straight_form[i - 1];
	if (availability_of_unit)
	{
		straight_form[last_exp_number + 1] = 1;
		availability_of_unit = 0;
	}
	else straight_form[last_exp_number + 1] = 0;
	IncreaseExpByOne();
}

void BinNumbFloatingPoint::IncreaseExpByOne()
{
	for (int i = last_exp_number; i > 0; i--) {
		if (straight_form[i] == 1)  straight_form[i] = 0;
		else {
			straight_form[i] = 1;
			break;
		}
	}
}

void BinNumbFloatingPoint::DecreaseExpByOne()
{
	int ind = last_exp_number;
	while (straight_form[ind] != 1) {
		straight_form[ind] = 1;
		ind--;
	}
	straight_form[ind] = 0;
}

bool BinNumbFloatingPoint::ExpComparison(const BinNumbFloatingPoint& other)
{
	for (int i = last_exp_number; i > 0; i--) {
		if (this->straight_form[i] < other.straight_form[i]) return false;
	}
	return true;
}

bool BinNumbFloatingPoint::ExpEquality(const BinNumbFloatingPoint& other)
{
	for (int i = last_exp_number; i > 0; i--) {
		if (this->straight_form[i] != other.straight_form[i]) return false;
	}
	return true;
}

void BinNumbFloatingPoint::SetUnit()
{
	availability_of_unit = 1;
}

bool BinNumbFloatingPoint::GetStraightForm(int i)
{
	return straight_form[i];
}

float BinNumbFloatingPoint::GetStandartForm()
{
	int exp = 0;
	float mant = 1;
	float standart = 0;
	for (int i = 1; i <= last_exp_number; i++) {
		if (straight_form[i] == 1) exp += pow(2, last_exp_number - i);
	}
	for (int i = last_exp_number + 1; i <= last_mant_number; i++) {
		if (straight_form[i] == 1) mant += pow(0.5 , i - last_exp_number);
	}
	standart = pow(-1, straight_form[0]) * pow(2, exp - 127) * mant;
	return standart;
}

void BinNumbFloatingPoint::SetStraightForm(int i, bool value)
{
	straight_form[i] = value;
}
