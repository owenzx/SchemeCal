#pragma once
#include "Base.h"
#include "Boolean.h"
#include "number.h"
#define SCAST_CHAR(x) static_cast<Char*>(x)

class Char :
	public Base
{
public:
	Char(char ch);
	~Char();
	//Boolean *isChar();
	Boolean *cles(Char *char2);
	Boolean *cles_ci(Char *char2);
	Boolean *isChar_alpha();
	Boolean *isChar_num();
	Boolean *isChar_space();
	Boolean *isChar_upc();
	Boolean *isChar_lowc();
	Number *chartoint();
	Char *toup();
	Char *tolow();
	void print();
	static Char *from_string(const char *expression);
	char ch_;
};

