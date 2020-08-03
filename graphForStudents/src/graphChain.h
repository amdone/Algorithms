/*
 * graphChain.h
 *
 *  Created on: 2019年6月8日
 *      Author: Eichi
 */

#ifndef SRC_GRAPHCHAIN_H_
#define SRC_GRAPHCHAIN_H_

#include "chain.h"


template <class T>
class graphChain : public chain<T>
{
	//template<class E> friend class linkedWDigraph;//因为要访问firstNode
   public:
      T* eraseElement(int theVertex)
      {
         chainNode<T> *current = this->firstNode,
                      *trail = NULL; // one behind current
        while (current != NULL && current->element.first != theVertex)
         {
            trail = current;
            current = current->next;
         }
        if (current == NULL) // no match
            return NULL;
        T* theElement = &current->element; // save matching element
        // remove current from chain
         if (trail != NULL)
            trail->next = current->next;
         else
            this->firstNode = current->next; // current is first node
        delete current;//节点被删除了，怎么还能有current->element呢？
         this->listSize--;
         return theElement;
      }

      chainNode<T> * getFisrtNode(){//因为要访问firstNode,如果前面不声明为友元，就要增加这个函数
    	  return this->firstNode;
      }

};



#endif /* SRC_GRAPHCHAIN_H_ */
