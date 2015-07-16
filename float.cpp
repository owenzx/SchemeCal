#include "float.h"
#include "rational.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>

#define ABS(x) ((x)<0?(-(x)):(x))

Float::Float(double number) : number_(number){
	type_ = FLOAT;
}

Float::~Float(){

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
	Rational *rat = new Rational();
	ostringstream os;
	os.precision(18); 
	os << fixed << number_;
	Number *result = rat->convert(this);
	delete rat;
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
	Float *tmp = SCAST_FLOAT(number2);
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
	Float *tmp = SCAST_FLOAT(number2);
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
	if ((number_ - trunc(number_)) != 0.5){
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
