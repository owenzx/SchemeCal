#pragma once
#include "number.h"
#include "long_int.h"

#define SCAST_RATIONAL(x) static_cast<Rational*>(x)

class Rational : public Number {
public:
	//bool isInt() const;
	Rational(string numerator = "0", string denominator = "1");
	Rational(LongInt numerator, LongInt denominator);
	virtual ~Rational();
	bool greater(Number *number2);
	bool equal(Number *number2);
	void reduce();
	virtual Number *getNumerator();
	virtual Number *getDenominator();
	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual Boolean *les(Number *number2);
	virtual Boolean *lesE(Number *number2);
	virtual Boolean *grt(Number *number2);
	virtual Boolean *grtE(Number *number2);
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
	virtual Boolean *isZero();
	virtual Boolean *isNega();
	virtual Boolean *isPosi();
	virtual Boolean *isOdd();
	virtual Boolean *isEven();
	virtual Boolean *isInt();
	virtual Boolean *isRat();
	virtual Boolean *isReal();
	virtual Boolean *isCpx();
	virtual Boolean *isNum();
	virtual void print();
	static bool checkstring(const string &s);
	static Rational *from_string(const char *expression);
	bool operator==(const Rational &tmp) const;
	LongInt numerator_;
	LongInt denominator_;

};
