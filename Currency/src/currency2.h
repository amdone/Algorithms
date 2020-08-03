/*
 * currency2.h
 *
 *  Created on: 2017年3月14日
 *      Author: lsn
 */

#ifndef currency2_H_
#define currency2_H_

#include <exception>
#include <iostream>

using namespace std;

class currency2 {
public:
	enum signType {plus, minus};//因为std空间中也有plus和minus，所以会冲突，在currency1是改名了，在这里变了地方

	friend currency2 operator-(const currency2& x,const currency2& y);
	currency2(signType s = plus,unsigned long d = 0, unsigned int c = 0);
	~currency2() {};
	bool setValue(signType s, unsigned long d, unsigned int c);
	bool setValue(float a);
	signType	getSign() const{ if(amount >= 0)  return plus; else return minus;};
	unsigned long getDollars()const {return amount >=0 ? amount/100 : -amount / 100;};
	unsigned int getCents() const {return amount >=0 ? amount % 100 : -amount % 100;};//%对正数是通常意义上的取余数运算，负数就不对
	currency2 add(const currency2& x) ;
	currency2& increment(const currency2& x);
	void output()const;

	currency2 operator+(const currency2& x);
	currency2& operator+=(const currency2& x);
	void setSign(signType newSign){if(newSign == plus) amount<0 ? amount=-amount :amount;else amount < 0 ? amount : amount=-amount;};
	currency2& operator=(const currency2& x);
	bool operator!=(const currency2& x);
	bool operator==(const currency2& x);
	operator float() const;
	//currency2(currency2 &x);
	currency2& operator=(int x);
	currency2& operator=(double x);


private:
	long amount;
};

currency2 operator-(const currency2& x,const currency2& y);
ostream& operator<<(ostream& out, const currency2& x);


#endif /* currency2_H_ */
