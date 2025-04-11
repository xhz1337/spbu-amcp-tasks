#include "long_number.hpp"

using mmh::LongNumber;
		
LongNumber::LongNumber() : length(1), sign(1) {
	numbers = new int[length];
	numbers[0] = 0;
}


LongNumber::LongNumber(const char* const str) {
	int str_length = get_length(str);
	if (str[0] == '-') {
		sign = -1;
		length = str_length - 1;
	} else {
		sign = 1;
		length = str_length;
	}
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = str[str_length - i - 1] - '0';
	}
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];
	for (int i = 0; i < length; i++) numbers[i] = x.numbers[i];
}

LongNumber::LongNumber(LongNumber&& x) {
	length = x.length;
	sign = x.sign;
	numbers = x.numbers;
	x.numbers = nullptr;
}

LongNumber::~LongNumber() {
	length = 0;
	delete [] numbers;
	numbers = nullptr;
}

LongNumber& LongNumber::operator = (const char* const str) {
	int str_len = get_length(str);
	if (str[0] == '+') {
		sign = 1;
		length = str_len;
	} else {
		sign = -1;
		length = str_len - 1;
	}
	delete [] numbers;
	numbers = new int[length];
	for (int i = 0; i < length; i++){
		numbers[i] = str[str_len - i - 1] - '0';
	}
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this == &x) return *this;
	length = x.length;
	sign = x.sign;
	delete [] numbers;
	numbers = new int[length];
	for (int i = 0; i < length; i++) numbers[i] = x.numbers[i];
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	length = x.length;
	sign = x.sign;
	delete [] numbers;
	numbers = x.numbers;
	x.numbers = nullptr;
	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (this == &x) return true;	
	if (length != x.length) return false;
	if (sign != x.sign) return false;
	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) return false;
	}
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (sign != x.sign){
		return sign > x.sign;
	}	
	if (length != x.length){
		if (sign == 1) return length > x.length;
		return length < x.length;

	}
	for (int i = 0; i < length; i++){
		if (numbers[i] != x.numbers[i]){
			if (sign == 1) return numbers[i] > x.numbers[i];
			return numbers[i] < x.numbers[i];
		}
	}
	return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	//TODO
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	// TODO
}

int LongNumber::get_digits_number() const noexcept {
	// TODO
}

int LongNumber::get_rank_number(int rank) const {
	// TODO
}

bool LongNumber::is_negative() const noexcept {
	// TODO
}

int LongNumber::get_length(const char* const str) const noexcept {
	// TODO
}

namespace biv {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		// TODO
	}
}