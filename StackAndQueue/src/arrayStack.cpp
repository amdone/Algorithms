/*
 * arrayStack.cpp
 *
 *  Created on: 2017年3月26日
 *      Author: lsn
 */

#include "arrayStack.h"
template<typename T>
arrayStack<T>:: arrayStack(int initialCapacity){
	if(initialCapacity < 1)
		throw std::invalid_argument("initialCapacity < 1");
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;
}


template<class T>
void arrayStack<T>::changeLength1D(T * &a, int oldLength, int newLength){
	if(newLength < 0)
		throw std::invalid_argument("new length must be >= 0");
	T * temp = new T[newLength];
	int number = std::min(oldLength,newLength);
	std::copy(a, a + number, temp);
	delete [] a;
	a= temp;
}


template<typename T>
void arrayStack<T>:: push(const T& theElement){
	if(stackTop == arrayLength - 1){
		changeLength1D(stack,arrayLength, 2*arrayLength);
		arrayLength *= 2;
	}
	stack[++stackTop] = theElement;
}

template<class T>
void arrayStack<T>::output(std::ostream& out) const{
	std::copy(stack,stack + stackTop + 1, std::ostream_iterator<T>(out, "  "));
	out<<std::endl;
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const arrayStack<T>& x){
	x.output(out);
	return out;
}


