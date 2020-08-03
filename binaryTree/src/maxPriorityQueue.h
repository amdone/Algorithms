/*
 * maxPriorityQueue.h
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

#ifndef SRC_MAXPRIORITYQUEUE_H_
#define SRC_MAXPRIORITYQUEUE_H_
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
template<class T>
class maxPriorityQueue
{
   public:
      virtual ~maxPriorityQueue() {}
      virtual bool empty() const = 0;
                  // return true iff queue is empty
      virtual int size() const = 0;
                  // return number of elements in queue
      virtual const T& top() = 0;
                  // return reference to the max element
      virtual void pop() = 0;
                  // remove the top element
      virtual void push(const T& theElement) = 0;
                  // add theElement to the queue
};
#endif /* SRC_MAXPRIORITYQUEUE_H_ */
