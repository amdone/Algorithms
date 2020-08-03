/*
 * Currency.cpp
 *
 *  Created on: 2017年2月12日
 *      Author: lsn
 */

#include "currency.h"
currency::currency(signType s,unsigned long d, unsigned int c) {
	if(c > 99){
		throw invalid_argument("cents > 99");
		//std::cerr<<"Cents should be < 100" << std::endl;
		//exit(EXIT_FAILURE);
	}
	sign = s;
	dollars=d;
	cents=c;
}
bool currency::setValue(signType s, unsigned long d, unsigned int c){
	if (c > 99) return false;
	sign = s; dollars = d; cents = c;
	return true;

}
bool currency::setValue(float a){
	if (a < 0) {sign = Minus; a = -a;}
	else sign = Plus;
	dollars = a; // extract integer part
	// get two decimal digits
	cents = (a + 0.001 - dollars) * 100;
	return true;
}


currency currency::add(const currency& x){
	long a1, a2, a3;
	currency ans;
	a1 = dollars * 100 + cents;
	if(sign == Minus) a1 = -a1;
	a2 = x.dollars*100 + x.cents;
	if(x.sign == Minus) a2 = -a2;
	a3 = a1 + a2;
	if(a3 < 0 ){
			ans.sign = Minus;
			a3 = -a3;
		}
	else
		ans.sign = Plus;
	ans.dollars = a3 / 100;
	ans.cents = a3 - ans.dollars * 100;
	return ans;
}

currency& currency::increment(const currency& x){
	*this = add(x);
	return *this;//和前面的比较
}


currency currency::operator+(const currency& x){
	currency tmp;
	tmp = *this;
	tmp+=x;//+利用+=实现
	return tmp;
}
currency& currency::operator+=(const currency& x){
	*this = add(x);
	return *this;
}
/*
currency& currency::operator=(const currency& x){
	//cout <<"=";观察是不是调用了这个函数     -->调用了该函数
	this->sign = x.sign;
	this->dollars = x.dollars;
	this->cents = x.cents;
	return *this;
}
*/

bool currency::operator!=(const currency& x){
	if(this->sign != x.sign) return true;
	if(this->dollars != x.dollars) return true;
	if(this->cents != x.cents) return true;
	return false;
}

bool currency::operator==(const currency& x){
	if(*this != x) return false;
	return true;
}

void currency::output() const
{// Output currency value.
   if (sign == Minus) cout << '-';
   cout << '$' << dollars << '.';
   if (cents < 10) cout << "0";
   cout << cents<<endl;;
}

currency::operator float() const{
	float dollars= (*this).getDollars();
	float cents = (*this).getCents();
	float tmp = dollars + cents/100.0f;
	if((*this).getSign() == Minus) tmp = -tmp;
	return tmp;
}

/*
currency::currency(currency &x) {
	sign = x.sign;
	dollars=x.dollars;
	cents=x.cents;
	//cout<<"copy"<<endl;
}
*/

currency operator-(const currency& x,const currency& y){
	currency tmp;
	tmp = y;
	if(tmp.getSign() == Minus)
		tmp.setSign(Plus);
	else
		tmp.setSign(Minus);
	tmp+=x;
	return tmp;
}
ostream& operator<<(ostream& out, const currency& x){
	   if (x.getSign() == Minus) cout << '-';
	   cout << '$' << x.getDollars() << '.';
	   if (x.getCents() < 10) cout << "0";
	   out << x.getCents();
	   return out;
}

