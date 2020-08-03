/*
 * binarySearchTree.h
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

#ifndef SRC_BINARYSEARCHTREE_H_
#define SRC_BINARYSEARCHTREE_H_



#include "bsTree.h"


//为了输出pair
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const std::pair<const K, E>& x){
	out << x.first << ' ' << x.second;
	return out;
}

#include "linkedBinaryTree.cpp"



template<class K, class E>
class binarySearchTree : public bsTree<K,E>,
                         public linkedBinaryTree<std::pair<const K, E> >
{


   public:
      // methods of dictionary
      bool empty() const {return this->treeSize == 0;}
      int size() const {return this->treeSize;}
      std::pair<const K, E>* find(const K& theKey) const;
      void insert(const std::pair<const K, E>& thePair);
      void erase(const K& theKey);
      void ascend();

};
#endif /* SRC_BINARYSEARCHTREE_H_ */
