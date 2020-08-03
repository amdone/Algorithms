/*
 * RandomNumber.h
 *
 *  Created on: 2020Äê5ÔÂ21ÈÕ
 *      Author: Eichi
 */

#ifndef RANDOMNUMBER_H_
#define RANDOMNUMBER_H_

#pragma once
#include <iostream>
#include <time.h>
using namespace std;

const unsigned long maxshort = 65536L;
const unsigned long multiplier = 1194211693L;
const unsigned long adder = 12345L;

class RandomNumber
{
	private:
		unsigned long randSeed;
	public:
		RandomNumber (unsigned long s = 0);
		unsigned short Random (unsigned long n);
		double fRandom (void);
		int signedRandom(int n);
};

RandomNumber:: RandomNumber(unsigned long s)
{
	if(s == 0)
		randSeed = time(0);
	else
		randSeed = s;
}

unsigned short RandomNumber:: Random(unsigned long n)
{
	randSeed = multiplier * randSeed + adder;
	return (unsigned short) ((randSeed >> 16) % n);
}


double RandomNumber:: fRandom(void)
{
	return Random (maxshort) / double (maxshort);
}



#endif /* RANDOMNUMBER_H_ */
