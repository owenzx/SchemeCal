#include "Complex.h"
#include "rational.h"
#include "float.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>



bool Rational::checkstring(const string &s){
	if (s[0] != '+' && s[0] != '-'){
		if (s[0]<'0' || s[0] > '9') return false;
	}
	for (int i = 1; i < s.length(); ++i){
		if (s[i]<'0' || s[i] > '9') return false;
	}
	return true;
}


Complex::Complex(string real, string imag)
{
	const char* real2(real.c_str());
	const char* imag2(imag.c_str());

	real_ = Rational::from_string(real2);
	if (!real_) { real_ = Float::from_string(real2); }
	if (real_ == NULL){ throw 0; }

	imag_ = Rational::from_string(imag2);
	if (!imag_) { real_ = Float::from_string(imag2); }
	if (imag_ == NULL){ throw 0; }
}


Complex::Complex(Number *real, Number *imag = new Rational(0, 1)){
	switch (real->type_){
	case RATIONAL:{
		Rational *tmp = SCAST_RATIONAL(real);
		real_ = new Rational(*tmp);
		break;
	}
	case FLOAT:{
		Float *tmp = SCAST_FLOAT(real);
		real_ = new Float(*tmp);
		break;
	}
	default:{
		assert(0 && "type_ not defined");
	}
	}
	switch (imag->type_){
	case RATIONAL:{
		Rational *tmp = SCAST_RATIONAL(imag);
		imag_ = new Rational(*tmp);
		break;
	}
	case FLOAT:{
		Float *tmp = SCAST_FLOAT(imag);
		imag_ = new Float(*tmp);
		break;
	}
	default:{
		assert(0 && "type_ not defined");
	}
	}
}

Complex::~Complex()
{
}



Number *Complex::convert(Number *number2){
	assert(number2->type_ <= type_);
	Complex *result = new Complex();
	switch (number2->type_){
	case RATIONAL:{
		Rational *tmp = SCAST_RATIONAL(number2);
		break;
	}
	case FLOAT:{
		Float *tmp = SCAST_FLOAT(number2);
		break;
	}
	case COMPLEX:{
		Complex *tmp = SCAST_COMPLEX(number2);
		result->real_ = tmp->real_;
		result->imag_ = tmp->imag_;
		break;
	}
	default:{
		assert(0 && "type_ not defined");
	}
	}
	return result;
}

Number *Complex::add(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	if (real_->type_ > tmp->real_->type_)
	{
		result->real_ = real_->add(real_->convert(tmp->real_));
	}
	else
	{
		result->real_ = (tmp->real_->convert(real_))->add(tmp->real_);
	}

	if (imag_->type_ > tmp->imag_->type_)
	{
		result->imag_ = imag_->add(imag_->convert(tmp->imag_));
	}
	else
	{
		result->imag_ = (tmp->imag_->convert(imag_))->add(tmp->imag_);
	}

	return result;
}

Number *Complex::sub(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	if (real_->type_ > tmp->real_->type_)
	{
		result->real_ = real_->sub(real_->convert(tmp->real_));
	}
	else
	{
		result->real_ = (tmp->real_->convert(real_))->sub(tmp->real_);
	}

	if (imag_->type_ > tmp->imag_->type_)
	{
		result->imag_ = imag_->sub(imag_->convert(tmp->imag_));
	}
	else
	{
		result->imag_ = (tmp->imag_->convert(imag_))->sub(tmp->imag_);
	}

	return result;
}

Number *Complex::mul(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	if (real_->type_ > tmp->real_->type_)
	{
		result->real_ = real_->mul(real_->convert(tmp->real_));
	}
	else
	{
		result->real_ = (tmp->real_->convert(real_))->mul(tmp->real_);
	}

	if (imag_->type_ > tmp->imag_->type_)
	{
		result->imag_ = imag_->mul(imag_->convert(tmp->imag_));
	}
	else
	{
		result->imag_ = (tmp->imag_->convert(imag_))->mul(tmp->imag_);
	}

	return result;
}

Number *Complex::div(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	if (real_->type_ > tmp->real_->type_)
	{
		result->real_ = real_->div(real_->convert(tmp->real_));
	}
	else
	{
		result->real_ = (tmp->real_->convert(real_))->div(tmp->real_);
	}

	if (imag_->type_ > tmp->imag_->type_)
	{
		result->imag_ = imag_->div(imag_->convert(tmp->imag_));
	}
	else
	{
		result->imag_ = (tmp->imag_->convert(imag_))->div(tmp->imag_);
	}

	return result;
}



Complex *Complex::from_string(char *expression){
	string exp = expression;
	if (exp[exp.length() - 1] != 'i') return NULL;
	int imag_start = 0;
	for (int i = exp.length() - 1; i >= 0; --i){
		if ((exp[i] == '+' || exp[i] == '-') && (i == 0 || (exp[i - 1] >= '0' && exp[i - 1] <= '9'))){
			imag_start = i;
			break;
		}
	}
	if (imag_start!=0){
		string real = exp.substr(0, imag_start);
		if (!checkstring(real)) return NULL;
		string imag = exp.substr(imag_start, exp.length() - imag_start-1);
		if (imag == "+") imag = "1";
		else if (imag == "-") imag = "-1";
		else if (!checkstring(imag)) return NULL;
		return new Complex(real, imag);
	}
	else{
		string imag = exp.substr(0,exp.length()-1);
		if (imag == "" || imag == "+") imag = "1";
		else if (imag == "-") imag = "-1";
		else if (!checkstring(imag)) return NULL;
		return new Complex("0", imag);
	}
}

