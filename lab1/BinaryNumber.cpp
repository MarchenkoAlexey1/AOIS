#include "BinaryNumber.h"

int BinaryNumber::GetLastNumberIndex()
{
	return last_number;
}

void BinaryNumber::ReceivingReverseForm()
{
	if (straight_form[0] == 0) {
		for (int i = 1; i <= last_number; i++) {
			reverse_form[i] = straight_form[i];
		}
	}
	else {
		for (int i = 1; i <= last_number; i++) {
			reverse_form[i] = 1 - straight_form[i];
		}
	}
}

void BinaryNumber::ReceivingAdditionalForm()
{
	ReceivingReverseForm();

	for (int i = 1; i <= last_number; i++) {
		additional_form[i] = reverse_form[i];
	}

	bool buffer = 0;

	if (straight_form[0] == 1) {
		for (int i = last_number; i > 0; i--) {
			if (additional_form[last_number] == 0 && buffer == 0) {
				additional_form[last_number] = 1;
				break;
			}
			else if (additional_form[i] == 1) {
				additional_form[i] = 0;
				buffer = 1;
			}
			else {
				additional_form[i] = 1;
				break;
			}
		}
	}
}

BinaryNumber::BinaryNumber()
{
	for (int i = 0; i <= last_number; i++) {
		additional_form[i] = reverse_form[i] = straight_form[i] = 0;
	}
}

BinaryNumber::BinaryNumber(int number)
{
	int original_value = abs(number);

	if (number > 0) additional_form[0] = reverse_form[0] = straight_form[0] = 0;
	else additional_form[0] = reverse_form[0] = straight_form[0] = 1;

	while (original_value + 1 > pow(2, number_of_significant_numbers)){
		straight_form[last_number - number_of_significant_numbers] = number % 2;
		number_of_significant_numbers++;
		number /= 2;
	} 
	for (int i = 1; i <= last_number - number_of_significant_numbers; i++) {
		straight_form[i] = 0;
	}

	ReceivingAdditionalForm();
}

BinaryNumber::BinaryNumber(const BinaryNumber&other)
{
	this->number_of_significant_numbers = other.number_of_significant_numbers;
	for (int i = 0; i <= last_number; i++) {
		this->straight_form[i] = other.straight_form[i];
		this->reverse_form[i] = other.reverse_form[i];
		this->additional_form[i] = other.additional_form[i];
	}
}

void BinaryNumber::Copy(const BinaryNumber& other)
{
	this->number_of_significant_numbers = other.number_of_significant_numbers;
	for (int i = 0; i <= last_number; i++) {
		this->straight_form[i] = other.straight_form[i];
		this->reverse_form[i] = other.reverse_form[i];
		this->additional_form[i] = other.additional_form[i];
	}
}

void BinaryNumber::ShiftLeft(bool number) {
	bool buffer;
	for (int i = 1; i < last_number; i++) {
		this->straight_form[i] = this->straight_form[i + 1];
	}
	this->straight_form[last_number] = number;
}

bool BinaryNumber::operator>=(const BinaryNumber& other)
{
	for (int i = 1; i <= last_number; i++) {
		if (this->straight_form[i] == 1 && other.straight_form[i] == 0) return 1;
		if (this->straight_form[i] == 0 && other.straight_form[i] == 1) return 0;
	}
	return 1;
}

BinaryNumber& BinaryNumber::operator=(const BinaryNumber& other)
{
	for (int i = 0; i <= last_number; i++) {
		this->additional_form[i] = other.additional_form[i];
	}
	return *this;
}

BinaryNumber BinaryNumber::operator+(const BinaryNumber& other)
{
	BinaryNumber result;
	int buffer = 0;

	for (int i = last_number; i >= 0; i--) {
		buffer += this->additional_form[i] + other.additional_form[i];
		if (buffer % 2 == 0) {
			result.straight_form[i] = 0;
			if (buffer == 2) buffer = 1;
			else buffer = 0;
		}
		else {
			result.straight_form[i] = 1;
			if (buffer == 3) buffer = 1;
			else buffer = 0;
		}
	}

	if (result.straight_form[0] == 1) {
		result.ReceivingAdditionalForm();
		result.reverse_form[0] = result.additional_form[0] = 1;
		for (int i = 0; i <= last_number; i++) {
			result.straight_form[i] = result.additional_form[i];
		}
	}
	result.ReceivingAdditionalForm();
	return result;
}

BinaryNumber BinaryNumber::operator*(const BinaryNumber& other)
{
	BinaryNumber result;
	result.straight_form[0] += this->straight_form[0] + other.straight_form[0];

	for (int i = last_number; i > 0; i--) {
		if (other.straight_form[i] == 1) {
			int buffer = 0;
			for (int j = last_number; j >= 7; j--) { 
				buffer += this->straight_form[j] + result.straight_form[i + j - 15];
				if (buffer % 2 == 0) {
					result.straight_form[i + j - 15] = 0;
					if (buffer == 2) buffer = 1;
					else buffer = 0;
				}
				else {
					result.straight_form[i + j - 15] = 1;
					if (buffer == 3) buffer = 1;
					else buffer = 0;
				}
			}
		}
		else {
			continue;
		}
	}
	result.ReceivingAdditionalForm();
	return result;
}

BinaryNumber BinaryNumber::operator-(const BinaryNumber& other) {
	if (this->straight_form[0] == 0) this->additional_form[0] = this->reverse_form[0] = this->straight_form[0] = 1;
	else this->additional_form[0] = this->reverse_form[0] = this->straight_form[0] = 0;
	this->ReceivingAdditionalForm();
	BinaryNumber result;
	int buffer = 0;

	for (int i = last_number; i >= 0; i--) {
		buffer += this->additional_form[i] + other.additional_form[i];
		if (buffer % 2 == 0) {
			result.straight_form[i] = 0;
			if (buffer == 2) buffer = 1;
			else buffer = 0;
		}
		else {
			result.straight_form[i] = 1;
			if (buffer == 3) buffer = 1;
			else buffer = 0;
		}
	}

	if (result.straight_form[0] == 1) {
		result.ReceivingAdditionalForm();
		result.reverse_form[0] = result.additional_form[0] = 1;
		for (int i = 0; i <= last_number; i++) {
			result.straight_form[i] = result.additional_form[i];
		}
	}
	if (this->straight_form[0] == 0) this->additional_form[0] = this->reverse_form[0] = this->straight_form[0] = 1;
	else this->additional_form[0] = this->reverse_form[0] = this->straight_form[0] = 0;
	this->ReceivingAdditionalForm();
	if (result.straight_form[0] == 0) result.additional_form[0] = result.reverse_form[0] = result.straight_form[0] = 1;
	else result.additional_form[0] = result.reverse_form[0] = result.straight_form[0] = 0;
	result.ReceivingAdditionalForm();
		return result;
}

BinaryNumber BinaryNumber::operator/(const BinaryNumber& other)
{
	BinaryNumber result;
	BinaryNumber buffer;
	int numerator_size = this->number_of_significant_numbers;
	int number_of_shifts = 0;

	for (int i = 0; i < other.number_of_significant_numbers; i++) this->ShiftLeft(0);

	for (int i = 0; i < 1; i++) {
		BinaryNumber numerator_slice;
		numerator_slice.ReceivingAdditionalForm();
		while (!(numerator_slice >= other)) {
			numerator_slice.ShiftLeft(this->straight_form[last_number - this->number_of_significant_numbers - other.number_of_significant_numbers + 1]);
			this->ShiftLeft(0);
			numerator_size--;
			if (numerator_size <= 0) number_of_shifts++;
		}
		buffer.Copy(numerator_slice - other);
		buffer.straight_form[0] = buffer.reverse_form[0] = buffer.additional_form[0] = 0;
		buffer.ShiftLeft(this->straight_form[last_number - this->number_of_significant_numbers - other.number_of_significant_numbers + 1]);
		this->ShiftLeft(0);
		if (numerator_size <= 0) number_of_shifts++;
		numerator_size--;
		result.ShiftLeft(1);
	}
	while (number_of_shifts < 6) {
		BinaryNumber numerator_slice;
		numerator_slice.Copy(buffer);
		if (numerator_slice >= other) {
			buffer.Copy(numerator_slice - other);
			buffer.straight_form[0] = buffer.reverse_form[0] = buffer.additional_form[0] = 0;
			buffer.ShiftLeft(this->straight_form[last_number - this->number_of_significant_numbers - other.number_of_significant_numbers + 1]);
			this->ShiftLeft(0);
			if (numerator_size <= 0) number_of_shifts++;
			numerator_size--;
			result.ShiftLeft(1);
		}
		else {
			buffer.ShiftLeft(this->straight_form[last_number - this->number_of_significant_numbers - other.number_of_significant_numbers + 1]);
			this->ShiftLeft(0);
			if (numerator_size <= 0) number_of_shifts++;
			numerator_size--;
			result.ShiftLeft(0);
		}
	}
	return result;
}

bool BinaryNumber::GetStraightForm(int i)
{
	return straight_form[i];
}

bool BinaryNumber::GetReverseForm(int i)
{
	return reverse_form[i];
}

bool BinaryNumber::GetAdditionalForm(int i)
{
	return additional_form[i];
}

void BinaryNumber::SetStraightForm(int i, bool value) {
	straight_form[i] = value;
}

int BinaryNumber::GetStandartForm()
{
	int standart = 0;
	for (int i = 1; i <= last_number; i++) {
		if (straight_form[i] == 1) standart += pow(2, last_number - i);
	}
	if (straight_form[0] == 1) standart *= -1;
	return standart;
}

float BinaryNumber::GetStandartFormForFloating()
{
	float standart = 0;
	for (int i = 1; i <= last_number - 5; i++) {
		if (straight_form[i] == 1) standart += pow(2, last_number - 5 - i);
	}
	for (int i = last_number - 4; i <= last_number; i++) {
		if (straight_form[i] == 1) standart += pow(0.5, i - last_number + 5);
	}
	if (straight_form[0] == 1) standart *= -1;
	return standart;
}