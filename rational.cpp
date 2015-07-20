#include "rational.h"
#include "float.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

bool Rational::isInt() const{
	LongInt one(1);
	return (denominator_.number_== one.number_);
}


bool Rational::greater(Number *number2){
	Number *result = this->sub(number2);
	Rational *tmp = SCAST_RATIONAL(result);
	return tmp->numerator_.number_[0] == '+';
}

bool Rational::checkstring(const string &s){
	if (s[0] != '+' && s[0] != '-'){
		if (s[0]<'0' || s[0] > '9') return false;
	}
	for (int i = 1; i < s.length(); ++i){
		if (s[i]<'0' || s[i] > '9') return false;
	}
	return true;
}

Rational::Rational(string numerator, string denominator) : numerator_(numerator),
denominator_(denominator){
	type_ = RATIONAL;
	//std::cout << "Before REDUCE" << std::endl;
	reduce();
}

Rational::Rational(LongInt numerator, LongInt denominator) : numerator_(numerator),
denominator_(denominator){
	type_ = RATIONAL;
	reduce();
}


Rational::~Rational(){

}

void Rational::reduce(){
	//if (!denominator_) throw ('a');
	assert(denominator_ && "denominator is zero");
	if (!numerator_){
		denominator_ = 1;
		return;
	}
	LongInt big, small, tmp;
	big = max(numerator_, denominator_);
	small = min(numerator_, denominator_);
	while (tmp = big % small){
		//big.print();
		//cout << endl;
		//small.print();
		//cout << endl << endl;
		big = small;
		small = tmp;
	}
	numerator_ = numerator_ / small;
	denominator_ = denominator_ / small;
	if (denominator_ < LongInt(0)){
		numerator_ = LongInt(0) - numerator_;
		denominator_ = LongInt(0) - denominator_;
	}
}



Number *Rational::inextoex(){
	Rational *result = new Rational(numerator_, denominator_);
	return result;
}

Number *Rational::extoinex(){
	Float *flt = new Float();
	Number *result = flt->convert(this);
	delete flt;
	return result;
}


Number *Rational::convert(Number *number2){
	assert(number2->type_ <= type_);
	Rational *result = new Rational();
	switch (number2->type_){
	case RATIONAL:{
		Rational *tmp = SCAST_RATIONAL(number2);
		result->numerator_ = tmp->numerator_;
		result->denominator_ = tmp->denominator_;
		break;
	}
	default:
		assert(0 && "type_ not defined");
	}
	result->reduce();
	return result;
}

Number *Rational::add(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_*tmp->denominator_ + denominator_*tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::sub(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::mul(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_ * tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::div(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_ * tmp->denominator_;
	result->denominator_ = denominator_ * tmp->numerator_;
	result->reduce();
	return result;
}

Number *Rational::abs(){
	LongInt denominator = denominator_;
	LongInt numerator= numerator_;
	if (numerator_.number_[0] == '-') numerator.number_[0] = '+';
	Rational *result = new Rational(numerator,denominator);
	return result;
}

Number *Rational::quo(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	assert(isInt() && tmp->isInt() && "These numbers are not integers!");
	Rational *result = new Rational(numerator_/(tmp->numerator_),LongInt(1));
	return result;
}

Number *Rational::rem(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	assert(isInt() && tmp->isInt() && "These numbers are not integers!");
	Rational *result = new Rational(numerator_ % (tmp->numerator_), LongInt(1));
	return result;
}


Number *Rational::mod(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	assert(isInt() && tmp->isInt() && "These numbers are not integers!");
	Rational *result;
	if (LongInt(0)<numerator_*(tmp->numerator_) || LongInt(0).number_==(numerator_*(tmp->numerator_)).number_) result = new Rational(numerator_ % (tmp->numerator_), LongInt(1));
	else {
		result = new Rational(tmp->numerator_, LongInt(1));
		result = SCAST_RATIONAL(result->add(new Rational(numerator_ % (tmp->numerator_), LongInt(1))));
	}
	return result;
}

Number *Rational::gcd(Number *number2){
	Number *tmp2 = number2->abs();
	Rational *tmp = SCAST_RATIONAL(tmp2);
	assert(isInt() && tmp->isInt() && "These numbers are not integers!");
	if (numerator_.number_[0] == '0') {
		Rational *result = new Rational(tmp->numerator_,LongInt(1));
		return result;
	}
	else if (tmp->numerator_.number_[0] == '0') {
		Rational *result = new Rational(numerator_, LongInt(1));
		return result;
	}
	LongInt big = max(numerator_, tmp->numerator_);
	LongInt small = min(numerator_, tmp->numerator_);
	LongInt t;
	while (t = big % small){
		big = small;
		small = t;
	}
	Rational *result = new Rational(small,LongInt(1));
	return result;
}

Number *Rational::lcm(Number *number2){
	Number *tmp2 = number2->abs();
	Rational *tmp = SCAST_RATIONAL(tmp2);
	assert(isInt() && tmp->isInt() && "These numbers are not integers!");
	if (numerator_.number_[0] == '0' && tmp->numerator_.number_[0] == '0'){
		Rational *result = new Rational(LongInt(0),LongInt(1));
		return result;
	}
	Rational *result = SCAST_RATIONAL(this->mul(number2)->div(gcd(number2)));
	return result;
}

Number *Rational::exp(Number *number2){
	Float *flt = new Float();
	Number *base = flt->convert(this);
	Float *base_ = SCAST_FLOAT(base);
	Number *power = flt->convert(number2);
	Number *result = base_->exp(power);
	delete flt;
	return result;
}

Number *Rational::sqt(){
	Float *flt = new Float();
	Number *tmp = flt->convert(this);
	Float *tmp_ = SCAST_FLOAT(tmp);
	Number *result = tmp_->sqt();
	return result;
}


Number *Rational::flr(){
	Rational *result;
	if (isInt()) result = new Rational(*this);
	else {
		if (numerator_.number_[0] == '-'){
			result = new Rational(numerator_ / denominator_ - LongInt(1), LongInt(1));
		}
		else{
			result = new Rational(numerator_ / denominator_, LongInt(1));
		}
	}
	return result;
}

Number *Rational::cel(){
	Rational *result;
	if (isInt()) result = new Rational(*this);
	else {
		if (numerator_.number_[0] == '+'){
			result = new Rational(numerator_ / denominator_ + LongInt(1), LongInt(1));
		}
		else{
			result = new Rational(numerator_ / denominator_, LongInt(1));
		}
	}
	return result;
}

Number *Rational::trc(){
	Rational *result = new Rational(numerator_/denominator_,LongInt(1));
	return result;
}

Number *Rational::rnd(){
	Number *intPart = trc();
	Number *decPart = sub(intPart);
	Number *adecPart = decPart->abs();
	Number *aintPart = intPart->abs();
	Rational *adecPart_ = SCAST_RATIONAL(adecPart);
	Rational *aintPart_ = SCAST_RATIONAL(aintPart);
	Rational *half = new Rational(LongInt(1), LongInt(2));
	Rational *one = new Rational(LongInt(1), LongInt(1));
	if (adecPart_->greater(half)){
		if (this->numerator_.number_[0] == '+'){
			Number *result = intPart->add(one);
			delete one; delete half; delete adecPart; delete aintPart; delete intPart; delete decPart;
			return result;
		}
		else{
			Number *result = intPart->sub(one);
			delete one; delete half; delete adecPart; delete aintPart; delete intPart; delete decPart;
			return result;
		}
	}
	else if (*adecPart_ == *half){
		if (aintPart_->numerator_ % LongInt(2) ){
			if (this->numerator_.number_[0] == '+'){
				Number *result = intPart->add(one);
				delete one; delete half; delete adecPart; delete aintPart; delete intPart; delete decPart;
				return result;
			}
			else{
				Number *result = intPart->sub(one);
				delete one; delete half; delete adecPart; delete aintPart; delete intPart; delete decPart;
				return result;
			}
		}
		else{
			delete one; delete half; delete adecPart; delete aintPart; delete decPart;
			return intPart;
		}
	}
	else{
		delete one; delete half; delete adecPart; delete aintPart; delete decPart;
		return intPart;
	}
}

Number *Rational::maxi(Number *number2){
	Rational *result;
	Rational *tmp = SCAST_RATIONAL(number2);
	if (this->greater(number2)){
		return (result = new Rational(this->numerator_,this->denominator_));
	}
	else{
		return (result = new Rational(tmp->numerator_,tmp->denominator_));
	}
}

Number *Rational::mini(Number *number2){
	Rational *result;
	Rational *tmp = SCAST_RATIONAL(number2);
	if (!this->greater(number2)){
		return (result = new Rational(this->numerator_, this->denominator_));
	}
	else{
		return (result = new Rational(tmp->numerator_, tmp->denominator_));
	}
}


Number *Rational::getNumerator(){
	Rational *result = new Rational(numerator_, LongInt(1));
	return result;
}

Number *Rational::getDenominator(){
	Rational *result = new Rational(denominator_, LongInt(1));
	return result;
}


void Rational::print(){
	numerator_.print();
	if (denominator_ != (LongInt)1){
		printf("/");
		denominator_.print();
	}
	//printf("\n");
}




Rational *Rational::from_string(const char *expression){
	string exp = expression;
	if (exp.find('.') != exp.npos || exp.find('e') != exp.npos) return NULL;
	if (exp.find('/') != exp.npos){
		string numerator = exp.substr(0, exp.find('/'));
		if (!checkstring(numerator)) return NULL;
		string denominator = exp.substr(exp.find('/') + 1, exp.length() - exp.find('/') - 1);
		if (!checkstring(denominator)) return NULL;
		return new Rational(numerator, denominator);
	}
	else{
		string numerator = exp;
		if (!checkstring(numerator)) return NULL;
		return new Rational(numerator, "1");
	}
}

bool Rational::operator==(const Rational &tmp) const{
	return (numerator_.number_ == tmp.numerator_.number_ && denominator_.number_ == tmp.denominator_.number_);
}

//Rational *Rational::from_string(char *expression){
//	char* end_pointerr;
//	char *separate_pos = strchr(expression, '/');
//	if (separate_pos){
//		int numerator = (int)strtol(expression, &end_pointerr, 10);
//		if (end_pointerr == expression || end_pointerr != separate_pos)
//			return NULL;
//		int denominator = (int)strtol(separate_pos + 1, &end_pointerr, 10);
//		if (end_pointerr == separate_pos + 1 || end_pointerr != expression + strlen(expression))
//			return NULL;
//		return new Rational(numerator, denominator);
//	}
//	else{
//		int numerator = (int)strtol(expression, &end_pointerr, 10);
//		if (end_pointerr == expression || end_pointerr != expression + strlen(expression))
//			return NULL;
//		return new Rational(numerator, 1);
//	}
//}

//int main(){
//	Rational *a = new Rational(-18,18);
//	Rational *b = new Rational(4,5);
//	printf("%d %d\n", a->numerator_.number_, a->denominator_.number_);
//	 (a->div(b))->print();
//}
