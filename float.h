#pragma once
#include "number.h"

#define SCAST_FLOAT(x) static_cast<Float*>(x)

class Float : public Number {
public:
	Float(double number = 0);
	virtual ~Float();

	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual Number *abs();
	virtual Number *quo(Number *number2);
	virtual Number *rem(Number *number2);
	virtual Number *mod(Number *number2);
	virtual Number *gcd(Number *number2);
	virtual Number *lcm(Number *number2);
	virtual Number *exp(Number *number2);
	virtual Number *sqt();
	virtual Number *flr();
	virtual Number *cel();
	virtual Number *trc();
	virtual Number *rnd();
	virtual Number *maxi(Number *number2);
	virtual Number *mini(Number *number2);
	virtual Number *inextoex();
	virtual Number *extoinex();
	virtual void print();
	static Float *from_string(const char *expression);
	double number_;
};