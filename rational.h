#pragma once
#include "number.h"
#include "long_int.h"

#define SCAST_RATIONAL(x) static_cast<Rational*>(x)

class Rational : public Number {
public:
	bool isInt() const;
	Rational(string numerator = "0", string denominator = "1");
	Rational(LongInt numerator, LongInt denominator);
	virtual ~Rational();
	bool greater(Number *number2);
	void reduce();
	virtual Number *getNumerator();
	virtual Number *getDenominator();
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
	static bool checkstring(const string &s);
	static Rational *from_string(const char *expression);
	bool operator==(const Rational &tmp) const;
	LongInt numerator_;
	LongInt denominator_;

};
