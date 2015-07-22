#include "Boolean.h"
#include <cstdio>

Boolean::Boolean(bool val) :val_(val){
	type_ = BOOLEAN;
}


Boolean::~Boolean(){}


void Boolean::print(){
	if (val_) printf("#t");
	else printf("#f");
}