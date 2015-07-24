#pragma once
#include "Base.h"
#include <string>

using std::string;

class String :
	public Base
{
public:
	String(string str);
	~String();
	void print();
	static String *from_string(const char *expression);
	string str_;
};

