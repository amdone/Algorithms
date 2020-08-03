/*
 * maxHblt.h
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 *      这个实现方法和1中的没有本质不同，只是感觉好理解一点
 */

#ifndef SRC_MAXHBLT_H_
#define SRC_MAXHBLT_H_
#include <queue>
#include "maxPriorityQueue.h"
#include "linkedBinaryTree.cpp"
template<class T>
class maxHblt : public maxPriorityQueue<T>,
                public linkedBinaryTree<std::pair<int,T> >{
   public:
      bool empty() const {return 0 == this->treeSize;}
      int size() const {return this->treeSize;}
      const T& top();
      void pop();
      void push(const T&);
      void initialize(T *, int);
      void meld(maxHblt<T>& theHblt);
      void output() {this->postOrder(hbltOutput); std::cout << std::endl;}
   private:
      binaryTreeNode<std::pair<int,T> >* meld(binaryTreeNode<std::pair<int,T> >*,
                binaryTreeNode<std::pair<int,T> >* );
      static void hbltOutput(binaryTreeNode<std::pair<int,T> > *t)
                  {std::cout << t->element.second << ' ';}
};
#endif /* SRC_MAXHBLT_H_ */
