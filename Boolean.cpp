#include "Boolean.h"
#include <cstdio>
#include <cstring>

using namespace std;

Boolean::Boolean(bool val) :val_(val){
	type_ = BOOLEAN;
}


Boolean::~Boolean(){}


Boolean *Boolean::optnot(){
	Boolean *result = new Boolean(!val_);
	return result;
}


Boolean *Boolean::isInt(){
	Boolean *result = new Boolean(false);
	return result;
}
Boolean *Boolean::isRat(){
	Boolean *result = new Boolean(false);
	return result;
}

Boolean *Boolean::isReal(){
	Boolean *result = new Boolean(false);
	return result;
}

Boolean *Boolean::isCpx(){
	Boolean *result = new Boolean(false);
	return result;
}

Boolean *Boolean::isNum(){
	Boolean *result = new Boolean(false);
	return result;
}


void Boolean::print(){
	if (val_) printf("#t");
	else printf("#f");
}

Boolean *Boolean::from_string(const char *expression){
	if (!strcmp(expression, "#t") || !strcmp(expression, "#T"))return new Boolean(true);
	if (!strcmp(expression, "#f") || !strcmp(expression, "#F"))return new Boolean(false);
	else return NULL;
}
