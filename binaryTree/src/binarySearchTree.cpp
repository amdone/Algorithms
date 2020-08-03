/*
 * binarySearchTree.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */
#include <functional>
#include "binarySearchTree.h"



template<class K, class E>
void binarySearchTree<K,E>::ascend() {

    // additional method of bsTree
    //可以将this->inOrderOutput(); 写成：
	//linkedBinaryTree<std::pair<const K, E> >::inOrderOutput();


	this->inOrderOutput();
}

template<class K, class E>
std::pair<const K, E>* binarySearchTree<K,E>::find(const K& theKey) const
{// Return pointer to matching pair.
 // Return NULL if no matching pair.
   // p starts at the root and moves through
   // the tree looking for an element with key theKey
   binaryTreeNode<std::pair<const K, E> > *p = linkedBinaryTree<std::pair<const K, E> >::root;
   while (p != NULL)
      // examine p->element
      if (theKey < p->element.first)
         p = p->leftChild;
      else
         if (theKey > p->element.first)
            p = p->rightChild;
         else // found matching pair
            return &p->element;

   // no matching pair
   return NULL;
}
template<class K, class E>
void binarySearchTree<K,E>::insert(const std::pair<const K, E>& thePair){
	// find place to insert
   binaryTreeNode<std::pair<const K, E> > *p = this->root,*pp = NULL;
   while (p != NULL){// examine p->element
      pp = p;// move p to a child
      if (thePair.first < p->element.first)
         p = p->leftChild;
      else
         if (thePair.first > p->element.first)
            p = p->rightChild;
         else{// replace old value
            p->element.second = thePair.second;
            return;
         }
   }
   // get a node for thePair and attach to pp
   binaryTreeNode<std::pair<const K, E> > *newNode
                 = new binaryTreeNode<std::pair<const K, E> > (thePair);
   if (this->root != NULL) // the tree is not empty
      if (thePair.first < pp->element.first)
         pp->leftChild = newNode;
      else
         pp->rightChild = newNode;
   else
	   this->root = newNode; // insertion into empty tree
   ++this->treeSize;
}


//erase函数与书上不一样，没有new q
template<class K, class E>
void binarySearchTree<K,E>::erase(const K& theKey){
   // search for node with key theKey
   binaryTreeNode<std::pair<const K, E> > *p = this->root,*pp = NULL;
   while (p != NULL && p->element.first != theKey){//注意两个句子位置不能颠倒
      pp = p;   // move to a child of p
      if (theKey < p->element.first)
         p = p->leftChild;
      else
         p = p->rightChild;
   }
   if (p == NULL)return; // no pair with key theKey

   if (p->leftChild != NULL && p->rightChild != NULL){// two children
      // find largest element in left subtree of p
      binaryTreeNode<std::pair<const K, E> > *s = p->leftChild,
                                       *ps = p;  // parent of s
      while (s->rightChild != NULL){// move to larger element
         ps = s;
         s = s->rightChild;
      }

      //一般情况下s是ps的右孩子,但当ps=p时，s是ps(即p)的左孩子
      //将s的左孩子给它的父节点ps
      if(ps != p)//s是ps的右孩子
    	  ps->rightChild = s->leftChild;
      else//s是ps的左孩子，因为后面要用s替换p，这句看似多余，但又是必须的
    	  //否则，下面的将p的左右孩子给s，会把s作为s的左孩子
    	  ps->leftChild = s->leftChild;
      //因为s本身没有右孩子，上面又将它的左孩子给了双亲节点，所以，这时，s没有孩子。

      //将p的左右孩子给s
      s->leftChild = p->leftChild;
      s->rightChild = p->rightChild;

      //将s作为p的双亲的孩子，替换p
      if (pp == NULL) //要删除的节点p是根节点
    	  this->root = s;
      else if (p == pp->leftChild)
              pp->leftChild = s;
           else
              pp->rightChild = s;

      --this->treeSize;
      delete p;
      return;
   }
   // p has at most one child
   // save child pointer in c
   binaryTreeNode<std::pair<const K, E> > *c;
   if (p->leftChild != NULL)
      c = p->leftChild;
   else
      c = p->rightChild;

   // delete p
   if (p == this->root)
	   this->root = c;
   else{// is p left or right child of pp?
      if (p == pp->leftChild)
         pp->leftChild = c;
      else
    	  pp->rightChild = c;
   }
   --this->treeSize;
   delete p;
}


