#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <ctime>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <bitset>
#include <cctype>
#include <cassert>
#include <complex>
#include "number.h"

struct Cons {
	//Number *car;
	Base *car;
	Cons *cdr;
	Cons(Base *_car, Cons *_cdr) : car(_car), cdr(_cdr) {}
	bool check_length(int len) {
		int l = 0;
		for (Cons *p = this; p; p = p->cdr) l++;
		return l == len;
	}
};

class Opt {
public:
	//virtual Number *calc(Cons *con) = 0;
	virtual Base *calc(Cons *con) = 0;
};

class OptB {
public:
	virtual Boolean *calc(Cons *con) = 0;
};