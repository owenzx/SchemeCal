#pragma once
#include "Base.h"
#define SCAST_BOOLEAN(x) static_cast<Boolean*>(x)
class Boolean :public Base
{
public:
	Boolean(bool val = false);
	~Boolean();
	virtual Boolean *isInt();
	virtual Boolean *isRat();
	virtual Boolean *isReal();
	virtual Boolean *isCpx();
	virtual Boolean *isNum();
	virtual Boolean *isChar();
	Boolean *optnot();
	virtual void print();
	static Boolean *from_string(const char *expression);
	bool val_;
};

