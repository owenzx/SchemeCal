#pragma once
#include "Base.h"
class Boolean :public Base
{
public:
	Boolean(bool val = false);
	~Boolean();
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
	static Boolean *from_string(const char *expression);
	bool val_;
};

