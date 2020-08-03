/*
 * BTreeNode.h
 *
 *  Created on: 2019Äê7ÔÂ13ÈÕ
 *      Author: Eichi
 */

#ifndef SRC_BTREENODE_H_
#define SRC_BTREENODE_H_
#include <iostream>

template <class T>
struct BTreeNode{
	int keyNum;
	bool leaf;
	T *element;
	BTreeNode **child;

	BTreeNode(){
		element = NULL;
		keyNum = 0;
		child = NULL;
		leaf = true;
	}

	BTreeNode(int rank){
		element = new T[rank];
		keyNum = 0;
		leaf = true;
		child = new BTreeNode*[rank];
	}

	BTreeNode(int rank,bool leaf){
		keyNum = 0;
		this->leaf = leaf;
		element = new T[rank];
		child = new BTreeNode*[rank];

	}
	void insertNode(int rank,T theElement,BTreeNode* pc);
	void splitChild(int rank,int index,BTreeNode *y,BTreeNode *pc);
	void output();

};




#endif /* SRC_BTREENODE_H_ */





