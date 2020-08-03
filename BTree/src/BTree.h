/*
 * BTree.h
 *
 *  Created on: 2019Äê7ÔÂ13ÈÕ
 *      Author: Eichi
 */


#ifndef SRC_BTREE_H_
#define SRC_BTREE_H_

#include "BTreeNode.h"


template<class K,class E>
class BTree{
	public:
		BTree();
		BTree(int rank);
		bool empty() const;
		int size() const;

		void insert(const std::pair<const K, E>& thePair);
		void output();
		void BTree_print(BTreeNode<std::pair<K,E>> *r, BTreeNode<std::pair<K,E>> *pc,int layer);
		void print();

		std::pair<K, E> BTreeMaximum(BTreeNode<std::pair<K, E>> *x);
		std::pair<K, E> BTreeMinimum( BTreeNode<std::pair<K,E>> *x );
		void Delete(int k);
		void BTreeDelete(BTreeNode<std::pair<K, E>> *x, int k);
	private:
		BTreeNode<std::pair<K,E>> *root;
		int treeSize;
		int rank;
		BTreeNode<std::pair<K,E>> *pointerCollector;


};


template <class K, class E>
std::ostream& operator<<(std::ostream& out,std::pair<K, E>& x){
	out << x.first << '-' << x.second;
	return out;
}


#endif /* SRC_BTREE_H_ */
