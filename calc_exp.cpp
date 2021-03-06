#include "calc_exp.h"
#include "opt.h"
#include "compare.h"
#include "next_token.h"
#include <cstdio>

Base *calc_exp(){
//Number *calc_exp(){
	char *tk0 = next_token();
	//Number *res;
	Base *res;
	if (*tk0 == '(')
	{
		char *tk1 = next_token();
		Opt *opt; /*OptB *optb;*/
		Cons *cons = new Cons(NULL, NULL), *tail = cons;
		//Number *val;
		Base *val;
		if (tk1 == NULL){ printf("123"); throw 0; }
		if (strcmp(tk1, "+") == 0)opt = new Add();
		else if (strcmp(tk1, "-") == 0)opt = new Sub();
		else if (strcmp(tk1, "*") == 0)opt = new Mul();
		else if (strcmp(tk1, "/") == 0)opt = new Div();
		else if (strcmp(tk1, "<") == 0)opt = new Les();
		else if (strcmp(tk1, "<=") == 0)opt = new LesE();
		else if (strcmp(tk1, ">") == 0)opt = new Grt();
		else if (strcmp(tk1, ">=") == 0)opt = new GrtE();
		else if (strcmp(tk1, "abs") == 0)opt = new Abs();
		else if (strcmp(tk1, "quotient") == 0)opt = new Quo();
		else if (strcmp(tk1, "remainder") == 0)opt = new Rem();
		else if (strcmp(tk1, "modulo") == 0)opt = new Mod();
		else if (strcmp(tk1, "gcd") == 0)opt = new Gcd();
		else if (strcmp(tk1, "lcm") == 0)opt = new Lcm();
		else if (strcmp(tk1, "expt") == 0)opt = new Exp();
		else if (strcmp(tk1, "exp") == 0)opt = new Ex();
		else if (strcmp(tk1, "sqrt") == 0)opt = new Sqt();
		else if (strcmp(tk1, "floor") == 0)opt = new Flr();
		else if (strcmp(tk1, "ceiling") == 0)opt = new Cel();
		else if (strcmp(tk1, "truncate") == 0)opt = new Trc();
		else if (strcmp(tk1, "round") == 0)opt = new Rnd();
		else if (strcmp(tk1, "numerator") == 0)opt = new Nume();
		else if (strcmp(tk1, "denominator") == 0)opt = new Deno();
		else if (strcmp(tk1, "inexact->exact") == 0)opt = new InexToEx();
		else if (strcmp(tk1, "exact->inexact") == 0)opt = new ExtoInex();
		else if (strcmp(tk1, "real-part") == 0)opt = new Rep();
		else if (strcmp(tk1, "imag-part") == 0)opt = new Imp();
		else if (strcmp(tk1, "max") == 0)opt = new Max();
		else if (strcmp(tk1, "min") == 0)opt = new Min();
		else if (strcmp(tk1, "sin") == 0)opt = new Sin();
		else if (strcmp(tk1, "cos") == 0)opt = new Cos();
		else if (strcmp(tk1, "tan") == 0)opt = new Tan();
		else if (strcmp(tk1, "asin") == 0)opt = new Asin();
		else if (strcmp(tk1, "acos") == 0)opt = new Acos();
		else if (strcmp(tk1, "atan") == 0)opt = new Atan();
		else if (strcmp(tk1, "log") == 0)opt = new Log();
		else if (strcmp(tk1, "make-rectangular") == 0)opt = new ToRect();
		else if (strcmp(tk1, "make-polar") == 0)opt = new ToPolar();
		else if (strcmp(tk1, "magniude") == 0)opt = new Magn();
		else if (strcmp(tk1, "angle") == 0)opt = new Ang();
		else if (strcmp(tk1, "zero?") == 0)opt = new IsZero();
		else if (strcmp(tk1, "negative?") == 0)opt = new IsNega();
		else if (strcmp(tk1, "positive?") == 0)opt = new IsPosi();
		else if (strcmp(tk1, "odd?") == 0)opt = new IsOdd();
		else if (strcmp(tk1, "even?") == 0)opt = new IsEven();
		else if (strcmp(tk1, "integer?") == 0)opt = new IsInt();
		else if (strcmp(tk1, "rational?") == 0)opt = new IsRat();
		else if (strcmp(tk1, "real?") == 0)opt = new IsReal();
		else if (strcmp(tk1, "complex?") == 0)opt = new IsCpx();
		else if (strcmp(tk1, "number?") == 0)opt = new IsNum();
		else if (strcmp(tk1, "not") == 0)opt = new optNot();
		else throw 0;
		//if (!opt && optb){
		//	delete opt;
		//	OptB *opt = optb;
		//}
		while ((val = calc_exp()))
		{
			tail->cdr = new Cons(val, NULL);
			tail = tail->cdr;
		}
		res = opt->calc(cons->cdr);
		for (Cons *np; cons; cons = np)
		{
			np = cons->cdr;
			delete cons;
		}
	}
	else if (*tk0 == ')')
	{
		return NULL;
	}
	else
	{
		res = Rational::from_string(tk0);
		if (!res) { res = Float::from_string(tk0); }
		if (!res) { res = Complex::from_string(tk0); }
		if (!res) { res = Boolean::from_string(tk0); }
		if (res == NULL){ throw 0; }
	}
	return res;
}
