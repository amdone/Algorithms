/*
 * stack.h
 *
 *  Created on: 2017年4月11日
 *      Author: lsn
 */

#ifndef SRC_STACKNEW_H_
#define SRC_STACKNEW_H_
#include <iostream>
#include <new>//new placement
#include <cstdlib>//malloc,free
#include <stdexcept>
#include <iterator>
#include <algorithm>
template<typename T>
class stackNew {
public:
	stackNew(int initCapacity = 10);
	~stackNew();
	bool empty(){return -1 == front;}
	int size(){return front + 1;}
	void push(T &theElement);
	void pop();
	T& top();
    void output(std::ostream& out)const;

private:
	T * element;
	int capacity;
	int front;//栈顶在数组中的下标。
};

#endif /* SRC_STACKNEW_H_ */
