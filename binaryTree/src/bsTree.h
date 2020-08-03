/*
 * bsTree.h
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

#ifndef SRC_BSTREE_H_
#define SRC_BSTREE_H_
#include "dictionary.h"
template<class K, class E>
class bsTree : public dictionary<K,E>
{
   public:
      virtual void ascend() = 0;
                  // output in ascending order of key
      virtual ~bsTree(){};
};
#endif /* SRC_BSTREE_H_ */
