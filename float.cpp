#include "float.h"
#include "rational.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

#define ABS(x) ((x)<0?(-(x)):(x))

Float::Float(double number) : number_(number){
	type_ = FLOAT;
}

Float::~Float(){

}

string Float::doubleToString(double d){
	ostringstream os;
	os.precision(18);
	if (os << d)
		return os.str();
	return "invalid conversion";
}


Number *Float::convert(Number *number2){
	assert(number2->type_ <= type_);
	Float *result = new Float();
	switch (number2->type_){
	case RATIONAL:{
		Rational *tmp = SCAST_RATIONAL(number2);
		result->number_ = (double)tmp->numerator_ / (double)tmp->denominator_;
		// printf("%lf", result->number_);
		break;
	}
	case FLOAT:{
		Float *tmp = SCAST_FLOAT(number2);
		result->number_ = tmp->number_;
		break;
	}
	default:
		assert(0 && "type_ not defined");
	}
	return result;
}

Number *Float::inextoex(){

	string floatstr = doubleToString(number_);
	//cout << floatstr << endl;
	string numerator, denominator;
	int dotPos = floatstr.find('.'), ePos = floatstr.find('e'), endPos = floatstr.length() - 1, zeronum = 0, pownum;
	//	cout << ePos << endl;
	if (dotPos == floatstr.npos){
		numerator = floatstr;
		denominator = "1";
	}
	else{
		numerator = floatstr.substr(0, dotPos);
		if (ePos != floatstr.npos) endPos = ePos - 1;
		numerator += floatstr.substr(dotPos + 1, endPos - dotPos);
		denominator = "1";
		zeronum += (endPos - dotPos);
	}
	//	cout << floatstr.substr(ePos,floatstr.length()-ePos-1).c_str() << endl;
	if (ePos != floatstr.npos) pownum = atoi(floatstr.substr(ePos + 1, floatstr.length() - ePos - 1).c_str());
	else pownum = 0;
	//	cout << "P" << pownum << endl;
	//	cout << "Z" << zeronum << endl;
	zeronum -= pownum;
	string zeros(ABS(zeronum), '0');
	if (zeronum>0) denominator += zeros;
	else numerator += zeros;
	//cout << numerator << endl;
	//cout << denominator << endl;

	Rational *result = new Rational(numerator,denominator);
	return result;
}

Number *Float::extoinex(){
	Float *result = new Float(number_);
	return result;
}


Number *Float::add(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ + tmp->number_);
	return result;
}

Number *Float::sub(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ - tmp->number_);
	return result;
}

Number *Float::mul(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ * tmp->number_);
	return result;
}

Number *Float::div(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	if (tmp->number_ == 0)throw('a');
	//assert(ABS(tmp->number_) != 0 && "divide zero");
	Float *result = new Float(number_ / tmp->number_);
	return result;
}

Number *Float::abs(){
	Float *result = new Float(ABS(number_));
	return result;
}

Number *Float::quo(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	assert(number_ == trunc(number_) && tmp->number_ == trunc(tmp->number_)
		&& "These numbers are not integers!");
	Float *result = SCAST_FLOAT(this->div(number2)->trc());
	return result;
}

Number *Float::rem(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	assert(number_ == trunc(number_) && tmp->number_ == trunc(tmp->number_)
		&& "These numbers are not integers!");
	Float *result = new Float(fmod(number_, tmp->number_));
	return result;
}


Number *Float::mod(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	assert(number_ == trunc(number_) && tmp->number_ == trunc(tmp->number_)
		&& "These numbers are not integers!");
	Float *result;
	if (number_*(tmp->number_)>0) result = new Float(fmod(number_, tmp->number_));
	else result = new Float(tmp->number_ + fmod(number_, tmp->number_));
	return result;
}

Number *Float::gcd(Number *number2){
	Number *tmp2 = number2->abs();
	Float *tmp = SCAST_FLOAT(tmp2);
	assert(number_ == trunc(number_) && tmp->number_ == trunc(tmp->number_)
		&& "These numbers are not integers!");
	if (number_ == 0) {
		Float *result = new Float(tmp->number_);
		return result;
	}
	else if (tmp->number_ == 0) {
		Float *result = new Float(number_);
		return result;
	}
	double big = max(number_, tmp->number_);
	double small = min(number_, tmp->number_);
	double t;
	while (t = fmod(big, small)){
		big = small;
		small = t;
	}
	Float *result = new Float(small);
	return result;
}

Number *Float::lcm(Number *number2){
	Number *tmp2 = number2->abs();
	Float *tmp = SCAST_FLOAT(tmp2);
	if (number_ == 0 && tmp->number_ == 0){
		Float *result = new Float(0);
		return result;
	}
	Float *result = SCAST_FLOAT(this->mul(number2)->div(gcd(number2)));
	return result;
}

Number *Float::exp(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(pow(number_,tmp->number_));
	return result;
}

Number *Float::sqt(){
	Float *result = new Float(sqrt(number_));
	return result;
}


Number *Float::flr(){
	Float *result = new Float(floor(number_));
	return result;
}

Number *Float::cel(){
	Float *result = new Float(ceil(number_));
	return result;
}

Number *Float::trc(){
	Float *result = new Float(trunc(number_));
	return result;
}

Number *Float::rnd(){
	if (ABS(number_ - trunc(number_)) != 0.5){
		Float *result = new Float(round(number_));
		return result;
	}
	else{
		if (fmod(trunc(number_),2)==0){
			Float *result = new Float(trunc(number_));
			return result;
		}
		else{
			Float *result = new Float(round(number_));
			return result;
		}
	}
	
}

Number *Float::maxi(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(max(number_, tmp->number_));
	return result;
}

Number *Float::mini(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(min(number_, tmp->number_));
	return result;
}

void Float::print(){
	printf("%.16g", number_);
	if (number_ == trunc(number_)) printf(".0");
	//printf("/n");
}

Float *Float::from_string(const char *expression){
	char *end_pointer;
	double val = strtod(expression, &end_pointer);
	if (end_pointer == expression || end_pointer != expression + strlen(expression))
		return NULL;
	return new Float(val);
}


// int main(){
// 	Float *a = new Float(1.2);
// 	Float *b = new Float(1.3);
// 	(a->add(b))->print();
// }
