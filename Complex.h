#pragma once
#include "number.h"
#include <string>
#include "rational.h"
#include "float.h"
#define SCAST_COMPLEX(x) static_cast<Complex*>(x)

using namespace std;

class Complex :
	public Number
{
public:
	Complex(string real = "0", string imag = "0");
	Complex(Number* real, Number* imag = new Rational(0, 1));
	~Complex();
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
	virtual Number *getNumerator();
	virtual Number *getDenominator();
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
	virtual Number *inextoex();
	virtual Number *extoinex();
	virtual void print();
	Number* getreal();
	Number* getimag();
	Number* torect(Number *number1, Number *number2);
	Number* topolar(Number *number1, Number *number2);
	Number* getmag();
	Number* getang();
	//static bool checkstring(const string &s);
	static Complex *from_string(char *expression);
	Number* real_;
	Number* imag_;
};

