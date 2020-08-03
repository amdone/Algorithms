/*
 * huffmanTree.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */


//在优先队列中存放指针，避免对象构造和赋值函数的开销
#include <queue>
#include <vector>
#include <functional>
#include "binaryTree.h"//为了使用binaryTreeNode


template<class T>
class huffmanTree {
public:
	huffmanTree(T weight[], int n);
	~huffmanTree(){if(root) erase(root);};
	//STL优先队列使用默认的构造和赋值，即指针的复制
private:
	binaryTreeNode<T> *root;

public://提供比较2个指针所指huffmanTree的大小比较
	//类comp重载了operator(),所以它是一个仿函数，可以当函数使用
	//std::binary_function在C++11以后是过时的用法了。
	//更新的用法应该用lambda函数，参见huffmanTree4.cpp的第3种写法
	struct comp : public std::binary_function<huffmanTree *, huffmanTree *, bool>{
	    bool operator()(const huffmanTree *lhd, const huffmanTree *rhd) const{
	    	return lhd->root->element > rhd->root->element;
	    }
	};

private:
	huffmanTree(huffmanTree<T> *x, huffmanTree<T> *y);
	huffmanTree(T element){root = new binaryTreeNode<T>(element);}
	void erase(binaryTreeNode<T> *t);

private:
	huffmanTree<T>& operator=(huffmanTree<T>& rhd);//禁止外部使用
	huffmanTree();//{root = NULL;}//禁止外部使用默认构造函数构造huffmanTree



};


template <class T>
void huffmanTree<T>::erase(binaryTreeNode<T> *t){
	if(!t) return;
	erase(t->leftChild);
	erase(t->rightChild);
	delete t;
}
/*
template <class T>
huffmanTree<T>& huffmanTree<T>::operator=(huffmanTree<T>& rhd){
	root = rhd.root;//使用转移语义
	rhd.root = NULL;
	return *this;
}
*/
template <class T>
huffmanTree<T>::huffmanTree(huffmanTree<T> *x, huffmanTree<T> *y){
	root = new binaryTreeNode<T>(x->root->element + y->root->element, x->root, y->root);
	x->root = y->root = NULL;
}


template <class T>
huffmanTree<T>::huffmanTree(T weight[], int n){
	//使用STL的最小优先队列，使用huffmanTree类提供的比较大小的仿函数comp作为比较大小的方法
	//队列中存放的是指针，与存放huffmanTree对象相比，可以减少复制的代价
   std::priority_queue<huffmanTree<T> *,std::vector<huffmanTree<T>* >,huffmanTree<T>::comp  > heap;

   for (int i = 0; i < n; ++i)
      heap.push(new huffmanTree<T>(weight[i]));//new出了n个huffmanTree

   huffmanTree<T> *x, *y;
   for (int i = 0; i < n - 1; ++i){
      x = heap.top(); heap.pop();
      y = heap.top(); heap.pop();

      heap.push(new huffmanTree<T>(x,y));//new出了1个huffmanTree

      delete x;//释放1个huffmanTree
      delete y;//释放1个huffmanTree
   }

   y = heap.top(); heap.pop();
   this->root = y->root;
   y->root = NULL;
   delete y;//再释放最后1个
}
