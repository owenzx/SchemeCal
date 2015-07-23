#include "Boolean.h"
#include <cstdio>
#include <cstring>

using namespace std;

Boolean::Boolean(bool val) :val_(val){
	type_ = BOOLEAN;
}


Boolean::~Boolean(){}


Boolean *Boolean::isZero(){ return NULL; }
Boolean *Boolean::isNega(){ return NULL; }
Boolean *Boolean::isPosi(){ return NULL; }
Boolean *Boolean::isOdd(){ return NULL; }
Boolean *Boolean::isEven(){ return NULL; }
Boolean *Boolean::isInt(){ return NULL; }
Boolean *Boolean::isRat(){ return NULL; }
Boolean *Boolean::isReal(){ return NULL; }
Boolean *Boolean::isCpx(){ return NULL; }
Boolean *Boolean::isNum(){ return NULL; }


void Boolean::print(){
	if (val_) printf("#t");
	else printf("#f");
}

Boolean *Boolean::from_string(const char *expression){
	if (!strcmp(expression, "#t") || !strcmp(expression, "#T"))return new Boolean(true);
	if (!strcmp(expression, "#f") || !strcmp(expression, "#F"))return new Boolean(false);
	else return NULL;
}
