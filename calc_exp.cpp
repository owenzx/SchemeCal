#include "calc_exp.h"
#include "opt.h"
#include "compare.h"
#include "next_token.h"
#include <cstdio>

Number *calc_exp(){
	char *tk0 = next_token();
	Number *res;
	if (*tk0 == '(')
	{
		char *tk1 = next_token();
		Opt *opt;
		Cons *cons = new Cons(NULL, NULL), *tail = cons;
		Number *val;
		if (tk1 == NULL){ printf("123"); throw 0; }
		if (strcmp(tk1, "+") == 0)opt = new Add();
		else if (strcmp(tk1, "-") == 0)opt = new Sub();
		else if (strcmp(tk1, "*") == 0)opt = new Mul();
		else if (strcmp(tk1, "/") == 0)opt = new Div();
		else if (strcmp(tk1, "abs") == 0)opt = new Abs();
		else if (strcmp(tk1, "quotient") == 0)opt = new Quo();
		else if (strcmp(tk1, "remainder") == 0)opt = new Rem();
		else if (strcmp(tk1, "modulo") == 0)opt = new Mod();
		else if (strcmp(tk1, "gcd") == 0)opt = new Gcd();
		else if (strcmp(tk1, "lcm") == 0)opt = new Lcm();
		else if (strcmp(tk1, "expt") == 0)opt = new Exp();
		else if (strcmp(tk1, "sqrt") == 0)opt = new Sqrt();
		else if (strcmp(tk1, "floor") == 0)opt = new Flr();
		else if (strcmp(tk1, "ceiling") == 0)opt = new Cel();
		else if (strcmp(tk1, "truncate") == 0)opt = new Trunc();
		else if (strcmp(tk1, "round") == 0)opt = new Rnd();
		else if (strcmp(tk1, "numerator") == 0)opt = new Nume();
		else if (strcmp(tk1, "denominator") == 0)opt = new Deno();
		else if (strcmp(tk1, "inexact->exact") == 0)opt = new InexToEx();
		else if (strcmp(tk1, "exact->inexact") == 0)opt = new ExtoInex();
		else if (strcmp(tk1, "real-part") == 0)opt = new Rep();
		else if (strcmp(tk1, "imag-part") == 0)opt = new Imp();
		else throw 0;
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
		if (res == NULL){ throw 0; }
	}
	return res;
}
