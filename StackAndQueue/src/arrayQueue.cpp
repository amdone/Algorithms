/*
 * arrayQueue.cpp
 *
 *  Created on: 2017年3月26日
 *      Author: lsn
 */

#include "arrayQueue.h"

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{// Constructor.
   if (initialCapacity < 1)
	   throw std::out_of_range("Capacity < 1");
   arrayLength = initialCapacity;
   queue = new T[arrayLength];
   theFront = theBack = 0;
}

template<class T>
arrayQueue<T>::arrayQueue(arrayQueue& source ){
	   arrayLength = source.arrayLength;
	   theFront = source.theFront;
	   theBack = source.theBack;
	   queue = new T[arrayLength];
	   std::copy(source.queue,source.queue + source.arrayLength, queue);
}

template<class T>
arrayQueue<T>& arrayQueue<T>::operator=(arrayQueue<T>&rhs){
		delete [] queue;
	   arrayLength = rhs.arrayLength;
	   theFront = rhs.theFront;
	   theBack = rhs.theBack;
	   queue = new T[arrayLength];
	   std::copy(rhs.queue,rhs.queue + rhs.arrayLength, queue);
	   return *this;
}


template<class T>
T& arrayQueue<T>::front() const{
	// return front element
       if (theFront == theBack)
          throw std::out_of_range("empty");
       return queue[(theFront + 1) % arrayLength];
}

template<class T>
 T& arrayQueue<T>::back() const
 {// return theBack element
       if (theFront == theBack)
          throw std::out_of_range("empty");
       return queue[theBack];
}


template<class T>
int arrayQueue<T>::size() const{
	return (theBack - theFront + arrayLength) % arrayLength;
}

template<class T>
void arrayQueue<T>::pop(){
	// remove theFront element
	if (theFront == theBack)
             throw std::out_of_range("empty");
    theFront = (theFront + 1) % arrayLength;
    //queue[theFront].~T();  // destructor for T
}

template<class T>
void arrayQueue<T>::push(const T& theElement){
   if ((theBack + 1) % arrayLength == theFront)
	   throw std::out_of_range("full");

   // put theElement at the theBack of the queue
   theBack = (theBack + 1) % arrayLength;
   queue[theBack] = theElement;
}

template<class T>
void arrayQueue<T>::output(std::ostream& out) const{
	if(theFront == theBack) return;
	if(theFront < theBack ){
		std::copy(queue + theFront + 1,queue + theBack + 1, std::ostream_iterator<T>(out, "  "));
		out<<std::endl;
	}
	else{
		std::copy(queue + theFront + 1,queue + arrayLength, std::ostream_iterator<T>(out, "  "));
		std::copy(queue,queue + theBack + 1, std::ostream_iterator<T>(out, "  "));
		out<<std::endl;

	}
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const arrayQueue<T>& x){
	x.output(out);
	return out;
}

