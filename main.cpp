#include "calc_exp.h"
#include <iostream>
#include <cstdio>
//using namespace std;

int main() {
	//cout << "START1" << endl;
	//LongInt *la = new LongInt("999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
	//LongInt*lb = new LongInt("1");
	//LongInt lc;
	//lc = *la + *lb;
	//lc.print();
	//cout << endl;
	//lc = *la - *lb;
	//lc.print();
	//cout << endl;
	//lc = *la * *lb;
	//lc.print();
	//cout << endl;
	//lc = *la / *lb;
	//lc.print();
	//cout << endl;
	//lc = *la % *lb;
	//lc.print();
	//cout << endl;

	//delete la; delete lb;



	//cout << "START2" << endl;
	//Rational *a = new Rational("999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", "1");
	//cout << "a is GENERATED" << endl;
	//Rational *b = new Rational("1", "1");
	//a->print();
	//(a->add(b))->print();



	//try {
	//	Number *res;
	//	res = calc_exp();
	//	res->print();
	//}
	//catch (...){ return 1; }
	//system("pause");
	//



	for (Base *res;;) {
		try{
			//printf("> ");
			res = calc_exp();
			if (res == NULL) throw (0);
			res->print();
			printf("\n");
		}
		catch (int) {
			cerr << "Wrong\n";
			//int c; while((c = getchar()) != '\n' && c != EOF);
			continue;
		}
		catch (char) {
			cerr << "Division by 0\n";
			//int c; while((c = getchar()) != '\n' && c != EOF);
			continue;
		}
	}

	return 0;
}
