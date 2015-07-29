#include "String.h"
#include <iostream>
#include "float.h"
#include "rational.h"
#include "Complex.h"
#include <cctype>

using namespace std;

String::String(string str) :str_(str)
{
	type_ = STRING;
}


String::~String(){}

String *String::chartostring(Char *ch){
	string str = "";
	str += ch->ch_;
	String *result = new String(str);
	return result;
}

Number *String::stringtonum(){
	const char *strnum = str_.c_str();
	Number *res;
	res = Rational::from_string(strnum);
	if (!res) { res = Float::from_string(strnum); }
	if (!res) { res = Complex::from_string(strnum); }
	return res;
}


String *String::makeString(Number *num, Char *ch){
	if (!(num->isInt())) {
		throw(0); return NULL;
	}
	Float *flt = new Float();
	Number *tmp = flt->convert(num);
	Float *numf = SCAST_FLOAT(tmp);
	int k = int(numf->number_);
	string str(k, ch->ch_);
	String *result = new String(str);
	delete flt; delete tmp;
	return result;

}

Number *String::getLength(){
	Rational *result = new Rational(LongInt(int(str_.length())), LongInt(1));
	return result;
}

Char *String::getRef(Number *num){
	if (!(num->isInt())) {
		throw(0); return NULL;
	}
	Float *flt = new Float();
	Number *tmp = flt->convert(num);
	Float *numf = SCAST_FLOAT(tmp);
	int k = int(numf->number_);
	Char *result = new Char(str_[k]);
	delete flt; delete tmp;
	return result;
}

Boolean *String::sles(String *str2){
	Boolean *result = new Boolean(str_ < str2->str_);
	return result;
}

Boolean *String::slesE(String *str2){
	Boolean *result = new Boolean(str_ < str2->str_);
	return result;
}

Boolean *String::sles_ci(String *str2){
	string strci1 = "", strci2 = "";
	for (int i = 0; i < str_.length(); ++i){
		strci1 += char(tolower(str_[i]));
	}
	for (int i = 0; i < str2->str_.length(); ++i){
		strci2 += char(tolower(str2->str_[i]));
	}
	Boolean *result = new Boolean(strci1 < strci2);
	return result;
}

Boolean *String::slesE_ci(String *str2){
	string strci1 = "", strci2 = "";
	for (int i = 0; i < str_.length(); ++i){
		strci1 += char(tolower(str_[i]));
	}
	for (int i = 0; i < str2->str_.length(); ++i){
		strci2 += char(tolower(str2->str_[i]));
	}
	Boolean *result = new Boolean(strci1 <= strci2);
	return result;
}

String *String::subString(String *str2, Number *start, Number *end){
	int startInd = start->toInt(), endInd = end->toInt();
	string str = str2->str_.substr(startInd - 1, endInd - startInd);
	String *result = new String(str);
	return result;
}

String *String::strAppend(String *str2){
	string str = str_ + str2->str_;
	String *result = new String(str);
	return result;
}

String *String::strCopy(){
	string str(str_);
	String *result = new String(str);
	return result;
}

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

Boolean *String::isChar(){
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