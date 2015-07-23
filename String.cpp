#include "String.h"
#include <iostream>

using namespace std;

String::String(string str) :str_(str)
{
	type_ = STRING;
}


String::~String(){}

void String::print(){
	cout << str_;
}

String *String::from_string(const char *expression){
	string exp = expression;
	if (exp[0] != '\"' || exp[exp.length()-1]!='\"')return NULL;
	return new String(exp.substr(1,exp.length()-2));
}