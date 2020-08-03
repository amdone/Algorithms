/*
 * huffmanTree.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

//书上的实现方法，有内存没有释放，也不好理解
#include "linkedBinaryTree.cpp"
#include <queue>
#include <vector>
template<class T>
struct huffmanNode
{
   linkedBinaryTree<T> *tree;
   T weight;

   operator T () const {return weight;}
};

template <class T>
linkedBinaryTree<T>* huffmanTree(T weight[], int n){
   //使用STL的最小优先队列
   std::priority_queue<huffmanNode<T>,std::vector<huffmanNode<T> >,std::greater<huffmanNode<T> > > heap;
   huffmanNode<T> *hNode = new huffmanNode<T> [n + 1];
   linkedBinaryTree<T> emptyTree;
   for (int i = 1; i <= n; ++i){
      hNode[i].weight = weight[i];
      hNode[i].tree = new linkedBinaryTree<T>;
      hNode[i].tree->makeTree(hNode[i].weight, emptyTree, emptyTree);
      heap.push(hNode[i]);
   }

   huffmanNode<T> w, x, y;
   linkedBinaryTree<T> *z;
   for (int i = 1; i < n; ++i){
      // remove two lightest trees from the min heap
      x = heap.top(); heap.pop();
      y = heap.top(); heap.pop();
      w.weight = x.weight + y.weight;

      // combine into a single tree
      z = new linkedBinaryTree<T>;
      z->makeTree(w.weight, *x.tree, *y.tree);
      w.tree = z;
      heap.push(w);

      delete x.tree;
      delete y.tree;
   }
   // destructor for min heap deletes hNode
   return heap.top().tree;
}
