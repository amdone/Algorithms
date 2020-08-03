/*
 * maxHblt.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

#include "maxHblt.h"

template<class T>
inline const T& maxHblt<T>::top(){// return max element
	if (0 == this->treeSize)
		throw std::out_of_range("empty");
    return this->root->element.second;

}

template<class T>
inline void maxHblt<T>::meld(maxHblt<T>& theHblt){// meld *this and theHblt
      meld(this->root, theHblt.root);
      this->treeSize += theHblt.treeSize;
      theHblt.root = NULL;
      theHblt.treeSize = 0;
}


template<class T>
void maxHblt<T>::push(const T& theElement){
	// Insert theElement into the leftist tree.
   // Create tree with one node.
   binaryTreeNode<std::pair<int,T> > *q =
      new binaryTreeNode<std::pair<int,T> > (std::pair<int,T>(1, theElement));

   // meld q and original tree
   meld(this->root,q);
   ++this->treeSize;
}

template<class T>
void maxHblt<T>::pop()
{// Delete max element.
   if (this->root == NULL)
      throw std::out_of_range("empty");

   // tree not empty
   binaryTreeNode<std::pair<int,T> > *left = this->root->leftChild,
                               *right = this->root->rightChild;
   delete this->root;
   this->root = left;
   meld(this->root, right);
   --this->treeSize;
}
template<class T>
void maxHblt<T>::initialize(T* theElements, int theSize)
{// Initialize hblt with theElements[1:theSize].
   std::queue<binaryTreeNode<std::pair<int,T> >*> q;
   this->deleteNodes(this->root);  // make *this empty
   // initialize queue of trees
   for (int i = 1; i <= theSize; ++i)// create trees with one node each
      q.push(new binaryTreeNode<std::pair<int,T> >(std::pair<int,T>(1, theElements[i])));

   // repeatedly meld from queue
   for (int i = 1; i <= theSize - 1; ++i){// pop and meld two trees from queue
      binaryTreeNode<std::pair<int,T> > *b = q.front();
      q.pop();
      binaryTreeNode<std::pair<int,T> > *c = q.front();
      q.pop();
      meld(b,c);
      // put melded tree on queue
      q.push(b);
   }
   if (theSize > 0) this->root = q.front();
   this->treeSize = theSize;
}

template<class T>
void maxHblt<T>::meld(binaryTreeNode<std::pair<int, T> >* &x, binaryTreeNode<std::pair<int, T> >* &y)
{// Meld leftist trees with roots *x and *y. Return pointer to new root in x.
   if (!y)   return;
   if (!x)   {x = y; return;}

   // neither is empty, swap x and y if necessary
   if (x->element.second < y->element.second) swap(x, y);

   meld(x->rightChild,y);
   // swap subtrees of x if necessary and set x->element.first
    if (!x->leftChild){// left subtree empty, swap the subtrees
          x->leftChild = x->rightChild;
          x->rightChild = NULL;
          x->element.first = 1;
    }
    else{// swap only if left subtree has smaller s value
       if (x->leftChild->element.first < x->rightChild->element.first)
          swap(x->leftChild, x->rightChild);
       // update s value of x
       x->element.first = x->rightChild->element.first + 1;
    }
 }
