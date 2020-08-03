/*
 * linkedBinaryTree.h
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

#ifndef SRC_LINKEDBINARYTREE_H_
#define SRC_LINKEDBINARYTREE_H_
#include <queue>
#include <algorithm>
#include <iostream>
#include <stdexcept>


#include "binaryTree.h"


template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E> >
{
   public:
      linkedBinaryTree() {root = NULL; treeSize = 0;}
      ~linkedBinaryTree(){deleteNodes(root);};

      linkedBinaryTree<E>& operator=(const linkedBinaryTree<E> & rightHand);

      void makeTree(const E& element,linkedBinaryTree<E>&, linkedBinaryTree<E>&);

      bool empty() const {return 0 == treeSize ;}
      int size() const {return treeSize;}
      bool isHBLTree();
      bool isHBLTree(binaryTreeNode<E>* t);

   public://将核心函数封装得到的一组函数
      void preOrderOutput() {preOrder(output); std::cout<<std::endl;}
      void inOrderOutput() {inOrder(output); std::cout<<std::endl;}
      void postOrderOutput() {postOrder(output);std::cout<<std::endl;}
      void levelOrderOutput() {levelOrder(output);std::cout<<std::endl;}

      void preOrder(void(*theVisit)(binaryTreeNode<E>*)){
    	  visit = theVisit; preOrder(root);}
      void inOrder(void(*theVisit)(binaryTreeNode<E>*)){
    	  visit = theVisit; inOrder(root);}
      void postOrder(void(*theVisit)(binaryTreeNode<E>*)){
    	  visit = theVisit; postOrder(root);}
      void levelOrder(void(*theVisit)(binaryTreeNode<E> *)){
    	  visit=theVisit;levelOrder(root);}

   protected://以下是核心函数
      void preOrder(binaryTreeNode<E> *t);//先序遍历以t为根的二叉树
      void inOrder(binaryTreeNode<E> *t);
      void postOrder(binaryTreeNode<E> *t);
      void levelOrder(binaryTreeNode<E> *t);//层次遍历以t为根的二叉树


      binaryTreeNode<E> * copy(binaryTreeNode<E> *t);//复制以t为根的二叉树，得到一颗新的二叉树，根节点是函数的返回值
      void deleteNodes(binaryTreeNode<E> *t);//释放以t为根的二叉树的所有节点的空间

      static void output(binaryTreeNode<E> *t);


   protected:
      binaryTreeNode<E> *root;                //指向二叉链表的根节点
      int treeSize;                           //二叉树中节点的个数
      static void (*visit)(binaryTreeNode<E>*);// visit是一个指针，指向一个函数，该函数的返回值是 void，有1个参数。
                                               //visit是供所有的linkedBinaryTree的对象调用，一个对象改了这个值......
                                               //不是一个好办法
};

#endif /* SRC_LINKEDBINARYTREE_H_ */
