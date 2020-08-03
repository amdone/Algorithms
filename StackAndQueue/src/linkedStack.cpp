/*
 * linkedStack.cpp
 *
 *  Created on: 2017年3月26日
 *      Author: lsn
 */

#include "linkedStack.h"


template<class T>
linkedStack<T>::~linkedStack()
{// Destructor.
   while (stackTop != NULL)
   {// delete top node
      chainNode<T>* nextNode = stackTop->next;
      delete stackTop;
      stackTop = nextNode;
   }
}


template<class T>
void linkedStack<T>::push(const T& theElement)
{
	stackTop = new chainNode<T>(theElement, stackTop);
    ++stackSize;
}


template<class T>
void linkedStack<T>::pop()
{// Delete top element.
   if (stackSize == 0)
      throw std::out_of_range("stackSize is 0");

   chainNode<T>* nextNode = stackTop->next;
   delete stackTop;
   stackTop = nextNode;
   --stackSize;
}

template<class T>
void linkedStack<T>::output(std::ostream& out) const{
	std::copy(this->begin(), this->end(), std::ostream_iterator<T>(out, "  "));
	out<<std::endl;
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const linkedStack<T>& x){
	x.output(out);
	return out;
}

