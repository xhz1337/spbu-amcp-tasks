#include "long_number.hpp"

namespace mmh {	
	LongNumber::LongNumber() : len(1), sign(1) {
		numbers = new int[len];
		numbers[0] = 0;
	}

	LongNumber::LongNumber(const char* const str) {
		int str_len = get_length(str);
		if (str[0] == '-') {
			sign = -1;
			len = str_len - 1;
		} else {
			sign = 1;
			len = str_len;
		}
		numbers = new int[len];
		for (int i = 0; i < len; i++) {
			numbers[i] = str[str_len - i - 1] - '0';
		}
	}

	LongNumber::LongNumber(const LongNumber& x) {
		len = x.len;
		sign = x.sign;
		numbers = new int[len];
		for (int i = 0; i < len; i++) numbers[i] = x.numbers[i];
	}

	LongNumber::LongNumber(LongNumber&& x) {
		len = x.len;
		sign = x.sign;
		numbers = x.numbers;
		x.numbers = nullptr;
	}

	LongNumber::~LongNumber() {
		len = 0;
		delete [] numbers;
		numbers = nullptr;
	}

	LongNumber& LongNumber::operator = (const char* const str) {
		int str_len = get_length(str);
		if (str[0] == '+') {
			sign = 1;
			len = str_len;
		} else {
			sign = -1;
			len = str_len - 1;
		}
		delete [] numbers;
		numbers = new int[len];
		for (int i = 0; i < len; i++){
			numbers[i] = str[str_len - i - 1] - '0';
		}
		return *this;
	}

	LongNumber& LongNumber::operator = (const LongNumber& x) {
		if (this == &x) return *this;
		len = x.len;
		sign = x.sign;
		delete [] numbers;
		numbers = new int[len];
		for (int i = 0; i < len; i++) numbers[i] = x.numbers[i];
		return *this;
	}

	LongNumber& LongNumber::operator = (LongNumber&& x) {
		len = x.len;
		sign = x.sign;
		delete [] numbers;
		numbers = x.numbers;
		x.numbers = nullptr;
		return *this;
	}

	bool LongNumber::operator == (const LongNumber& x) const {
		if (this == &x) return true;	
		if (len != x.len || sign != x.sign) return false;
		for (int i = 0; i < len; i++) {
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
		if (len != x.len){
			if (sign == 1) return len > x.len;
			return len < x.len;
		}
		for (int i = 0; i < len; i++){
			if (numbers[i] != x.numbers[i]){
				if (sign == 1) return numbers[i] > x.numbers[i];
				return numbers[i] < x.numbers[i];
			}
		}
		return false;
	}

	bool LongNumber::operator < (const LongNumber& x) const {
		return (!(*this > x) && (*this != x));
	}

	LongNumber LongNumber::operator + (const LongNumber& x) const {
		LongNumber sum, min, max;
		if (sign == x.sign){
			if (len >= x.len){
				max = *this;
				min = x;
				sum.len = len + 1;
				sum.sign = sign;
			}
			else
			{
				max = x;
				min = *this;
				sum.len = x.len + 1;
				sum.sign = x.sign;
			}
			for (int i = 0; i < min.len; i++)
				sum.numbers[i] = min.numbers[i] + max.numbers[i]; 

			for (int i = min.len; i < max.len; i++)
				sum.numbers[i] = max.numbers[i];

			for (int i = 0; i < sum.len; i++)
			{
				if (sum.numbers[i] >= 10){
					sum.numbers[i] %= 10;
					++sum.numbers[i + 1];
				}
			}
		}	
		else{
			LongNumber posx = x, posthis = *this;
			posthis.sign = 1;
			posx.sign = 1;	
			if (posx.len >= posthis.len){
				max = *this;
				min = x;
				sum.len = len + 1;
				sum.sign = sign;
			}
			else
			{
				max = x;
				min = *this;
				sum.len = x.len + 1;
				sum.sign = x.sign;
			}
			for (int i = 0; i < max.len; i++)
				sum.numbers[i] = max.numbers[i]; 

			for (int i = 0; i < min.len; i++)
				sum.numbers[i] -= min.numbers[i];	

			for (int i = 0; i < sum.len - 1; i++)
			{
				if (sum.numbers[i] < 0){
					sum.numbers[i] += 10;
					--sum.numbers[i + 1];
				}
			}
			while (sum.len > 1 && sum.numbers[sum.len - 1] == 0){ //cut zeros 
				--sum.len;
			} 
		}
		return sum;
	}

	LongNumber LongNumber::operator - (const LongNumber& x) const {
		LongNumber rsum = x;
		rsum.sign = -rsum.sign;
		rsum = *this + rsum;
		return rsum;
	}

	LongNumber LongNumber::operator * (const LongNumber& x) const {
		LongNumber power;
		power.len = len + x.len;
		power.sign = sign * x.sign;
		for (int i = 0; i < x.len; i++) {
			for (int j = 0; j < len; j++) {
				power.numbers[j + i] += x.numbers[i] * numbers[j];
				if (power.numbers[i + j] > 9){
					int t = power.numbers[i + j] / 10;
					power.numbers[i + j + 1] += t;
					power.numbers[i + j] -= t * 10;
				}
			}
		}
		while (power.len > 1 && power.numbers[power.len - 1] == 0) {
			power.len--;
		}
		
		return power;
	}
	LongNumber LongNumber::operator / (const LongNumber& x) const {
		LongNumber res;
		LongNumber divident = *this;
		divident.sign = 1;
		if (divident < x) {
			return res;
		} else {
			res.len = len - x.len + 1;
			res.sign = sign*x.sign;

			for (int i = 0; i < res.len; i++) {
				LongNumber divider;
				divider.len = len - i;
				divider.sign = 1;
				
				for (int j = 0; j < x.len; j++) {
					divider.numbers[len - x.len - i + j] = x.numbers[j];
				}
				
				int k = 0;
				while (divident > divider || divident == divider) {
					k++;
					divident = divident - divider;
				}
				res.numbers[res.len - i - 1] = k;
			}
		}
		
		while (res.len > 1 && res.numbers[res.len - 1] == 0)
		{
			res.len--;
		}
		return res;
	}

	LongNumber LongNumber::operator % (const LongNumber& x) const {
		if (is_negative()) {
			LongNumber temp;
			if (x.is_negative() == 1) temp = "1";
			else temp = "-1";
			return *this - (*this / x + temp) * x;
		} else {
			return *this - (*this / x) * x;
		}
	}

	int LongNumber::get_digits_number() const noexcept {
		return len;
	}

	int LongNumber::get_rank_number(int rank) const {
		return numbers[rank-1];
	}

	bool LongNumber::is_negative() const noexcept {
		return sign == 0;
	}

	int LongNumber::get_length(const char* const str) const noexcept {
		int l = 0;
		while (str[len] != '\n') ++l;
		return l;

	}

	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if (x.sign == 0) {
			os << '-';
		}
		for (int i = 0; i < x.len; i++) {
			os << x.numbers[x.len - i - 1];
		}
		return os;
	}
}