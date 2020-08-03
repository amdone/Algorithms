/*
 * edge.h
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_

template <class T>
class edge
{
   public:
      virtual ~edge() {};
      virtual int vertex1() const = 0;
      virtual int vertex2() const = 0;
      virtual T weight() const = 0;
};

template <>
class edge<bool>
{
   public:
      virtual ~edge() {};
      virtual int vertex1() const = 0;
      virtual int vertex2() const = 0;
};

#endif /* SRC_EDGE_H_ */
