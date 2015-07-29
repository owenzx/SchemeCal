#pragma once
#include "Boolean.h"
#include "Base.h"
#define SCAST_NUMBER(x) static_cast<Number*>(x)

class Number :public Base {
public:
	//enum{
	//	RATIONAL = 1,
	//	FLOAT = 2,
	//	COMPLEX = 3
	//} type_;
	Number(){}
	virtual ~Number(){}
	//virtual bool greater(Number *number2);
	//virtual bool equal(Number *number2);
	virtual Number *convert(Number *number2) = 0;
	virtual Number *add(Number *number2) = 0;
	virtual Number *sub(Number *number2) = 0;
	virtual Number *mul(Number *number2) = 0;
	virtual Number *div(Number *number2) = 0;
	virtual Boolean *les(Number *number2) = 0;
	virtual Boolean *lesE(Number *number2) = 0;
	virtual Boolean *grt(Number *number2) = 0;
	virtual Boolean *grtE(Number *number2) = 0;
	virtual Number *abs() = 0;
	virtual Number *quo(Number *number2) = 0;
	virtual Number *rem(Number *number2) = 0;
	virtual Number *mod(Number *number2) = 0;
	virtual Number *gcd(Number *number2) = 0;
	virtual Number *lcm(Number *number2) = 0;
	virtual Number *exp(Number *number2) = 0;
	virtual Number *ex() = 0;
	virtual Number *sqt() = 0;
	virtual Number *flr() = 0;
	virtual Number *cel() = 0;
	virtual Number *trc() = 0;
	virtual Number *rnd() = 0;
	virtual Number *sin() = 0;
	virtual Number *cos() = 0;
	virtual Number *tan() = 0;
	virtual Number *asin() = 0;
	virtual Number *acos() = 0;
	virtual Number *atan() = 0;
	virtual Number *atan2(Number *number2) = 0;
	virtual Number *log() = 0;
	virtual Number *maxi(Number *number2) = 0;
	virtual Number *mini(Number *number2) = 0;
	virtual Number *inextoex() = 0;
	virtual Number *extoinex() = 0;
	virtual Number *getNumerator() = 0;
	virtual Number *getDenominator() = 0;
	virtual Boolean *isZero() = 0;
	virtual Boolean *isNega() = 0;
	virtual Boolean *isPosi() = 0;
	virtual Boolean *isOdd() = 0;
	virtual Boolean *isEven() = 0;
	virtual Boolean *isInt() = 0;
	virtual Boolean *isRat() = 0;
	virtual Boolean *isReal() = 0;
	virtual Boolean *isCpx() = 0;
	virtual Boolean *isNum() = 0;
	virtual Boolean *isExact() = 0;
	virtual Boolean *isInexact() = 0;
	virtual void print() = 0;
};
