#pragma once
#include "number.h"
#include <string>

using namespace std;

#define SCAST_FLOAT(x) static_cast<Float*>(x)

class Float : public Number {
private:
	string doubleToString(double d);
public:
	Float(double number = 0);
	virtual ~Float();
	bool greater(Number *number2);
	bool equal(Number *number2);
	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual Boolean les(Number *number2);
	virtual Boolean lesE(Number *number2);
	virtual Boolean grt(Number *number2);
	virtual Boolean grtE(Number *number2);
	virtual Number *abs();
	virtual Number *quo(Number *number2);
	virtual Number *rem(Number *number2);
	virtual Number *mod(Number *number2);
	virtual Number *gcd(Number *number2);
	virtual Number *lcm(Number *number2);
	virtual Number *exp(Number *number2);
	virtual Number *ex();
	virtual Number *sqt();
	virtual Number *flr();
	virtual Number *cel();
	virtual Number *trc();
	virtual Number *rnd();
	virtual Number *sin();
	virtual Number *cos();
	virtual Number *tan();
	virtual Number *asin();
	virtual Number *acos();
	virtual Number *atan();
	virtual Number *log();
	virtual Number *maxi(Number *number2);
	virtual Number *mini(Number *number2);
	virtual Number *inextoex();
	virtual Number *extoinex();
	virtual Number *getNumerator();
	virtual Number *getDenominator();
	virtual Boolean isZero();
	virtual Boolean isNega();
	virtual Boolean isPosi();
	virtual Boolean isOdd();
	virtual Boolean isEven();
	virtual Boolean isInt();
	virtual Boolean isRat();
	virtual Boolean isReal();
	virtual Boolean isCpx();
	virtual Boolean isNum();
	virtual void print();
	static Float *from_string(const char *expression);
	double number_;
};