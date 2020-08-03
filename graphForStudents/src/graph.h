/*
 * graph.h
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_
#include <iterator>
#include "vertexIterator.h"
#include "edge.h"


template<class T>
class graph{
   public:
      virtual ~graph() {}
      virtual int numberOfVertices() const = 0;
      virtual int numberOfEdges() const = 0;
      virtual bool existsEdge(int, int) const = 0;
      virtual void insertEdge(edge<T>*) = 0;
      virtual void eraseEdge(int, int) = 0;
      virtual int degree(int) const = 0;
      virtual int inDegree(int) const = 0;
      virtual int outDegree(int) const = 0;
      virtual bool directed() const = 0;
      virtual bool weighted() const = 0;
     // virtual vertexIterator<T>* iterator(int) = 0;
      virtual void output(std::ostream&) const = 0;
};
#endif /* SRC_GRAPH_H_ */
