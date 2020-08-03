/*
 * queue.h
 *
 *  Created on: 2017年3月26日
 *      Author: lsn
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>
#include <iterator>
template<class T>
class queue
{
   public:
      virtual ~queue() {}
      virtual bool empty() const = 0;
                  // return true iff queue is empty
      virtual int size() const = 0;
                  // return number of elements in queue
      virtual T& front() const = 0;
                  // return reference to the front element
      virtual T& back() const = 0;
                  // return reference to the back element
      virtual void pop() = 0;
                  // remove the front element
      virtual void push(const T& theElement) = 0;
                  // add theElement at the back of the queue
};
#endif /* QUEUE_H_ */
