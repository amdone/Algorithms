/*
 * arrayQueue.h
 *
 *  Created on: 2017年3月26日
 *      Author: lsn
 */

#ifndef ARRAYQUEUE_H_
#define ARRAYQUEUE_H_

#include "queue.h"
template<class T>
class arrayQueue : public queue<T>
{
   public:
      arrayQueue(int initialCapacity = 5);
      ~arrayQueue() {delete [] queue;}
      arrayQueue(arrayQueue& source );
      arrayQueue &operator=(arrayQueue&rhs);
      bool empty() const {return theFront == theBack;}
      int size() const;
      T& front() const;
      T& back() const;
      int getFront()const {return theFront;};
      int getBack()const {return theBack;};
      void pop();
      void push(const T& theElement);
      void output(std::ostream& out)const;

      void split(arrayQueue& first,arrayQueue& second);

  private:
      int theFront;       // 1 counterclockwise from theFront element
      int theBack;        // position of theBack element
      int arrayLength;    // queue capacity
      T *queue;           // element array
};
#endif /* ARRAYQUEUE_H_ */
