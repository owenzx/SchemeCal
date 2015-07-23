#include "opt.h"
#include "float.h"
#include "rational.h"
#include "Complex.h"
#include "number.h"
#include "Boolean.h"
#include "Base.h"
#include "Char.h"
#include "String.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <complex>
#include <cstdlib>
#define SCAST_RATIONAL(x) static_cast<Rational*>(x)
#define SCAST_FLOAT(x) static_cast<Float*>(x)
#define SCAST_NUMBER(x) static_cast<Number*>(x)

class Add : public Opt {
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational(0, 1);
		Number *last;
		for (; con; con = con->cdr)
		{
			if (con->car->type_ > 3 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = SCAST_NUMBER(con->car), *conv;
			last = res;
			if (res->type_ > opr->type_)
			{
				res = res->add(conv = res->convert(opr));
			}
			else
			{
				res = (conv = opr->convert(res))->add(opr);
			}

			delete last;
			delete conv;

		}
		return res;
	}
};

class Sub :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res = new Rational(0, 1), *last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		last = res;
		if (cnt == 1)
		{
			if (res->type_ > opr->type_)
				res = res->sub(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->sub(opr);
			delete last;
			delete conv;
			return res;
		}
		if (res->type_ > opr->type_)
			res = res->add(conv = res->convert(opr));
		else
			res = (conv = opr->convert(res))->add(opr);
		con = con->cdr;
		delete last;
		delete conv;
		for (; con; con = con->cdr)
		{
			opr = SCAST_NUMBER(con->car);
			last = res;
			if (res->type_ > opr->type_)
				res = res->sub(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->sub(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};

class Mul : public Opt {
	/* Use the lowest level type */
	Number *calc(Cons *con) {
		Number *res = new Rational(1, 1), *last;
		for (; con; con = con->cdr)
		{
			if (con->car->type_ > 3 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = SCAST_NUMBER(con->car), *conv;
			last = res;
			if (res->type_ > opr->type_)
				res = res->mul(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->mul(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};

class Div :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res = new Rational(1, 1), *last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		last = res;
		Number *zero = new Float(0.0);
		if (cnt == 1)
		{
			if (res->type_ > opr->type_)
				res = res->div(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->div(opr);
			delete last;
			delete conv;
			return res;
		}
		if (res->type_ > opr->type_)
			res = res->mul(conv = res->convert(opr));
		else
			res = (conv = opr->convert(res))->mul(opr);
		con = con->cdr;
		delete last;
		delete conv;
		for (; con; con = con->cdr)
		{
			opr = SCAST_NUMBER(con->car);
			last = res;
			if (res->type_ > opr->type_)
				res = res->div(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->div(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};

class Les :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		
		if (cnt < 2)
		{
			throw 0;
			return NULL;
		}
		Boolean f(false),*res;
		Number *last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		Number *first, *second;
		//if (cnt == 2)
		for (; con->cdr; con = con->cdr)
		{
			first = SCAST_NUMBER(con->car);  second = SCAST_NUMBER(con->cdr->car);
			if (first->type_ > second->type_)
			{
				res = first->les(first->convert(second));
			}
			else
			{
				res = second->convert(first)->les(second);
			}
			delete first; 
			if (res->val_ == f.val_)break;
		}
		delete second;
		return res;
	}
};

class LesE :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}

		if (cnt < 2)
		{
			throw 0;
			return NULL;
		}
		Boolean f(false), *res;
		Number *last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		Number *first, *second;
		//if (cnt == 2)
		for (; con->cdr; con = con->cdr)
		{
			first = SCAST_NUMBER(con->car);  second = SCAST_NUMBER(con->cdr->car);
			if (first->type_ > second->type_)
			{
				res = first->lesE(first->convert(second));
			}
			else
			{
				res = second->convert(first)->lesE(second);
			}
			delete first;
			if (res->val_ == f.val_)break;
		}
		delete second;
		return res;
	}
};

class Grt :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}

		if (cnt < 2)
		{
			throw 0;
			return NULL;
		}
		Boolean f(false), *res;
		Number *last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		Number *first, *second;
		//if (cnt == 2)
		for (; con->cdr; con = con->cdr)
		{
			first = SCAST_NUMBER(con->car);  second = SCAST_NUMBER(con->cdr->car);
			if (first->type_ > second->type_)
			{
				res = first->grt(first->convert(second));
			}
			else
			{
				res = second->convert(first)->grt(second);
			}
			delete first;
			if (res->val_ == f.val_)break;
		}
		delete second;
		return res;
	}
};

class GrtE :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}

		if (cnt < 2)
		{
			throw 0;
			return NULL;
		}
		Boolean f(false), *res;
		Number *last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		Number *first, *second;
		//if (cnt == 2)
		for (; con->cdr; con = con->cdr)
		{
			first = SCAST_NUMBER(con->car);  second = SCAST_NUMBER(con->cdr->car);
			if (first->type_ > second->type_)
			{
				res = first->grtE(first->convert(second));
			}
			else
			{
				res = second->convert(first)->grtE(second);
			}
			delete first;
			if (res->val_ == f.val_)break;
		}
		delete second;
		return res;
	}
};


class Abs :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->abs();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Quo :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *first = SCAST_NUMBER(con->car), *second = SCAST_NUMBER(con->cdr->car);
		if (cnt == 2)
		{
			if (first->type_ > second->type_)
			{
				res = first->quo(first->convert(second));
			}
			else
			{
				res = second->convert(first)->quo(second);
			}
			delete first; delete second;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Rem :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *first = SCAST_NUMBER(con->car), *second = SCAST_NUMBER(con->cdr->car);
		if (cnt == 2)
		{
			if (first->type_ > second->type_)
			{
				res = first->rem(first->convert(second));
			}
			else
			{
				res = second->convert(first)->rem(second);
			}
			delete first; delete second;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Mod :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *first = SCAST_NUMBER(con->car), *second = SCAST_NUMBER(con->cdr->car);
		if (cnt == 2)
		{
			if (first->type_ > second->type_)
			{
				res = first->mod(first->convert(second));
			}
			else
			{
				res = second->convert(first)->mod(second);
			}
			delete first; delete second;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Gcd :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Rational(0, 1), *last;
		for (; con; con = con->cdr)
		{
			if (con->car->type_ > 3 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = SCAST_NUMBER(con->car), *conv;
			last = res;
			if (res->type_ > opr->type_)
				res = res->gcd(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->gcd(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};

class Lcm :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Rational(1, 1), *last;
		for (; con; con = con->cdr)
		{
			if (con->car->type_ > 3 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = SCAST_NUMBER(con->car), *conv;
			last = res;
			if (res->type_ > opr->type_)
				res = res->lcm(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->lcm(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};

class Exp :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *first = SCAST_NUMBER(con->car), *second = SCAST_NUMBER(con->cdr->car);
		if (cnt == 2)
		{
			if (first->type_ > second->type_)
			{
				res = first->exp(first->convert(second));
			}
			else
			{
				res = second->convert(first)->exp(second);
			}
			delete first; delete second;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
	/*Number *calc(Cons *con)
	{
	Cons *tmp = con;
	int cnt = 0;
	for (; tmp; tmp = tmp->cdr)
	{
	if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
	{
	throw 0;
	}
	cnt++;
	}
	Number *res;
	Number *first = SCAST_NUMBER(con->car), *second = SCAST_NUMBER(con->cdr->car);
	if (cnt == 2)
	{
	Complex *cpx = new Complex();
	Number *firstc = cpx->convert(first);
	Number *secondc = cpx->convert(second);

	res = firstc->exp(secondc);

	delete first; delete second; delete firstc; delete secondc;
	return res;
	}
	else{
	throw 0;
	return NULL;
	}
	}*/
};

class Ex :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->ex();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Sqt :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->sqt();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
	/*Number *calc(Cons *con)
	{
	Cons *tmp = con;
	int cnt = 0;
	for (; tmp; tmp = tmp->cdr)
	{
	if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
	{
	throw 0;
	}
	cnt++;
	}
	Number *res, *tmp3;
	Number *opr = SCAST_NUMBER(con->car);
	if (cnt == 1)
	{
	Complex *cpx = new Complex();
	tmp3 = cpx->convert(opr);
	Complex *tmp2 = SCAST_COMPLEX(tmp3);
	res = tmp2->sqt();
	delete cpx;
	delete opr;
	delete tmp2;
	return res;
	}
	else{
	throw 0;
	return NULL;
	}
	}*/
};

class Flr :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->flr();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Cel :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->cel();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Trc :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->trc();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}

};

class Rnd :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->rnd();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}

};

class Nume :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->getNumerator();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Deno :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->getDenominator();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

//class Nume :public Opt{
//	Number *calc(Cons *con)
//	{
//		Cons *tmp = con;
//		int cnt = 0;
//		for (; tmp; tmp = tmp->cdr)
//		{
//			if (tmp->car->type_ != 1)
//			{
//				throw 0;
//			}
//			cnt++;
//		}
//		Number *res;
//		Number *opr = SCAST_NUMBER(con->car);
//		if (cnt == 1)
//		{
//			Rational *opt_r = SCAST_RATIONAL(opr);
//			res = opt_r->getNumerator();
//			delete opr;
//			return res;
//		}
//		else{
//			throw 0;
//			return NULL;
//		}
//	}
//};
//
//class Deno :public Opt{
//	Number *calc(Cons *con)
//	{
//		Cons *tmp = con;
//		int cnt = 0;
//		for (; tmp; tmp = tmp->cdr)
//		{
//			if (tmp->car->type_ != 1)
//			{
//				throw 0;
//			}
//			cnt++;
//		}
//		Number *res;
//		Number *opr = SCAST_NUMBER(con->car);
//		if (cnt == 1)
//		{
//			Rational *opt_r = SCAST_RATIONAL(opr);
//			res = opt_r->getDenominator();
//			delete opr;
//			return res;
//		}
//		else{
//			throw 0;
//			return NULL;
//		}
//	}
//};


class InexToEx :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->inextoex();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class ExtoInex :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->extoinex();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Rep :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res, *tmp3;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			Complex *cpx = new Complex();
			tmp3 = cpx->convert(opr);
			Complex *tmp2 = SCAST_COMPLEX(tmp3);
			res = tmp2->getreal();
			delete cpx;
			delete opr;
			delete tmp2;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Imp :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res, *tmp3;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			Complex *cpx = new Complex();
			tmp3 = cpx->convert(opr);
			Complex *tmp2 = SCAST_COMPLEX(tmp3);
			res = tmp2->getimag();
			delete cpx;
			delete opr;
			delete tmp2;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class Max :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res, *last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		if (cnt == 0)
		{
			throw(0);
		}
		res = opr;
		con = con->cdr;
		for (; con; con = con->cdr)
		{
			opr = SCAST_NUMBER(con->car);
			last = res;
			if (res->type_ > opr->type_)
				res = res->maxi(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->maxi(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};


class Min :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res, *last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		if (cnt == 0)
		{
			throw(0);
		}
		res = opr;
		con = con->cdr;
		for (; con; con = con->cdr)
		{
			opr = SCAST_NUMBER(con->car);
			last = res;
			if (res->type_ > opr->type_)
				res = res->mini(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->mini(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};



class Sin :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->sin();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class Cos :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->cos();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class Tan :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->tan();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class Asin :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->asin();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class Acos :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->acos();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};



class Atan :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->atan();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class Log :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->log();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class ToRect :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *first = SCAST_NUMBER(con->car), *second = SCAST_NUMBER(con->cdr->car);
		if (cnt == 2)
		{
			Complex *cpx = new Complex();
			res = cpx->torect(first, second);
			delete first; delete second; delete cpx;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class ToPolar :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res;
		Number *first = SCAST_NUMBER(con->car), *second = SCAST_NUMBER(con->cdr->car);
		if (cnt == 2)
		{
			Complex *cpx = new Complex();
			res = cpx->topolar(first, second);
			delete first; delete second; delete cpx;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class Magn :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res, *tmp3;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			Complex *cpx = new Complex();
			tmp3 = cpx->convert(opr);
			Complex *tmp2 = SCAST_COMPLEX(tmp3);
			res = tmp2->getmag();
			delete cpx;
			delete opr;
			delete tmp2;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class Ang :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 3 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res, *tmp3;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			Complex *cpx = new Complex();
			tmp3 = cpx->convert(opr);
			Complex *tmp2 = SCAST_COMPLEX(tmp3);
			res = tmp2->getang();
			delete cpx;
			delete opr;
			delete tmp2;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class IsZero :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->isZero();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};




class IsNega :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->isNega();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};



class IsPosi :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->isPosi();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};



class IsOdd :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->isOdd();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};



class IsEven :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->isEven();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};



class IsInt :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->isInt();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};



class IsRat :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->isRat();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class IsReal :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->isReal();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class IsCpx :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->isCpx();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class IsNum :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res;
		Number *opr = SCAST_NUMBER(con->car);
		if (cnt == 1)
		{
			res = opr->isNum();
			delete opr;
			return res;
		}
		else{
			throw 0;
			return NULL;
		}
	}
};

class optNot :public Opt{
	Boolean *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_ > 4 || tmp->car->type_ < 1)
			{
				throw 0;
			}
			cnt++;
		}
		Boolean *res = new Boolean(false);
		Base *opr = con->car;
		if (cnt == 1)
		{
			if (opr->type_ != 4){
				delete opr;
				return res;
			}
			else{
				Boolean *tmp = SCAST_BOOLEAN(opr);
				res = tmp->optnot();
				delete opr;
				return res;
			}
		}
		else{
			throw 0;
			return NULL;
		}
	}
};