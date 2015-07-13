#pragma once
#include "number.h"
#include "long_int.h"

#define SCAST_RATIONAL(x) static_cast<Rational*>(x)

class Rational : public Number {
public:
	Rational(string numerator = "0", string denominator = "1");
	Rational(LongInt numerator, LongInt denominator);
	virtual ~Rational();

	void reduce();
	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual void print();
	static bool checkstring(const string &s);
	static Rational *from_string(const char *expression);
	LongInt numerator_;
	LongInt denominator_;

};
