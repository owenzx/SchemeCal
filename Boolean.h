#pragma once
#include "Base.h"
class Boolean :public Base
{
public:
	Boolean(bool val = false);
	~Boolean();
	void print();
	bool val_;
};

