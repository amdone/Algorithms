/*
 * stack.h
 *
 *  Created on: 2017年3月26日
 *      Author: lsn
 */

#ifndef STACK_H_
#define STACK_H_

#include <iostream>
#include <iterator>
#include <stdexcept>


template<typename T>
class stack
{
   public:
      virtual ~stack() {}
      virtual bool empty() const = 0;
                  // return true iff stack is empty
      virtual int size() const = 0;
                  // return number of elements in stack
      virtual T& top() const = 0;
                  // return reference to the top element
      virtual void pop() = 0;
                  // remove the top element
      virtual void push(const T& theElement) = 0;
                  // insert theElement at the top of the stack
};
#endif /* STACK_H_ */
