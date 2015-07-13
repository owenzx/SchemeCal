#pragma once
#include "number.h"
#include <string>

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
	virtual void print();
	Number* get_real();
	Number* get_imag();
	static bool checkstring(const string &s);
	static Complex *from_string(char *expression);
	Number* real_;
	Number* imag_;
};

