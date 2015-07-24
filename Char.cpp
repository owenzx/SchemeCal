#include "Char.h"
#include "rational.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

Char::Char(char ch) :ch_(ch)
{
	type_ = CHAR;
}


Char::~Char(){}

Boolean *Char::cles(Char *char2){
	Boolean *result = new Boolean(ch_ < char2->ch_);
	return result;
}

Boolean *Char::cles_ci(Char *char2){
	Boolean *result = new Boolean(tolower(ch_) < tolower(char2->ch_));
	return result;
}


Boolean *Char::isChar_alpha(){
	Boolean *result = new Boolean((ch_ >= 'a' && ch_ <= 'z') || (ch_ >= 'A' && ch_ <= 'Z'));
	return result;
}

Boolean *Char::isChar_num(){
	Boolean *result = new Boolean(ch_ >= '0' && ch_ <= '9');
	return result;
}

Boolean *Char::isChar_space(){
	Boolean *result = new Boolean(isspace(ch_));
	return result;
}

Boolean *Char::isChar_upc(){
	Boolean *result = new Boolean(isupper(ch_));
	return result;
}

Boolean *Char::isChar_lowc(){
	Boolean *result = new Boolean(islower(ch_));
	return result;
}

Char *Char::toup(){
	Char *result = new Char(std::toupper(ch_));
	return result;
}

Char *Char::tolow(){
	Char *result = new Char(std::tolower(ch_));
	return result;
}

Number *Char::chartoint(){
	Rational *result = new Rational(LongInt(int(ch_)), LongInt(1));
	return result;
}

void Char::print(){
	cout << "#\\";
	switch (ch_)
	{
	case ' ': cout << "space"; break;
	case '\n':cout << "newline"; break;
	default:
		cout << ch_;
		break;
	}
}

Char *Char::from_string(const char *expression){
	string exp = expression;
	if (exp.length() < 3 || exp.substr(0, 2) != "#\\") return NULL;
	if (exp.length() == 3){
		return new Char(exp[2]);
	}
	else{
		string ch = exp.substr(2, exp.length() - 2);
		if (ch == "space"){
			return new Char(' ');
		}
		else if (ch == "newline"){
			return new Char('\n');
		}
		return NULL;
	}
}