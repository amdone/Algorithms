/*
 * vertexIterator.h
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

#ifndef SRC_VERTEXITERATOR_H_
#define SRC_VERTEXITERATOR_H_
template<class T>
class vertexIterator
{
   public:
      virtual ~vertexIterator() {}
      virtual int next() = 0;
      virtual int next(T&) = 0;
};

#endif /* SRC_VERTEXITERATOR_H_ */
