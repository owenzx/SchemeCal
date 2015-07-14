#include "Complex.h"
#include "rational.h"
#include "float.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

//
//
//bool Complex::checkstring(const string &s){
//	if (s[0] != '+' && s[0] != '-'){
//		if (s[0]<'0' || s[0] > '9') return false;
//	}
//	for (int i = 1; i < s.length(); ++i){
//		if (s[i]<'0' || s[i] > '9') return false;
//	}
//	return true;
//}


Complex::Complex(string real, string imag)
{
	type_ = COMPLEX;
	/*cout << "Complex::Complex" << endl;
	cout << "real=" << real << endl;
	cout << "imag=" << imag << endl;*/
	const char* real2(real.c_str());
	const char* imag2(imag.c_str());
	Float *flt = new Float();
	real_ = Rational::from_string(real2);
	imag_ = Rational::from_string(imag2);
	if (!real_ || !imag_){
		if (!imag_) imag_ = Float::from_string(imag2);
		else imag_ = flt->convert(imag_);
		if (!real_) real_ = Float::from_string(real2);
		else real_ = flt->convert(real_);
		if (!real_ || !imag_) { throw(1); }
	}
	//cout << "Complex::Complex FINISH" << endl;
}


Complex::Complex(Number *real, Number *imag){
	type_ = COMPLEX;
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
	//cout << "Complex::convert" << endl;
	assert(number2->type_ <= type_);
	Complex *result = new Complex();
	switch (number2->type_){
	case RATIONAL:{
		Rational *tmp = SCAST_RATIONAL(number2);
		result->real_ = tmp;
		result->imag_ = new Rational();
		break;
	}
	case FLOAT:{
		Float *tmp = SCAST_FLOAT(number2);
		result->real_ = tmp;
		result->imag_ = new Float();
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
	//cout << "Complex::add" << endl;
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
	// The following expressions just means a=a1a2-b1b2, b=a1b2+b1a2 
	if (real_->type_ > tmp->real_->type_)
	{
		result->real_ = (real_->mul(real_->convert(tmp->real_)))->sub(imag_->mul(imag_->convert(tmp->imag_)));
	}
	else
	{
		result->real_ = ((tmp->real_->convert(real_))->mul(tmp->real_))->sub((tmp->imag_->convert(imag_))->mul(tmp->imag_));
	}

	if (imag_->type_ > tmp->imag_->type_)
	{
		result->imag_ = (imag_->mul(imag_->convert(tmp->real_)))->add(real_->mul(real_->convert(tmp->imag_)));
	}
	else
	{
		result->imag_ = ((tmp->imag_->convert(real_))->mul(tmp->imag_))->add((tmp->real_->convert(imag_))->mul(tmp->real_));
	}

	return result;
}

Number *Complex::div(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	if (real_->type_ > tmp->real_->type_)
	{
		result->real_ = ((real_->mul(real_->convert(tmp->real_)))->add(imag_->mul(imag_->convert(tmp->imag_))))
			->div(real_->convert((tmp->real_->mul(tmp->real_))->add(tmp->imag_->mul(tmp->imag_))));
		//result->real_ = real_->div(real_->convert(tmp->real_));
	}
	else
	{
		result->real_ = (((tmp->real_->convert(real_))->mul(tmp->real_))->add((tmp->imag_->convert(imag_))->mul(tmp->imag_)))
			->div((tmp->real_->mul(tmp->real_))->add(tmp->imag_->mul(tmp->imag_)));
		//result->real_ = (tmp->real_->convert(real_))->div(tmp->real_);
	}

	if (imag_->type_ > tmp->imag_->type_)
	{
		result->imag_ = ((imag_->mul(imag_->convert(tmp->real_)))->sub(real_->mul(real_->convert(tmp->imag_))))
			->div(real_->convert((tmp->real_->mul(tmp->real_))->add(tmp->imag_->mul(tmp->imag_))));

		//result->imag_ = imag_->div(imag_->convert(tmp->imag_));
	}
	else
	{
		result->imag_ = (((tmp->real_->convert(imag_))->mul(tmp->real_))->sub((tmp->imag_->convert(real_))->mul(tmp->imag_)))
			->div((tmp->real_->mul(tmp->real_))->add(tmp->imag_->mul(tmp->imag_)));

		//result->imag_ = (tmp->imag_->convert(imag_))->div(tmp->imag_);
	}

	return result;
}

Number *Complex::abs(){
	return NULL;
}

Number *Complex::quo(Number *number2){
	return NULL;
}

Number *Complex::rem(Number *number2){
	return NULL;
}


Number *Complex::mod(Number *number2){
	return NULL;
}

Number *Complex::gcd(Number *number2){
	return NULL;
}

Number *Complex::lcm(Number *number2){
	return NULL;
}

Number *Complex::exp(Number *number2){
	return NULL;
}

Number *Complex::sqt(){
	return NULL;
}


Number *Complex::flr(){
	return NULL;
}

Number *Complex::cel(){
	return NULL;
}

Number *Complex::trc(){
	return NULL;
}

Number *Complex::rnd(){
	return NULL;
}

Number *Complex::maxi(Number *number2){
	return NULL;
}

Number *Complex::mini(Number *number2){
	return NULL;
}



Complex *Complex::from_string(char *expression){
	//cout << "Complex::from_string" << endl;
	string exp = expression;
	if (exp[exp.length() - 1] != 'i') return NULL;
	int imag_start = 0;
	for (int i = exp.length() - 1; i >= 0; --i){
		if ((exp[i] == '+' || exp[i] == '-') && (i == 0 || (exp[i - 1] >= '0' && exp[i - 1] <= '9'))){
			imag_start = i;
			break;
		}
	}
	if (imag_start != 0){
		string real = exp.substr(0, imag_start);
		//if (!checkstring(real)) return NULL;
		string imag = exp.substr(imag_start, exp.length() - imag_start - 1);
		if (imag == "+") imag = "1";
		else if (imag == "-") imag = "-1";
		//else if (!checkstring(imag)) return NULL;
		return new Complex(real, imag);
	}
	else{
		string imag = exp.substr(0, exp.length() - 1);
		if (imag == "" || imag == "+") imag = "1";
		else if (imag == "-") imag = "-1";
		//else if (!checkstring(imag)) return NULL;
		return new Complex("0", imag);
	}
}

void Complex::print(){
	if (real_->type_ == FLOAT){
		Float *real = SCAST_FLOAT(real_);
		Float *imag = SCAST_FLOAT(imag_);
		real->print();
		if (imag->number_ > 0){
			printf("+");
		}
		imag->print();
		printf("i");
	}
	else if (real_->type_ == RATIONAL){
		Rational *real = SCAST_RATIONAL(real_);
		Rational *imag = SCAST_RATIONAL(imag_);
		if (!imag->numerator_){
			if (!real->numerator_){
				printf("0");
			}
			else{
				real->print();
			}
		}
		else{
			real->print();
			if (!(imag->numerator_.number_[0] == '0' || imag->numerator_.number_[0] == '-')){
				printf("+");
			}
			imag->print();
			printf("i");
		}
	}

}