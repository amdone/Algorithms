/*
 * binaryTree.h
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

#ifndef SRC_BINARYTREE_H_
#define SRC_BINARYTREE_H_
#include <iostream>
template <class T>
struct binaryTreeNode{
   T element;
   binaryTreeNode<T> *leftChild,   // left subtree
                     *rightChild;  // right subtree
   binaryTreeNode() :element(T()){leftChild = rightChild = NULL;}
   binaryTreeNode(const T& theElement):element(theElement){
      leftChild = rightChild = NULL;
   }
   binaryTreeNode(const T& theElement,binaryTreeNode *theLeftChild,binaryTreeNode *theRightChild)
                  :element(theElement){
      leftChild = theLeftChild;
      rightChild = theRightChild;
   }
};


template<class T>
class binaryTree{
   public:
      virtual ~binaryTree() {}
      virtual bool empty() const = 0;
      virtual int size() const = 0;
      virtual void preOrder(void (*) (T *)) = 0;
              // parameter is a pointer to a function whose return
              // type is void and has a single argument of type T*
      virtual void inOrder(void (*) (T *)) = 0;
      virtual void postOrder(void (*) (T *)) = 0;
      virtual void levelOrder(void (*) (T *)) = 0;
};

#endif /* SRC_BINARYTREE_H_ */
