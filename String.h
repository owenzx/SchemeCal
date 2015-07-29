#pragma once
#include "Base.h"
#include "Boolean.h"
#include "Char.h"
#include "number.h"
#include <string>

using std::string;

class String :
	public Base
{
public:
	String(string str);
	~String();
	void print();
	String *chartostring(Char *ch);
	String *makeString(Number *num, char *ch);
	Number *getLength();
	Char *getRef(Number *num);
	Boolean *cles(String *str2);
	Boolean *cles_ci(String *str2);
	Boolean *clesE(String *str2);
	Boolean *cles_ciE(String *str2);
	String subString(String *str, Number *start, Number *end);
	String strAppend(String *str2);
	String strCopy(String *str2);
	Boolean *isInt();
	Boolean *isRat();
	Boolean *isReal();
	Boolean *isCpx();
	Boolean *isNum();
	static String *from_string(const char *expression);
	string str_;
};

