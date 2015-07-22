#include "Complex.h"
#include "rational.h"
#include "float.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <complex>



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
	if (real->type_ == RATIONAL && imag->type_ == RATIONAL){
		Rational *tmp = SCAST_RATIONAL(real);
		real_ = new Rational(*tmp);
		Rational *tmp2 = SCAST_RATIONAL(imag);
		imag_ = new Rational(*tmp2);
	}
	else{
		Float *flt = new Float();
		Number *tmp = flt->convert(real);
		Number *tmp2 = flt->convert(imag);
		if (!tmp || !tmp2) throw(1);
		Float *tmpf = SCAST_FLOAT(tmp);
		Float *tmp2f = SCAST_FLOAT(tmp2);
		real_ = new Float(*tmpf);
		imag_ = new Float(*tmp2f);
	}/*
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
	}*/
}

Complex::~Complex()
{
	delete real_;
	delete imag_;
}



Number *Complex::convert(Number *number2){
	//cout << "Complex::convert" << endl;
	assert(number2->type_ <= type_);
	Complex *result = new Complex();
	switch (number2->type_){
	case RATIONAL:{
		Rational *tmp = SCAST_RATIONAL(number2);
		result->real_ = new Rational(tmp->numerator_, tmp->denominator_);
		result->imag_ = new Rational();
		break;
	}
	case FLOAT:{
		Float *tmp = SCAST_FLOAT(number2);
		result->real_ = new Float(tmp->number_);
		result->imag_ = new Float();
		break;
	}
	case COMPLEX:{
		Complex *tmp = SCAST_COMPLEX(number2);
		if (tmp->real_->type_ == FLOAT){
			Float *real = SCAST_FLOAT(tmp->real_);
			Float *imag = SCAST_FLOAT(tmp->imag_);
			result->real_ = new Float(real->number_);
			result->imag_ = new Float(imag->number_);
		}
		else{
			Rational *real = SCAST_RATIONAL(tmp->real_);
			Rational *imag = SCAST_RATIONAL(tmp->imag_);
			result->real_ = new Rational(real->numerator_, real->denominator_);
			result->imag_ = new Rational(imag->numerator_, imag->denominator_);
		}
		break;
	}
	default:{
		assert(0 && "type_ not defined");
	}
	}
	return result;
}



Number *Complex::inextoex(){
	Number* real = real_->inextoex();
	Number* imag = imag_->inextoex();
	Complex *result = new Complex(real, imag);
	return result;
}

Number *Complex::extoinex(){
	Number* real = real_->extoinex();
	Number* imag = imag_->extoinex();
	Complex *result = new Complex(real, imag);
	return result;
}


Number* Complex::getreal(){
	if (real_->type_ == FLOAT){
		Float *tmp = SCAST_FLOAT(real_);
		Float *result = new Float(tmp->number_);
		return result;
	}
	else{
		Rational *tmp = SCAST_RATIONAL(real_);
		Rational *result = new Rational(tmp->numerator_, tmp->denominator_);
		return result;
	}
}

Number* Complex::getimag(){
	if (imag_->type_ == FLOAT){
		Float *tmp = SCAST_FLOAT(imag_);
		Float *result = new Float(tmp->number_);
		return result;
	}
	else{
		Rational *tmp = SCAST_RATIONAL(imag_);
		Rational *result = new Rational(tmp->numerator_, tmp->denominator_);
		return result;
	}
}

Number* Complex::torect(Number *number1,Number *number2){
	Complex *result = new Complex(number1, number2);
	return result;
}

Number* Complex::topolar(Number *number1,Number *number2){
	Float *flt = new Float();
	Number *tmp = flt->convert(number1);
	Number *tmp2 = flt->convert(number2);
	Float *tmpf = SCAST_FLOAT(tmp);
	Float *tmp2f = SCAST_FLOAT(tmp2);
	complex<double> cpx = polar(tmpf->number_, tmp2f->number_);
	Complex *result = new Complex(new Float(cpx.real()), new Float(cpx.imag()));
	return result;
}

Number* Complex::getmag(){
	Float *flt = new Float();
	Number *real = flt->convert(real_);
	Number *imag = flt->convert(imag_);
	Float *realf = SCAST_FLOAT(real);
	Float *imagf = SCAST_FLOAT(imag);
	complex<double> cpx(realf->number_, imagf->number_);
	double result_ = norm(cpx);
	Float *result = new Float(result_);
	delete flt; delete real; delete imag;
	return result;
}

Number* Complex::getang(){
	Float *flt = new Float();
	Number *real = flt->convert(real_);
	Number *imag = flt->convert(imag_);
	Float *realf = SCAST_FLOAT(real);
	Float *imagf = SCAST_FLOAT(imag);
	complex<double> cpx(realf->number_, imagf->number_);
	double result_ = arg(cpx);
	Float *result = new Float(result_);
	delete flt; delete real; delete imag;
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

//Number *Complex::mul(Number *number2){
//	Complex *tmp = SCAST_COMPLEX(number2);
//	Complex *result = new Complex();
//	// The following expressions just means a=a1a2-b1b2, b=a1b2+b1a2 
//	if (real_->type_ > tmp->real_->type_)
//	{
//		result->real_ = (real_->mul(real_->convert(tmp->real_)))->sub(imag_->mul(imag_->convert(tmp->imag_)));
//	}
//	else
//	{
//		result->real_ = ((tmp->real_->convert(real_))->mul(tmp->real_))->sub((tmp->imag_->convert(imag_))->mul(tmp->imag_));
//	}
//
//	if (imag_->type_ > tmp->imag_->type_)
//	{
//		result->imag_ = (imag_->mul(imag_->convert(tmp->real_)))->add(real_->mul(real_->convert(tmp->imag_)));
//	}
//	else
//	{
//		result->imag_ = ((tmp->imag_->convert(real_))->mul(tmp->imag_))->add((tmp->real_->convert(imag_))->mul(tmp->real_));
//	}
//
//	return result;
//}


Number *Complex::mul(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	if (real_->type_ == FLOAT || tmp->real_->type_ == FLOAT){
		Float *flt = new Float();
		Number *imag = flt->convert(imag_);
		Number *imag2 = flt->convert(tmp->imag_);
		Number *real = flt->convert(real_);
		Number *real2 = flt->convert(tmp->real_);
		Float *realf = SCAST_FLOAT(real);
		Float *real2f = SCAST_FLOAT(real2);
		Float *imagf = SCAST_FLOAT(imag);
		Float *imag2f = SCAST_FLOAT(imag2);
		complex<double> cpx1(realf->number_, imagf->number_), cpx2(real2f->number_, imag2f->number_), cpxr;
		cpxr = cpx1 * cpx2;
		Float *result_real = new Float(cpxr.real());
		Float *result_imag = new Float(cpxr.imag());
		/*if (result_imag->number_ == 0) {
			delete flt; delete imag; delete imag2; delete real; delete real2; delete result_imag;
			return result_real;
			}*/
		Complex *result = new Complex(result_real, result_imag);
		delete flt; delete imag; delete imag2; delete real; delete real2; delete result_real; delete result_imag;
		return result;
	}
	else{
		Complex *result = new Complex();
		result->real_ = (real_->mul(tmp->real_))->sub(imag_->mul(tmp->imag_));
		result->imag_ = (imag_->mul(tmp->real_))->add(real_->mul(tmp->imag_));
		return result;
	}

}


//Number *Complex::div(Number *number2){
//	Complex *tmp = SCAST_COMPLEX(number2);
//	Complex *result = new Complex();
//	if (real_->type_ > tmp->real_->type_)
//	{
//		result->real_ = ((real_->mul(real_->convert(tmp->real_)))->add(imag_->mul(imag_->convert(tmp->imag_))))
//			->div(real_->convert((tmp->real_->mul(tmp->real_))->add(tmp->imag_->mul(tmp->imag_))));
//		//result->real_ = real_->div(real_->convert(tmp->real_));
//	}
//	else
//	{
//		result->real_ = (((tmp->real_->convert(real_))->mul(tmp->real_))->add((tmp->imag_->convert(imag_))->mul(tmp->imag_)))
//			->div((tmp->real_->mul(tmp->real_))->add(tmp->imag_->mul(tmp->imag_)));
//		//result->real_ = (tmp->real_->convert(real_))->div(tmp->real_);
//	}
//
//	if (imag_->type_ > tmp->imag_->type_)
//	{
//		result->imag_ = ((imag_->mul(imag_->convert(tmp->real_)))->sub(real_->mul(real_->convert(tmp->imag_))))
//			->div(real_->convert((tmp->real_->mul(tmp->real_))->add(tmp->imag_->mul(tmp->imag_))));
//
//		//result->imag_ = imag_->div(imag_->convert(tmp->imag_));
//	}
//	else
//	{
//		result->imag_ = (((tmp->real_->convert(imag_))->mul(tmp->real_))->sub((tmp->imag_->convert(real_))->mul(tmp->imag_)))
//			->div((tmp->real_->mul(tmp->real_))->add(tmp->imag_->mul(tmp->imag_)));
//
//		//result->imag_ = (tmp->imag_->convert(imag_))->div(tmp->imag_);
//	}
//
//	return result;
//}



Number *Complex::div(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	if (real_->type_ == FLOAT || tmp->real_->type_ == FLOAT){
		Float *flt = new Float();
		Number *imag = flt->convert(imag_);
		Number *imag2 = flt->convert(tmp->imag_);
		Number *real = flt->convert(real_);
		Number *real2 = flt->convert(tmp->real_);
		Float *realf = SCAST_FLOAT(real);
		Float *real2f = SCAST_FLOAT(real2);
		Float *imagf = SCAST_FLOAT(imag);
		Float *imag2f = SCAST_FLOAT(imag2);
		complex<double> cpx1(realf->number_, imagf->number_), cpx2(real2f->number_, imag2f->number_), cpxr;
		cpxr = cpx1 / cpx2;
		Float *result_real = new Float(cpxr.real());
		Float *result_imag = new Float(cpxr.imag());
		/*if (result_imag->number_ == 0) {
			delete flt; delete imag; delete imag2; delete real; delete real2; delete result_imag;
			return result_real;
			}*/
		Complex *result = new Complex(result_real, result_imag);
		delete flt; delete imag; delete imag2; delete real; delete real2; delete result_real; delete result_imag;
		return result;
	}
	else{
		Complex *result = new Complex();
		result->real_ = ((real_->mul(tmp->real_))->add(imag_->mul(tmp->imag_)))
			->div((tmp->real_->mul(tmp->real_))->add(tmp->imag_->mul(tmp->imag_)));
		result->imag_ = ((imag_->mul(tmp->real_))->sub(real_->mul(tmp->imag_)))
			->div((tmp->real_->mul(tmp->real_))->add(tmp->imag_->mul(tmp->imag_)));
		return result;
	}

}

Boolean *Complex::les(Number *number2){return NULL;}
Boolean *Complex::lesE(Number *number2){return NULL;}
Boolean *Complex::grt(Number *number2){return NULL;}
Boolean *Complex::grtE(Number *number2){return NULL;}


Number *Complex::abs(){
	if (real_->type_ == FLOAT){
		Float *imag = SCAST_FLOAT(imag_);
		if (imag->number_ != 0) throw(1);
		return real_->abs();
	}
	else{
		Rational *imag = SCAST_RATIONAL(imag_);
		if (imag->numerator_.number_[0] != '0') throw(1);
		return real_->abs();
	}
}

Number *Complex::quo(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	if (real_->type_ != RATIONAL || tmp->real_->type_ != RATIONAL){
		Float *flt = new Float();
		Number *imag = flt->convert(imag_);
		Number *imag2 = flt->convert(tmp->imag_);
		Number *real = flt->convert(real_);
		Number *real2 = flt->convert(tmp->real_);
		Float *imagf = SCAST_FLOAT(imag);
		Float *imag2f = SCAST_FLOAT(imag2);
		if (imagf->number_ != 0 || imag2f->number_ != 0) throw(1);
		delete flt;
		return real->quo(real2);
	}
	else{
		Rational *imagr = SCAST_RATIONAL(imag_);
		Rational *imag2r = SCAST_RATIONAL(tmp->imag_);
		if (imagr->numerator_.number_[0] != '0' || imag2r->numerator_.number_[0] != '0') throw(1);
		return real_->quo(tmp->real_);
	}
}

Number *Complex::rem(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	if (real_->type_ != RATIONAL || tmp->real_->type_ != RATIONAL){
		Float *flt = new Float();
		Number *imag = flt->convert(imag_);
		Number *imag2 = flt->convert(tmp->imag_);
		Number *real = flt->convert(real_);
		Number *real2 = flt->convert(tmp->real_);
		Float *imagf = SCAST_FLOAT(imag);
		Float *imag2f = SCAST_FLOAT(imag2);
		if (imagf->number_ != 0 || imag2f->number_ != 0) throw(1);
		delete flt;
		return real->rem(real2);
	}
	else{
		Rational *imagr = SCAST_RATIONAL(imag_);
		Rational *imag2r = SCAST_RATIONAL(tmp->imag_);
		if (imagr->numerator_.number_[0] != '0' || imag2r->numerator_.number_[0] != '0') throw(1);
		return real_->rem(tmp->real_);
	}
}


Number *Complex::mod(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	if (real_->type_ != RATIONAL || tmp->real_->type_ != RATIONAL){
		Float *flt = new Float();
		Number *imag = flt->convert(imag_);
		Number *imag2 = flt->convert(tmp->imag_);
		Number *real = flt->convert(real_);
		Number *real2 = flt->convert(tmp->real_);
		Float *imagf = SCAST_FLOAT(imag);
		Float *imag2f = SCAST_FLOAT(imag2);
		if (imagf->number_ != 0 || imag2f->number_ != 0) throw(1);
		delete flt;
		return real->mod(real2);
	}
	else{
		Rational *imagr = SCAST_RATIONAL(imag_);
		Rational *imag2r = SCAST_RATIONAL(tmp->imag_);
		if (imagr->numerator_.number_[0] != '0' || imag2r->numerator_.number_[0] != '0') throw(1);
		return real_->mod(tmp->real_);
	}
}

Number *Complex::gcd(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	if (real_->type_ != RATIONAL || tmp->real_->type_ != RATIONAL){
		Float *flt = new Float();
		Number *imag = flt->convert(imag_);
		Number *imag2 = flt->convert(tmp->imag_);
		Number *real = flt->convert(real_);
		Number *real2 = flt->convert(tmp->real_);
		Float *imagf = SCAST_FLOAT(imag);
		Float *imag2f = SCAST_FLOAT(imag2);
		if (imagf->number_ != 0 || imag2f->number_ != 0) throw(1);
		delete flt;
		return real->gcd(real2);
	}
	else{
		Rational *imagr = SCAST_RATIONAL(imag_);
		Rational *imag2r = SCAST_RATIONAL(tmp->imag_);
		if (imagr->numerator_.number_[0] != '0' || imag2r->numerator_.number_[0] != '0') throw(1);
		return real_->gcd(tmp->real_);
	}
}

Number *Complex::lcm(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	if (real_->type_ != RATIONAL || tmp->real_->type_ != RATIONAL){
		Float *flt = new Float();
		Number *imag = flt->convert(imag_);
		Number *imag2 = flt->convert(tmp->imag_);
		Number *real = flt->convert(real_);
		Number *real2 = flt->convert(tmp->real_);
		Float *imagf = SCAST_FLOAT(imag);
		Float *imag2f = SCAST_FLOAT(imag2);
		if (imagf->number_ != 0 || imag2f->number_ != 0) throw(1);
		delete flt;
		return real->lcm(real2);
	}
	else{
		Rational *imagr = SCAST_RATIONAL(imag_);
		Rational *imag2r = SCAST_RATIONAL(tmp->imag_);
		if (imagr->numerator_.number_[0] != '0' || imag2r->numerator_.number_[0] != '0') throw(1);
		return real_->lcm(tmp->real_);
	}
}

//Number *Complex::exp(Number *number2){
//	Complex *tmp = SCAST_COMPLEX(number2);
//	if (real_->type_ != RATIONAL || tmp->real_->type_ != RATIONAL){
//		Float *flt = new Float();
//		Number *imag = flt->convert(imag_);
//		Number *imag2 = flt->convert(tmp->imag_);
//		Number *real = flt->convert(real_);
//		Number *real2 = flt->convert(tmp->real_);
//		Float *imagf = SCAST_FLOAT(imag);
//		Float *imag2f = SCAST_FLOAT(imag2);
//		//if (imagf->number_ != 0 || imag2f->number_ != 0) throw(1);
//		if (imagf->number_ == 0 && imag2f->number_ == 0) {
//			delete flt;
//			return real->exp(real2);
//		}
//		//So much pointers should be deleted here...
//		delete flt; delete imag; delete imag2; delete real; delete real2;
//	}
//	else{
//		Rational *imagr = SCAST_RATIONAL(imag_);
//		Rational *imag2r = SCAST_RATIONAL(tmp->imag_);
//		//if (imagr->numerator_.number_[0] != '0' || imag2r->numerator_.number_[0] != '0') throw(1);
//		if (imagr->numerator_.number_[0] == '0' && imag2r->numerator_.number_[0] == '0'){
//			return real_->exp(tmp->real_);
//		}
//		//It looks like nothing needs to be deleted here...
//	}
//	Float *flt = new Float();
//	Number *imag = flt->convert(imag_);
//	Number *imag2 = flt->convert(tmp->imag_);
//	Number *real = flt->convert(real_);
//	Number *real2 = flt->convert(tmp->real_);
//	Float *realf = SCAST_FLOAT(real);
//	Float *real2f = SCAST_FLOAT(real2);
//	Float *imagf = SCAST_FLOAT(imag);
//	Float *imag2f = SCAST_FLOAT(imag2);
//	complex<double> cpx1(realf->number_, imagf->number_), cpx2(real2f->number_, imag2f->number_),cpxr;
//	cpxr = pow(cpx1, cpx2);
//	Float *result_real = new Float(cpxr.real());
//	Float *result_imag = new Float(cpxr.imag());
//	Complex *result = new Complex(result_real, result_imag);
//	delete flt; delete imag; delete imag2; delete real; delete real2; delete result_real; delete result_imag;
//	return result;
//}


Number *Complex::exp(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Float *flt = new Float();
	Number *imag = flt->convert(imag_);
	Number *imag2 = flt->convert(tmp->imag_);
	Number *real = flt->convert(real_);
	Number *real2 = flt->convert(tmp->real_);
	Float *realf = SCAST_FLOAT(real);
	Float *real2f = SCAST_FLOAT(real2);
	Float *imagf = SCAST_FLOAT(imag);
	Float *imag2f = SCAST_FLOAT(imag2);
	complex<double> cpx1(realf->number_, imagf->number_), cpx2(real2f->number_, imag2f->number_), cpxr;
	cpxr = pow(cpx1, cpx2);
	Float *result_real = new Float(cpxr.real());
	Float *result_imag = new Float(cpxr.imag());
	if (result_imag->number_ == 0) {
		delete flt; delete imag; delete imag2; delete real; delete real2; delete result_imag;
		return result_real;
	}
	Complex *result = new Complex(result_real, result_imag);
	delete flt; delete imag; delete imag2; delete real; delete real2; delete result_real; delete result_imag;
	return result;
}

//Number *Complex::sqt(){
//	if (real_->type_ == FLOAT){
//		Float *imagf1 = SCAST_FLOAT(imag_);
//		if (imagf1->number_ == 0)	return real_->sqt();
//	}
//	else{
//		Rational *imagr = SCAST_RATIONAL(imag_);
//		if (imagr->numerator_.number_[0] == '0')	return real_->sqt();
//	}
//	Float *flt = new Float();
//	Number *real = flt->convert(real_);
//	Number *imag = flt->convert(imag_);
//	Float *realf = SCAST_FLOAT(real);
//	Float *imagf = SCAST_FLOAT(imag);
//	complex<double> cpx(realf->number_, imagf->number_);
//	cpx = sqrt(cpx);
//	Float *result_real = new Float(cpx.real());
//	Float *result_imag = new Float(cpx.imag());
//	Complex *result = new Complex(result_real, result_imag);
//	delete flt; delete result_real; delete result_imag; delete real; delete imag;
//	return result;
//}



Number *Complex::sqt(){
	Float *flt = new Float();
	Number *real = flt->convert(real_);
	Number *imag = flt->convert(imag_);
	Float *realf = SCAST_FLOAT(real);
	Float *imagf = SCAST_FLOAT(imag);
	complex<double> cpx(realf->number_, imagf->number_);
	cpx = sqrt(cpx);
	Float *result_real = new Float(cpx.real());
	Float *result_imag = new Float(cpx.imag());
	if (result_imag->number_ == 0) {
		delete flt; delete result_imag; delete real; delete imag;
		return result_real;
	}
	Complex *result = new Complex(result_real, result_imag);
	delete flt; delete result_real; delete result_imag; delete real; delete imag;
	return result;
}


Number *Complex::flr(){
	if (real_->type_ == FLOAT){
		Float *imag = SCAST_FLOAT(imag_);
		if (imag->number_ != 0) throw(1);
		return real_->flr();
	}
	else{
		Rational *imag = SCAST_RATIONAL(imag_);
		if (imag->numerator_.number_[0] != '0') throw(1);
		return real_->flr();
	}
}

Number *Complex::cel(){
	if (real_->type_ == FLOAT){
		Float *imag = SCAST_FLOAT(imag_);
		if (imag->number_ != 0) throw(1);
		return real_->cel();
	}
	else{
		Rational *imag = SCAST_RATIONAL(imag_);
		if (imag->numerator_.number_[0] != '0') throw(1);
		return real_->cel();
	}
}

Number *Complex::trc(){
	if (real_->type_ == FLOAT){
		Float *imag = SCAST_FLOAT(imag_);
		if (imag->number_ != 0) throw(1);
		return real_->trc();
	}
	else{
		Rational *imag = SCAST_RATIONAL(imag_);
		if (imag->numerator_.number_[0] != '0') throw(1);
		return real_->trc();
	}
}

Number *Complex::rnd(){
	if (real_->type_ == FLOAT){
		Float *imag = SCAST_FLOAT(imag_);
		if (imag->number_ != 0) throw(1);
		return real_->rnd();
	}
	else{
		Rational *imag = SCAST_RATIONAL(imag_);
		if (imag->numerator_.number_[0] != '0') throw(1);
		return real_->rnd();
	}
}

Number *Complex::ex(){return NULL;}

Number *Complex::sin(){return NULL;}
Number *Complex::cos(){return NULL;}
Number *Complex::tan(){return NULL;}
Number *Complex::asin(){return NULL;}
Number *Complex::acos(){return NULL;}
Number *Complex::atan(){return NULL;}
Number *Complex::log(){ return NULL; }

Number *Complex::maxi(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	if (real_->type_ != RATIONAL || tmp->real_->type_ != RATIONAL){
		Float *flt = new Float();
		Number *imag = flt->convert(imag_);
		Number *imag2 = flt->convert(tmp->imag_);
		Number *real = flt->convert(real_);
		Number *real2 = flt->convert(tmp->real_);
		Float *imagf = SCAST_FLOAT(imag);
		Float *imag2f = SCAST_FLOAT(imag2);
		if (imagf->number_ != 0 || imag2f->number_ != 0) throw(1);
		delete flt;
		return real->maxi(real2);
	}
	else{
		Rational *imagr = SCAST_RATIONAL(imag_);
		Rational *imag2r = SCAST_RATIONAL(tmp->imag_);
		if (imagr->numerator_.number_[0] != '0' || imag2r->numerator_.number_[0] != '0') throw(1);
		return real_->maxi(tmp->real_);
	}
}

Number *Complex::mini(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	if (real_->type_ != RATIONAL || tmp->real_->type_ != RATIONAL){
		Float *flt = new Float();
		Number *imag = flt->convert(imag_);
		Number *imag2 = flt->convert(tmp->imag_);
		Number *real = flt->convert(real_);
		Number *real2 = flt->convert(tmp->real_);
		Float *imagf = SCAST_FLOAT(imag);
		Float *imag2f = SCAST_FLOAT(imag2);
		if (imagf->number_ != 0 || imag2f->number_ != 0) throw(1);
		delete flt;
		return real->mini(real2);
	}
	else{
		Rational *imagr = SCAST_RATIONAL(imag_);
		Rational *imag2r = SCAST_RATIONAL(tmp->imag_);
		if (imagr->numerator_.number_[0] != '0' || imag2r->numerator_.number_[0] != '0') throw(1);
		return real_->mini(tmp->real_);
	}
}

Number *Complex::getNumerator(){
	if (real_->type_ == FLOAT){
		Float *imag = SCAST_FLOAT(imag_);
		if (imag->number_ != 0) throw(1);
		return real_->getNumerator();
	}
	else{
		Rational *imag = SCAST_RATIONAL(imag_);
		if (imag->numerator_.number_[0] != '0') throw(1);
		return real_->getNumerator();
	}
}


Number *Complex::getDenominator(){
	if (real_->type_ == FLOAT){
		Float *imag = SCAST_FLOAT(imag_);
		if (imag->number_ != 0) throw(1);
		return real_->getDenominator();
	}
	else{
		Rational *imag = SCAST_RATIONAL(imag_);
		if (imag->numerator_.number_[0] != '0') throw(1);
		return real_->getDenominator();
	}
}

Boolean *Complex::isZero(){return NULL;}
Boolean *Complex::isNega(){return NULL;}
Boolean *Complex::isPosi(){return NULL;}
Boolean *Complex::isOdd(){return NULL;}
Boolean *Complex::isEven(){return NULL;}
Boolean *Complex::isInt(){return NULL;}
Boolean *Complex::isRat(){return NULL;}
Boolean *Complex::isReal(){return NULL;}
Boolean *Complex::isCpx(){return NULL;}
Boolean *Complex::isNum(){return NULL;}

Complex *Complex::from_string(char *expression){
	//cout << "Complex::from_string" << endl;
	string exp = expression;
	if (exp[exp.length() - 1] != 'i' && exp[exp.length() - 1] != 'I') return NULL;
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
		if (imag->number_ >= 0){
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