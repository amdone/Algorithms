/*
 * currency2.cpp
 *
 *  Created on: 2017年3月14日
 *      Author: lsn
 */


#include "currency2.h"
currency2::currency2(signType s,unsigned long d, unsigned int c) {
	if(c > 99){
		throw invalid_argument("cents > 99");
		//std::cerr<<"Cents should be < 100" << std::endl;
		//exit(EXIT_FAILURE);
	}
	amount = d*100 + c;
	if(s == minus) amount = -amount;

}

bool currency2::setValue(signType s, unsigned long d, unsigned int c){
	if (c > 99) return false;
	amount = d*100 + c;
	if(s == minus) amount = -amount;
	return true;
}
bool currency2::setValue(float a){
	if(a < 0)
		amount = (a - 0.005)*100;
	else
		amount = (a + 0.005)*100;
	return true;
}


currency2 currency2::add(const currency2& x){
	currency2 ans;
	ans.amount = amount + x.amount;
	return ans;
}

currency2& currency2::increment(const currency2& x){
	amount += x.amount;
	return *this;
}


currency2 currency2::operator+(const currency2& x){
	currency2 tmp;
	tmp.amount = amount + x.amount;
	return tmp;
}
currency2& currency2::operator+=(const currency2& x){
	amount += x.amount;
	return *this;
}
currency2& currency2::operator=(const currency2& x){
	amount = x.amount;
	return *this;
}


bool currency2::operator!=(const currency2& x){
	if(amount != x.amount)
		return true;
	else
		return false;
}

bool currency2::operator==(const currency2& x){
	if(amount == x.amount)
		return true;
	else
		return false;
}

void currency2::output() const
{// Output currency2 value.
	long tmp = amount;
   if (tmp < 0) {
	   cout << '-';
	  tmp  = - tmp;;
   }
   cout << '$' << tmp/100 << '.';
   if (tmp%100 < 10) cout << "0";
   cout << tmp % 100 <<endl;;
}

currency2::operator float() const{
	float tmp;
	long tmpAmount = amount;
	if(tmpAmount < 0) tmpAmount = - tmpAmount;
	tmp = tmpAmount % 100;
	tmp /= 100.0;
	tmp += tmpAmount / 100;
	if(amount < 0) tmp = -tmp;
	return tmp;
}

currency2& currency2::operator=(int x){
	amount = x;
	return *this;
}
currency2& currency2::operator=(double x){
	if(x < 0)
		amount = (x - 0.005)*100;
	else
		amount = (x + 0.005)*100;
	return *this;
}

/*
currency2::currency2(currency2 &x) {
	sign = x.sign;
	dollars=x.dollars;
	cents=x.cents;
	//cout<<"copy"<<endl;
}
*/

currency2 operator-(const currency2& x,const currency2& y){
	currency2 tmp;
	tmp.amount = x.amount - y.amount;
	return tmp;
}
ostream& operator<<(ostream& out, const currency2& x){
	x.output();
	return out;
}


