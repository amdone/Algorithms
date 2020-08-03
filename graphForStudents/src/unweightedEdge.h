/*
 * unweightedEdge.h
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

#ifndef SRC_UNWEIGHTEDEDGE_H_
#define SRC_UNWEIGHTEDEDGE_H_
#include <stdexcept>
#include "edge.h"
class unweightedEdge : public edge<bool>
{
   public:
      unweightedEdge(int theV1, int theV2)
         {v1 = theV1; v2 = theV2;}
      ~unweightedEdge() {};
      int vertex1() const {return v1;}
      int vertex2() const {return v2;}
 //     bool weight() const {throw std::invalid_argument("weight");}
   private:
      int v1,
          v2;
};

#endif /* SRC_UNWEIGHTEDEDGE_H_ */
