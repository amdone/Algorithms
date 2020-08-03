/*
 * arrayStack.h
 *
 *  Created on: 2017年3月26日
 *      Author: lsn
 */

#ifndef ARRAYSTACK_H_
#define ARRAYSTACK_H_
#include "stack.h"
template<typename T>
class arrayStack : public stack<T>{
   public:
      arrayStack(int initialCapacity = 2);
      ~arrayStack() {delete [] stack;}
      bool empty() const {return stackTop == -1;};
      int size() const {return stackTop + 1;};
      T& top()const{
    	  if (-1 == stackTop)
    		  throw std::out_of_range("stackTop = -1");
    	  return stack[stackTop];
      };
      void pop(){
    	  if(-1 == stackTop)
    		  throw std::out_of_range("stackTop = -1");
    	  //stack[stackTop--].~T();//和arrayList同样的问题
    	  --stackTop;
      }
      void push(const T& theElement);
      void output(std::ostream& out)const;
  private:
      int stackTop;         // current top of stack
      int arrayLength;      // stack capacity
      T *stack;           // element array
      void changeLength1D(T* & a, int oldLength, int newLength);
};
#endif /* ARRAYSTACK_H_ */
