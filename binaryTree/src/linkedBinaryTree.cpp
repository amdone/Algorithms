/*
 * linkedBinaryTree.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */
#ifndef SRC_LINKEDBINARYTREE_CPP_
#define SRC_LINKEDBINARYTREE_CPP_

#include "linkedBinaryTree.h"



template<class E>
void linkedBinaryTree<E>::output(binaryTreeNode<E> *t){
    std::cout << t->element << ':';
}



template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t){
   if (t){//t!=NULL
      visit(t);
      preOrder(t->leftChild);
      preOrder(t->rightChild);
   }
}


template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t){
   if (t){//t!=NULL
      inOrder(t->leftChild);
      visit(t);
      inOrder(t->rightChild);
   }
}

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t){
   if (t){//t!=NULL
      postOrder(t->leftChild);
      postOrder(t->rightChild);
      visit(t);
   }
}

template <class E>
void linkedBinaryTree<E>::levelOrder(binaryTreeNode<E> *t){
   if(!t) return;
   std::queue<binaryTreeNode<E>*> q;
   q.push(t);
   while (!q.empty()){
	   t = q.front();
	   visit(t);  // visit t
	   q.pop();

      // put t's children on queue
      if (t->leftChild != NULL)
         q.push(t->leftChild);
      if (t->rightChild != NULL)
         q.push(t->rightChild);
   }
}
template<class E>
binaryTreeNode<E> * linkedBinaryTree<E>::copy(binaryTreeNode<E> *t){
	if(!t) return NULL;
	binaryTreeNode<E> * left,*right;
	left = copy(t->leftChild);
	right = copy(t->rightChild);
	return new binaryTreeNode<E>(t->element, left,right);
}

template<class E>
void linkedBinaryTree<E>::deleteNodes(binaryTreeNode<E> *t){
	if(!t) return;
	deleteNodes(t->leftChild);
	deleteNodes(t->rightChild);
	delete t;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::operator=(const linkedBinaryTree<E> & rightHand){
	if(this == & rightHand) return *this;//自己赋值到自己，但是现在的编译器对自己赋值给自己会提示错误
	deleteNodes(this->root);
	root = copy(rightHand.root);
	treeSize = rightHand.treeSize;//
	return *this;
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,
           linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)
{// Combine left, right, and element to make new tree.
 // left, right, and this must be different trees.
   // create combined tree
   root = new binaryTreeNode<E> (element, left.root, right.root);
   treeSize = left.treeSize + right.treeSize + 1;

   // deny access from trees left and right
   left.root = right.root = NULL;
   left.treeSize = right.treeSize = 0;
}

template<class E>
bool linkedBinaryTree<E>::isHBLTree(binaryTreeNode<E> *t){
	if(t == NULL)return true;
	if(t->leftChild == NULL && t->rightChild )return false;
	else{
		int leftS = 0,rightS = 0;
		binaryTreeNode<E> *l = t->leftChild;
		binaryTreeNode<E> *r = t->rightChild;
		while(l){
			leftS++;
			l = l->rightChild;
		}
		while(r){
			rightS++;
			r = r->rightChild;
		}
		if(leftS>=rightS){
			if(isHBLTree(t->leftChild))
				isHBLTree(t->rightChild);
			else return false;
		}
		else return false;
	}
	return true;
}

template<class E>
bool linkedBinaryTree<E>::isHBLTree(){
	return isHBLTree(this->root);
}


//注意模版静态类初始化的语法


template<class E>
void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*)=0;



#endif
