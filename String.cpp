#include "String.h"
#include <iostream>

using namespace std;

String::String(string str) :str_(str)
{
	type_ = STRING;
}


String::~String(){}




Boolean *String::isInt(){
	Boolean *result = new Boolean(false);
	return result;
}
Boolean *String::isRat(){
	Boolean *result = new Boolean(false);
	return result;
}

Boolean *String::isReal(){
	Boolean *result = new Boolean(false);
	return result;
}

Boolean *String::isCpx(){
	Boolean *result = new Boolean(false);
	return result;
}

Boolean *String::isNum(){
	Boolean *result = new Boolean(false);
	return result;
}


void String::print(){
	cout << '\"'<<str_<<'\"';
}

String *String::from_string(const char *expression){
	string exp = expression;
	if (exp[0] != '\"' || exp[exp.length()-1]!='\"')return NULL;
	return new String(exp.substr(1,exp.length()-2));
}