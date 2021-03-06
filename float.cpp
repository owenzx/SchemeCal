#include "float.h"
#include "rational.h"
#include "Complex.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#define ABS(x) ((x)<0?(-(x)):(x))

Float::Float(double number) : number_(number){
	type_ = FLOAT;
}

Float::~Float(){

}

bool Float::greater(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	return (number_ > tmp->number_);
}

bool Float::equal(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	return (number_ == tmp->number_);
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
//
//Number *Float::inextoex(){
//
//	string floatstr = doubleToString(number_);
//	//cout << floatstr << endl;
//	string numerator, denominator;
//	int dotPos = floatstr.find('.'), ePos = floatstr.find('e'), endPos = floatstr.length() - 1, zeronum = 0, pownum;
//	//	cout << ePos << endl;
//	if (dotPos == floatstr.npos){
//		numerator = floatstr;
//		denominator = "1";
//	}
//	else{
//		numerator = floatstr.substr(0, dotPos);
//		if (ePos != floatstr.npos) endPos = ePos - 1;
//		numerator += floatstr.substr(dotPos + 1, endPos - dotPos);
//		denominator = "1";
//		zeronum += (endPos - dotPos);
//	}
//	//	cout << floatstr.substr(ePos,floatstr.length()-ePos-1).c_str() << endl;
//	if (ePos != floatstr.npos) pownum = atoi(floatstr.substr(ePos + 1, floatstr.length() - ePos - 1).c_str());
//	else pownum = 0;
//	//	cout << "P" << pownum << endl;
//	//	cout << "Z" << zeronum << endl;
//	zeronum -= pownum;
//	string zeros(ABS(zeronum), '0');
//	if (zeronum>0) denominator += zeros;
//	else numerator += zeros;
//	//cout << numerator << endl;
//	//cout << denominator << endl;
//
//	Rational *result = new Rational(numerator,denominator);
//	return result;
//}

Number *Float::inextoex(){
	double numerator = number_, denominator = 1;
	while (numerator != trunc(numerator)){
		numerator *= 2;
		denominator *= 2;
	}
	while (fmod(numerator, 2) == 0 && denominator != 1){
		numerator /= 2;
		denominator /= 2;
	}
	Rational *result = new Rational(LongInt(numerator), LongInt(denominator));
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
	//if (tmp->number_ == 0)throw('a');
	assert(ABS(tmp->number_) != 0 && "divide zero");
	Float *result = new Float(number_ / tmp->number_);
	return result;
}

Boolean *Float::les(Number *number2){
	Boolean *result = new Boolean(!greater(number2) && !equal(number2));
	return result;
}

Boolean *Float::lesE(Number *number2){
	Boolean *result = new Boolean(!greater(number2));
	return result;
}

Boolean *Float::grt(Number *number2){
	Boolean *result = new Boolean(greater(number2));
	return result;
}

Boolean *Float::grtE(Number *number2){
	Boolean *result = new Boolean(greater(number2) || equal(number2));
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
	if (number_*(tmp->number_) >= 0) result = new Float(fmod(number_, tmp->number_));
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
	Float *result = SCAST_FLOAT(this->mul(tmp)->div(gcd(tmp)));
	return result;
}

Number *Float::exp(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	double number = pow(number_, tmp->number_);
	if (number == number)	{
		Float *result = new Float(number);
		return result;
	}
	else{
		Complex *cpx = new Complex();
		Number *base = cpx->convert(this);
		Complex *base_ = SCAST_COMPLEX(base);
		Number *power = cpx->convert(number2);
		Number *result = base_->exp(power);
		delete cpx;
		return result;
	}

}

Number *Float::ex(){
	Float *result = new Float(std::exp(number_));
	return result;
}

Number *Float::sqt(){
	double number = sqrt(number_);
	if (number == number)	{
		Float *result = new Float(number);
		return result;
	}
	else{
		Complex *cpx = new Complex();
		Number *tmp = cpx->convert(this);
		Complex *tmp_ = SCAST_COMPLEX(tmp);
		Number *result = tmp_->sqt();
		return result;
	}
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
		if (fmod(trunc(number_), 2) == 0){
			Float *result = new Float(trunc(number_));
			return result;
		}
		else{
			Float *result = new Float(round(number_));
			return result;
		}
	}

}

Number *Float::sin(){
	Float *result = new Float(std::sin(number_));
	return result;
}

Number *Float::cos(){
	Float *result = new Float(std::cos(number_));
	return result;
}

Number *Float::tan(){
	Float *result = new Float(std::tan(number_));
	return result;
}

Number *Float::asin(){
	double number = std::asin(number_);
	if (number == number)	{
		Float *result = new Float(number);
		return result;
	}
	else{
		Complex *cpx = new Complex();
		Number *tmp = cpx->convert(this);
		Complex *tmp_ = SCAST_COMPLEX(tmp);
		Number *result = tmp_->asin();
		return result;
	}
}

Number *Float::acos(){
	double number = std::acos(number_);
	if (number == number)	{
		Float *result = new Float(number);
		return result;
	}
	else{
		Complex *cpx = new Complex();
		Number *tmp = cpx->convert(this);
		Complex *tmp_ = SCAST_COMPLEX(tmp);
		Number *result = tmp_->acos();
		return result;
	}
}

Number *Float::atan(){
	Float *result = new Float(std::atan(number_));
	return result;
}

Number *Float::log(){
	double number = std::log(number_);
	if (number == number)	{
		Float *result = new Float(number);
		return result;
	}
	else{
		Complex *cpx = new Complex();
		Number *tmp = cpx->convert(this);
		Complex *tmp_ = SCAST_COMPLEX(tmp);
		Number *result = tmp_->log();
		return result;
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

Number *Float::getNumerator(){
	double numerator = number_, denominator = 1;
	while (numerator != trunc(numerator)){
		numerator *= 2;
		denominator *= 2;
	}
	while (fmod(numerator, 2) == 0 && denominator != 1){
		numerator /= 2;
		denominator /= 2;
	}
	Float *result = new Float(numerator);
	return result;
}

Number *Float::getDenominator(){
	double numerator = number_, denominator = 1;
	while (numerator != trunc(numerator)){
		numerator *= 2;
		denominator *= 2;
	}
	while (fmod(numerator, 2) == 0 && denominator != 1){
		numerator /= 2;
		denominator /= 2;
	}
	Float *result = new Float(denominator);
	return result;
}

 Boolean *Float:: isZero(){
	 Boolean *result = new Boolean(number_ == 0);
	 return result;
 }

 Boolean *Float:: isNega(){
	 Boolean *result = new Boolean(number_ < 0);
	 return result;
 }

 Boolean *Float:: isPosi(){
	 Boolean *result = new Boolean(number_ > 0);
	 return result;
 }

 Boolean *Float:: isOdd(){
	 if (!isInt()->val_){
		 throw 0;
		 return NULL;
	 }
	 else{
		 Boolean *result = new Boolean(fmod(number_, 2) != 0);
		 return result;
	 }
 }

 Boolean *Float:: isEven(){
	 if (!isInt()->val_){
		 throw 0;
		 return NULL;
	 }
	 else{
		 Boolean *result = new Boolean(fmod(number_, 2) == 0);
		 return result;
	 }
 }

 Boolean *Float:: isInt(){
	 Boolean *result = new Boolean(number_ == trunc(number_));
	 return result;
 }

 Boolean *Float:: isRat(){
	 Boolean *result = new Boolean(true);
	 return result;
 }
 
 Boolean *Float:: isReal(){
	 Boolean *result = new Boolean(true);
	 return result;
 }
 
 Boolean *Float:: isCpx(){
	 Boolean *result = new Boolean(true);
	 return result;
 }
 
 Boolean *Float:: isNum(){
	 Boolean *result = new Boolean(true);
	 return result;
 }



void Float::print(){
	cout << fixed << setprecision(10) << number_;
	//printf("%.10g", number_);
	//if (number_ == trunc(number_) && number_ < 1e17) printf(".0");
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
