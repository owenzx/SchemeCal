#pragma once

#define SCAST_NUMBER(x) static_cast<Number*>(x)

class Number {
public:
	enum{
		RATIONAL = 1,
		FLOAT = 2,
		COMPLEX = 3
	} type_;
	Number(){}
	virtual ~Number(){}
	virtual Number *convert(Number *number2) = 0;
	virtual Number *add(Number *number2) = 0;
	virtual Number *sub(Number *number2) = 0;
	virtual Number *mul(Number *number2) = 0;
	virtual Number *div(Number *number2) = 0;
	virtual Number *abs() = 0;
	virtual Number *quo(Number *number2) = 0;
	virtual Number *rem(Number *number2) = 0;
	virtual Number *mod(Number *number2) = 0;
	virtual Number *gcd(Number *number2) = 0;
	virtual Number *lcm(Number *number2) = 0;
	virtual Number *exp(Number *number2) = 0;
	virtual Number *sqt() = 0;
	virtual Number *flr() = 0;
	virtual Number *cel() = 0;
	virtual Number *trc() = 0;
	virtual Number *rnd() = 0;
	virtual Number *maxi(Number *number2) = 0;
	virtual Number *mini(Number *number2) = 0;
	virtual Number *inextoex() = 0;
	virtual Number *extoinex() = 0;
	virtual void print() = 0;
};
