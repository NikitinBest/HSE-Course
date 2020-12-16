#include <iostream>
#include <vector>
#include <string>

class BigInteger{
private:
    std::vector<int> num;
    bool sgn = true;
    BigInteger& add(const BigInteger&, const bool);
	BigInteger& calc(const BigInteger&, const bool);
    void trim();
public:
    BigInteger(const BigInteger& a);
    BigInteger(int);
    BigInteger(std::string num ="");

	~BigInteger();

	friend BigInteger abs(const BigInteger&);

	friend bool operator==(const BigInteger& a, const BigInteger& b);
	friend bool operator!=(const BigInteger& a, const BigInteger& b);
    friend bool operator<(const BigInteger& a, const BigInteger& b);
	friend bool operator>(const BigInteger& a, const BigInteger& b);
	friend bool operator<=(const BigInteger& a, const BigInteger& b);
	friend bool operator>=(const BigInteger& a, const BigInteger& b);


	BigInteger operator-() const;
	friend BigInteger operator+(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator-(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator*(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator/(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator%(const BigInteger& a, const BigInteger& b);

    BigInteger& operator+=(const BigInteger& x);
    BigInteger& operator%=(const BigInteger& x);
    BigInteger& operator-=(const BigInteger& x);
    BigInteger& operator*=(const BigInteger& x);        
    BigInteger& operator/=(const BigInteger& x);

    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);

    operator bool() const;

    std::string toString() const;
	friend std::istream& operator>>(std::istream& in, BigInteger& x);
	friend std::ostream& operator<<(std::ostream& out, const BigInteger& x);
};