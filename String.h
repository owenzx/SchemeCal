#pragma once
#include "Base.h"
#include "Boolean.h"
#include "Char.h"
#include "number.h"
#include <string>
#define SCAST_STRING(x) static_cast<String*>(x)

using std::string;

class String :
	public Base
{
public:
	String(string str="");
	~String();
	void print();
	String *chartostring(Char *ch);
	Number *stringtonum();
	String *makeString(Number *num, Char *ch);
	Number *getLength();
	Char *getRef(Number *num);
	Boolean *sles(String *str2);
	Boolean *sles_ci(String *str2);
	Boolean *slesE(String *str2);
	Boolean *slesE_ci(String *str2);
	String *subString(String *str2, Number *start, Number *end);
	String *strAppend(String *str2);
	String *strCopy();
	Boolean *isInt();
	Boolean *isRat();
	Boolean *isReal();
	Boolean *isCpx();
	Boolean *isNum();
	Boolean *isChar();
	static String *from_string(const char *expression);
	string str_;
};

