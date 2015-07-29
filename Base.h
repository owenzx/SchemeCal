#pragma once
class Base
{
public:
	enum{
		RATIONAL = 1,
		FLOAT = 2,
		COMPLEX = 3,
		BOOLEAN =4,
		CHAR=5,
		STRING=6
	} type_;
	Base(){}
	virtual Base *isInt()=0;
	virtual Base *isRat()=0;
	virtual Base *isReal()=0;
	virtual Base *isCpx()=0;
	virtual Base *isNum()=0;
	virtual ~Base(){};
	virtual void print() = 0;
};

