#include "rational.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

bool Rational::isInt() const{
	LongInt one(1);
	return (numerator_.number_ == one.number_);
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
	if (!denominator_) throw ('a');
	//assert(denominator_ && "denominator is zero");
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
	Rational *result = new Rational();
	return result;
}

Number *Rational::rem(Number *number2){
	return NULL;
}


Number *Rational::mod(Number *number2){
	return NULL;
}

Number *Rational::gcd(Number *number2){
	return NULL;
}

Number *Rational::lcm(Number *number2){
	return NULL;
}

Number *Rational::exp(Number *number2){
	return NULL;
}

Number *Rational::sqt(){
	return NULL;
}


Number *Rational::flr(){
	return NULL;
}

Number *Rational::cel(){
	return NULL;
}

Number *Rational::trc(){
	return NULL;
}

Number *Rational::rnd(){
	return NULL;
}

Number *Rational::maxi(Number *number2){
	return NULL;
}

Number *Rational::mini(Number *number2){
	return NULL;
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
