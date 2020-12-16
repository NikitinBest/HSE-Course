#include "biginteger.h"

BigInteger::BigInteger(int x){
    sgn = true;
    if(x == 0){
        num = {0};
        return;
    }
    if(x < 0) {
        sgn = false;
        x *= -1;
    }
    while(x){
        num.push_back(x%10);
        x/=10;
    }
}

BigInteger::BigInteger(std::string x){
   sgn = !(x.size() && x[0]=='-');
   for(int i = x.size(); i > 0; --i){
		std::string substr = (i < 1) ? x.substr(0, i) : x.substr(i - 1, 1);
		this->num.push_back(atoi(substr.c_str()));
   }
}

BigInteger::BigInteger(const BigInteger& X) {
	this->sgn = X.sgn;
	this->num = X.num;
}

BigInteger::~BigInteger() {
    //destructor
}

//Boolean operators
bool operator==(const BigInteger& a, const BigInteger& b){
    return (a.num == b.num) && (a.sgn == b.sgn);
}
bool operator!=(const BigInteger& a, const BigInteger& b){
    return !(a==b);
}
bool operator<(const BigInteger& a, const BigInteger& b){
    if(a==b) return false;
    if(a.sgn){
        if(b.sgn){
            if(a.num.size()!=b.num.size())
                return a.num.size()<b.num.size();
            else{
                for(int i = a.num.size() - 1; i >= 0 ; --i){
                    if(a.num[i]!=b.num[i]) return a.num[i]<b.num[i];
                }
                return false;
            }
        } else {
            return false;
        }
    } else {
        if(b.sgn){
            return true;
        } else{
			if (a.num.size() != b.num.size())
				return a.num.size() > b.num.size();
            else{
                for(int i = a.num.size() - 1; i >= 0 ; --i){
                    if(a.num[i]!=b.num[i]) return a.num[i]>b.num[i];
                }
                return false;
            }
        }
    }
}
bool operator>(const BigInteger& a, const BigInteger& b) {
	if (a == b) return false;
	return b < a;
}
bool operator<=(const BigInteger& a, const BigInteger& b) {
	return ((a < b) || (a == b));
}
bool operator>=(const BigInteger& a, const BigInteger& b) {
	return ((a > b) || (a == b));
}

BigInteger abs(const BigInteger& x) {
	return x.sgn ? x : -x;
}

void BigInteger::trim() {
	while(num.size() > 1 && num.back() == 0) num.pop_back();
	if (num.size() == 1 && num.back() == 0) sgn = true;
}

BigInteger& BigInteger::calc(const BigInteger& x, const bool minus) {
   int ost = 0;
	const bool isThisBigger = abs(*this) > abs(x), isSubtraction = (!sgn) ^ (!x.sgn) ^ minus;

	if (!isThisBigger) {
		sgn = !((!x.sgn) ^ minus);
	}

	for (int i = 0; i < num.size() || i < x.num.size() || ost != 0; i++) {
		if (i >= num.size()) {
			num.push_back(0);
		}

		if (isSubtraction) {
			if (isThisBigger) {
				num[i] -= (i < x.num.size() ? x.num[i] : 0);
			}
			else {
				num[i] = (i < x.num.size() ? x.num[i] : 0) - (i < num.size() ? num[i] : 0);
			}
		}
		else {
			num[i] += (i < x.num.size() ? x.num[i] : 0);
		}

		num[i] += ost;
		ost = 0;

		if (num[i] >= 10) {
			num[i] -= 10;
			ost++;
		}
		else if (num[i] < 0) {
			num[i] += 10;
			ost--;
		}
	}

	trim();
	return *this;
};

BigInteger& BigInteger::operator+=(const BigInteger& x){
    return calc(x, false);
}
BigInteger& BigInteger::operator-=(const BigInteger& x){
    return calc(x, true);
}
BigInteger& BigInteger::operator*=(const BigInteger& x){
    BigInteger res(0);
	int ost = 0;

	res.sgn = !(sgn ^ x.sgn);

	for (int i = 0; i < num.size(); i++) {
		for (int j = 0; j < x.num.size() || ost; j++) {
			int k = i + j;

			if (k >= res.num.size()) {
				res.num.push_back(0);
			}

			res.num[k] += num[i] * x.num[j] + ost;
			ost = 0;

			if (res.num[k] >= 10) {
				ost = res.num[k] / 10;
				res.num[k] %= 10;
			}
		}
	}

	res.trim();
	return *this = res;
}
BigInteger& BigInteger::operator/=(const BigInteger& x){
    BigInteger res(0);
    for(;*this>x;++res){
        *this-=x;
    }
    return *this = res;
}
BigInteger& BigInteger::operator%=(const BigInteger& x){
    BigInteger res(0);
    if((*this == res) || (res == x)) return *this = res;
    for(;*this>=x;){
        *this-=x;
    }
    res.sgn = sgn;
    return *this = res;
}
BigInteger BigInteger::operator-() const{
    BigInteger x = *this;
    x.sgn^=1;
    return x;
}
BigInteger operator+(const BigInteger& a, const BigInteger& b) {
	return BigInteger(a) += b;
}
BigInteger operator-(const BigInteger& a, const BigInteger& b) {
	return BigInteger(a) -= b;
}
BigInteger operator*(const BigInteger& a, const BigInteger& b) {
	return BigInteger(a) *= b;
}
BigInteger operator/(const BigInteger& a, const BigInteger& b) {
	return BigInteger(a) /= b;
}
BigInteger operator%(const BigInteger& a, const BigInteger& b) {
	return BigInteger(a) %= b;
}

BigInteger BigInteger::operator++(int){
    BigInteger last(*this), one(1);
    *this+=one;
    return (last);
}
BigInteger& BigInteger::operator++() {
    BigInteger one(1);
    *this += one;
	return (*this);
}

BigInteger BigInteger::operator--(int){
    BigInteger last(*this), one(1);
    *this-=one;
    return (last);
}
BigInteger& BigInteger::operator--() {
    BigInteger one(1);
    *this -= one;
	return (*this);
}

BigInteger::operator bool() const {
	return *this != BigInteger(0);
}

std::string BigInteger::toString() const{
    std::string str = this->sgn?"":"-";
    for(int i = this->num.size() - 1; i >=0; --i){
        str+=std::to_string(this->num[i]);
    }
    return str;
}

std::istream& operator>>(std::istream& in, BigInteger& x){
    std::string str;
    in>>str;
    x = BigInteger(str);
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& x){
    if (!x.sgn) out<<"-";
    for(int i = x.num.size() - 1; i>=0; --i)
        out<<x.num[i];
    return out;
}
