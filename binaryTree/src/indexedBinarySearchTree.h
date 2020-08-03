/*
 * indexedBinarySearchTree.h
 *
 *  Created on: 2017年5月14日
 *      Author: lsn
 */

#ifndef SRC_INDEXEDBINARYSEARCHTREE_H_
#define SRC_INDEXEDBINARYSEARCHTREE_H_

#include "bsTree.h"
#include "linkedBinaryTree.cpp"


//binaryTree节点中的element，第2种实现方法，推荐。
//另外一种方法就是修改binaryTreeNode，增加一个数据域leftSize。
template<class K, class E>
struct indexedBinarySearchTreeElement{
	K	key;
	E	value;
	int leftSize;
};

//为了输出indexedBinarySearchTreeElement
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const indexedBinarySearchTreeElement<K,E>& x){
	out <<x.key<<':'<<x.value<<':'<<x.leftSize;
	return out;
}



template<class K, class E>
class indexedBinarySearchTree :public bsTree<K,E>,
                        public linkedBinaryTree<indexedBinarySearchTreeElement<K, E> >{
public:
    // methods of dictionary
    bool empty() const;
    int size() const;
    std::pair<const K, E>* find(const K& theKey) const;
    void insert(const std::pair<const K, E>& thePair);
    void erase(const K& theKey);

    std::pair<const K, E>* get(int theIndex) const;

    // additional method of bsTree
    void ascend();
};

#endif /* SRC_INDEXEDBINARYSEARCHTREE_H_ */
