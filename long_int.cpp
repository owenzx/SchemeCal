#include "long_int.h"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <numeric>
#include <cmath>
//string LongInt::reverse(const string &number_)const{
//	string temp = "";
//	//	temp += number_[0];
//	for (int i = 1; i < number_.length(); ++i){
//		temp = number_[i] + temp;
//	}
//	temp = number_[0] + temp;
//	return temp;
//}

string LongInt::reverse(const string &number_)const{
	string temp = number_;
	std::reverse(temp.begin(),temp.end());
	temp.erase(temp.length()-1, 1);
	temp = number_[0] + temp;
	return temp;
}


string LongInt::add(const string &aa, const string &bb)const{
	if (aa == "0") return bb;
	if (bb == "0") return aa;
	string ans = "";
	ans += aa[0];
	string a = reverse(aa);
	//	cout << a << endl;
	string b = reverse(bb);
	//	cout << b << endl;
	if (a.length() < b.length()) swap(a, b);
	int jw = 0;
	for (int i = 1; i < b.length(); ++i){
		ans += (a[i] + b[i] - '0' - '0' + jw) % 10 + '0';
		jw = (a[i] + b[i] - '0' - '0' + jw) / 10;
	}
	for (int i = b.length(); i < a.length(); ++i){
		//		if ((a[i] - '0' + jw) == 0) break;
		ans += (a[i] - '0' + jw) % 10 + '0';
		jw = (a[i] - '0' + jw) / 10;
	}
	if (jw != 0) ans += ('0' + jw);
	return reverse(ans);
}

string LongInt::minus(const string &aa, const string &bb)const{
	if (bb == "0") return aa;
	if (aa == bb) return "0";
	string ans = "";
	ans += aa[0];
	string a = reverse(aa);
	string b = reverse(bb);
	int tw = 0;
	for (int i = 1; i < b.length(); ++i){
		//		cout << char((a[i] - b[i] + tw + 10) % 10 + '0' )<< endl;
		ans += (a[i] - b[i] + tw + 10) % 10 + '0';
		if ((a[i] - b[i] + tw) >= 0) tw = 0;
		else tw = -1;
	}
	for (int i = b.length(); i < a.length(); ++i){
		//		cout << a[i]<<endl;
		//		cout << tw << endl;
		ans += (a[i] + tw + 10 - '0') % 10 + '0';
		if ((a[i] + tw - '0') >= 0) tw = 0;
		else tw = -1;
	}
	//	cout << ans << endl;
	for (int i = ans.length() - 1; i >= 0; --i){
		if (ans[i] != '0'){
			ans = ans.substr(0, i + 1);
			break;
		}
	}
	return reverse(ans);
}




LongInt::LongInt(int number){
	if (number == 0) number_ = "0";
	else if (number > 0) number_ = "+";
	else number_ = "-";
	number = ABS(number);
	while (number != 0){
		number_ +=  '0' + number % 10;
		number /= 10;
	}
	number_ = reverse(number_);
}

LongInt::LongInt(double number){
	if (number == 0) number_ = "0";
	else if (number > 0) number_ = "+";
	else number_ = "-";
	number = ABS(number);
	while (number >= 1){
		number_ += '0' + fmod(number, 10);
		number /= 10;
	}
	number_ = reverse(number_);
}


//LongInt::LongInt(const string &number) {
//	if (number[0]=='+' || number[0] == '-' || number=="0") number_ = number;
//	else number_ = "+" + number;
//}

LongInt::LongInt(const string &number) {
     bool allZero = true;
    for (int i=1; i<number.length();++i){
        if (number[i]!='0'){
            allZero = false;
            break;
        }
    }
    if (allZero && !(number[0]<='9' && number[0]>='1')) number_ = "0";
    else {
        string temp;;
        if (number[0]=='-') temp = "-";
        else temp = "+";
        for (int i=0; i<number.length();++i){
            if (number[i]>='1' && number[i]<='9'){
                for (int j=i; j<number.length(); ++j){
                    temp += number[j];
                }
                break;
            }
        }
        number_ = temp;
    }
}


LongInt::LongInt(const LongInt &long_int2) : number_(long_int2.number_){}

LongInt::~LongInt(){

}

LongInt::operator bool(){
	if (number_ == "0") return false;
	else return true;
}

LongInt::operator int(){
	if (number_ == "0")return 0;
	int result = 0;
	for (int i = 1; i < number_.length(); ++i){
		result *= 10;
		result += number_[i] - '0';
	}
	if (number_[0] == '-') result = -result;
	return result;
}

LongInt::operator double(){
	if (number_ == "0")return 0;
	double result = 0;
	for (int i = 1; i < number_.length(); ++i){
		result *= 10;
		result += number_[i] - '0';
	}
	if (number_[0] == '-') result = -result;
	return result;
}


bool LongInt::operator!=(const LongInt &long_int2) const{
	return number_ != long_int2.number_;
}


bool LongInt::operator<(const LongInt &long_int2) const{
	if (number_[0] == '+' && long_int2.number_[0] != '+') return false;
	if (number_[0] == '-' && long_int2.number_[0] != '-') return true;
	if (number_[0] == '0') return (long_int2.number_[0] == '+');
	if (long_int2.number_[0] == '0') return (number_[0] == '-');
	// after these judgements, two longints should be the SAME sign and NONZERO
	if (number_.length() != long_int2.number_.length()) return(!(number_.length() < long_int2.number_.length() ^ number_[0] == '+'));
	for (int i = 1; i < number_.length(); ++i){
		if (number_[i] < long_int2.number_[i]) return (number_[0] == '+');
		if (number_[i] > long_int2.number_[i]) return (!(number_[0] == '+'));
	}
	return false;
}


LongInt &LongInt::operator=(const LongInt &long_int2){
	if (this == &long_int2) return *this;
	number_ = long_int2.number_;
	return *this;
}

LongInt LongInt::operator+(const LongInt &long_int2) const{
	string a = number_, b = long_int2.number_;
	string absa = "+", absb = "+", result;
	if (a == "0" || b == "0") return add(a, b);
	if (a[0] == b[0]) return add(a, b);
	else{
		absa += a.substr(1, a.length() - 1); absb += b.substr(1, b.length() - 1);
		if (absa == absb) return(LongInt("0"));
		else if (LongInt(absa) < LongInt(absb)) {
			result = minus(absb, absa);
			result[0] = b[0];
			return result;
		}
		else{
			result = minus(absa, absb);
			result[0] = a[0];
			return result;
		}
	}
}

LongInt LongInt::operator-(const LongInt &long_int2) const{
	string a = number_, b = long_int2.number_;
	string absa = "+", absb = "+", result;
	absa += a.substr(1, a.length() - 1); absb += b.substr(1, b.length() - 1);
	if (b == "0") return minus(a, b);
	if (a == "0") {
		b[0] = '+' + '-' - b[0];
		return b;
	}
	if (a[0] != b[0]) {
		result = add(absa, absb);
		result[0] = a[0];
		return result;
	}
	else{
		if (absa == absb) return(LongInt("0"));
		else if (LongInt(absa) < LongInt(absb)) {
			result = minus(absb, absa);
			result[0] = '+' + '-' - a[0];
			return result;
		}
		else{
			result = minus(absa, absb);
			result[0] = a[0];
			return result;
		}
	}
}

LongInt LongInt::operator*(const LongInt &long_int2) const{
	if (number_ == "0" || long_int2.number_ == "0") return LongInt("0");
	string a = reverse(number_), b = reverse(long_int2.number_), ans = "";
	if (a[0] == b[0]) ans += '+';
	else ans += '-';
	int len = a.length() + b.length() + 1;
	bool start = false;
	int *temp = new int[len];
	memset(temp, 0, len*sizeof(int));
	for (int i = 1; i < a.length(); ++i){
		for (int j = 1; j < b.length(); ++j){
			temp[i + j - 1] += (a[i] - '0') * (b[j] - '0');
		}
	}
	for (int i = 1; i < len - 1; ++i){
		temp[i + 1] += temp[i] / 10;
		temp[i] %= 10;
	}
	for (int i = len - 1; i >= 1; --i){
		if (temp[i] != 0) start = true;
		if (start) ans += '0' + temp[i];
	}
	delete[] temp;
	return ans;
}

LongInt LongInt::operator/(const LongInt &long_int2) const{
	if (long_int2.number_ == "0") throw ('a');
	//assert(long_int2.number_ != "0" && "devide zero");
	string a = "+", b = "+", ans = "";
	a += number_.substr(1, number_.length() - 1); b += long_int2.number_.substr(1, long_int2.number_.length() - 1);
	if (number_[0] == long_int2.number_[0]) ans += '+';
	else ans += '-';
	string current = "+";
	string product[10];
	product[0] = "0";
	for (int num = 1; num <= 9; num++) product[num] = add(product[num - 1], b);
	int dqwei = 1;
	while (dqwei != a.length()) {
		if (current == "0")current = "+";
		current += (a[dqwei]);
		if (current == "+0")current = "0";
		//cout <<"BBB "<< current<<endl;
		if (b==current || LongInt(b) < LongInt(current)) {
			for (int num = 9; num >= 1; num--) {
				if (product[num] == current || LongInt(product[num]) < LongInt(current)) {
					ans += '0' + num;
					//cout <<"AAA "<< current<<endl;
					current = minus(current, product[num]);
					break;
				}
			}
		}
		else {
			if (ans.length() != 1) ans += ('0');
		}
		dqwei++;
	}
	//cout << "NOW ANSWER" << ans << endl;
	if (ans.length() == 1) ans = "0";
	return LongInt(ans);
}

LongInt LongInt::operator%(const LongInt &long_int2) const{
	if (long_int2.number_ == "0") throw ('a');
	//assert(long_int2.number_!="0" && "devide zero");
	return (*this - (*this / long_int2)*long_int2);
}

LongInt max(const LongInt &long_int1, const LongInt &long_int2){
	LongInt result(MAX(long_int1, long_int2));
	return result;
}

LongInt min(const LongInt &long_int1, const LongInt &long_int2){
	LongInt result(MIN(long_int1, long_int2));
	return result;
}

void LongInt::print(){
	if (number_[0] != '+') cout << number_;
	else cout << number_.substr(1, number_.length() - 1);
}
