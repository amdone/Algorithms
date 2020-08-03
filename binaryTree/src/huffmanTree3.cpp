/*
 * huffmanTree.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

//堆中存放huffmanTree，采用通常意义的构造和赋值语义，而不是第4种方法的转移语义
#include "binaryTree.h"
#include <queue>
#include <vector>
template<class T>
class huffmanTree {
	template<class E>
	friend bool operator> (const huffmanTree<E> &fi,const huffmanTree<E> &se);

public:
	huffmanTree(T weight[], int n);
	~huffmanTree(){	if(root) erase(root);};

	//STL的优先队列要使用下面的2个函数,必须const参数
	huffmanTree<T> & operator=(const huffmanTree<T> &rhd);
	huffmanTree(const huffmanTree<T>& rhd);

private:
	binaryTreeNode<T> *root;
	huffmanTree(){root = NULL;};
	huffmanTree(T element){	root = new binaryTreeNode<T>(element);};

	huffmanTree(huffmanTree<T> &x,huffmanTree<T> &y);
	void erase(binaryTreeNode<T> *t);
	binaryTreeNode<T> * copy(binaryTreeNode<T> *t);

};


template <class T>
void huffmanTree<T>::erase(binaryTreeNode<T> *t){
	if(!t) return;
	erase(t->leftChild);
	erase(t->rightChild);
	delete t;
}

template <class T>
huffmanTree<T>::huffmanTree(const huffmanTree<T>&  rhd){
	root =copy(rhd.root);//复制rhd的二叉链表而不是转移
}


template <class T>
huffmanTree<T> & huffmanTree<T>::operator=(const huffmanTree<T> &rhd){
	if(root)erase(root);
	root =copy(rhd.root);
	//这里也可以采用转移语义
	//root = rhd.root;
	//rhd.root = NULL;
	return *this;
}


template <class T>
binaryTreeNode<T> * huffmanTree<T>::copy(binaryTreeNode<T> *t){
	if(!t) return NULL;
	binaryTreeNode<T> *left, *right;
	left = copy(t->leftChild);
	right = copy(t->rightChild);
	return new binaryTreeNode<T>(t->element,left,right);
}


template <class T>
huffmanTree<T>::huffmanTree(huffmanTree<T> &x, huffmanTree<T> &y){
	root = new binaryTreeNode<T>(x.root->element + y.root->element, x.root, y.root);
	x.root = y.root = NULL;
}

template <class T>
bool operator>(const huffmanTree<T> &fi,const huffmanTree<T> &se){
	return fi.root->element > se.root->element;
}

template <class T>
huffmanTree<T>::huffmanTree(T weight[], int n){
   //使用STL的最小优先队列
   std::priority_queue<huffmanTree<T>,std::vector<huffmanTree<T> >,std::greater<huffmanTree<T> > > heap;
   for (int i = 0; i < n; ++i)
	   //huffmanTree(weight[i])生成1个对象。
	   heap.push(huffmanTree(weight[i]));

   huffmanTree<T> x, y,w;
   for(int i = 0; i < n-1;i++){
      x = const_cast<huffmanTree<T>& >(heap.top());
      heap.pop();

      y = const_cast<huffmanTree<T>& >(heap.top());
      heap.pop();

      heap.push(huffmanTree(x,y));
   }

   //不能使用
   //*this = const_cast<huffmanTree<T>& >(heap.top());
   //因为this还不存在
   w = const_cast<huffmanTree<T>& >(heap.top());
   this->root = copy(w.root);//这里可以采用转移语义
}
