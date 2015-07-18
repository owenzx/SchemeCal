#pragma once
#include <string>
#define MAX(x,y) ((x)<(y)?(y):(x))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define ABS(x) ((x)<0?(-(x)):(x))

using namespace std;

class LongInt {
private:
	string reverse(const string &number_)const;
	string add(const string &a, const string &b)const;
	string minus(const string &a, const string &b)const;
public:
	LongInt(int number = 0);
	LongInt(const string &number);
	LongInt(const LongInt &long_int2);
	LongInt(double number);
	~LongInt();

	operator bool();
	operator int();
	operator double();
	bool operator!=(const LongInt &long_int2) const;
	bool operator<(const LongInt &long_int2) const;
	LongInt &operator=(const LongInt &long_int2);
	LongInt operator+(const LongInt &long_int2) const;
	LongInt operator-(const LongInt &long_int2) const;
	LongInt operator*(const LongInt &long_int2) const;
	LongInt operator/(const LongInt &long_int2) const;
	LongInt operator%(const LongInt &long_int2) const;
	friend LongInt max(const LongInt &long_int1, const LongInt &long_int2);
	friend LongInt min(const LongInt &long_int1, const LongInt &long_int2);
	void print();

	string number_;
};