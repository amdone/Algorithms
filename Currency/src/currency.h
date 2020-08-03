/*
 * Currency.h
 *
 *  Created on: 2017年2月12日
 *      Author: lsn
 */

#ifndef CURRENCY_H_
#define CURRENCY_H_
#include <exception>
#include <iostream>
using namespace std;

enum signType {Plus, Minus};
class currency {
public:
	currency(signType s = Plus,unsigned long d = 0, unsigned int c = 0);
	~currency() {};
	bool setValue(signType s, unsigned long d, unsigned int c);
	bool setValue(float a);
	signType	getSign() const{return sign;};
	unsigned long getDollars()const {return dollars;};
	unsigned int getCents() const {return cents;};
	currency add(const currency& x) ;
	currency& increment(const currency& x);
	void output()const;


	currency operator+(const currency& x);
	currency& operator+=(const currency& x);
	void setSign(signType newSign){sign = newSign;};
	//currency& operator=(const currency& x);
	bool operator!=(const currency& x);
	bool operator==(const currency& x);
	operator float() const;
	//currency(currency &x);

private:
	signType sign;
	unsigned long dollars;
	unsigned int cents;
};

currency operator-(const currency& x,const currency& y);
ostream& operator<<(ostream& out, const currency& x);


#endif /* CURRENCY_H_ */
