/*
 * huffmanTree.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */

//堆中存放huffmanTree，使用转移语义实现，效率比实现3高
//编译前，需做以下设置，采用C++11标准
//project->properties->C/C++Build->Settins->GCC C++ Compiler->Miscellanceous->Other flags :-std=c++11
#include "binaryTree.h"
#include <queue>
#include <vector>
#include <utility>
#include <functional>

template<class T>
class huffmanTree {
	template<class E>
	friend bool operator> (const huffmanTree<E> &fi,const huffmanTree<E> &se);
	template<class E>
	friend bool compHuffmanTree (const huffmanTree<E> &fi,const huffmanTree<E> &se);


public:
	huffmanTree(T weight[], int n);
	~huffmanTree();
	//以下两个函数priority_quque要使用，很多STL的容器需要这两个函数
	huffmanTree<T> & operator=(huffmanTree<T> && rhd);//c++11的移动赋值函数
	huffmanTree(huffmanTree<T>&& rhd);//c++11的移动复制构造函数

private:
	binaryTreeNode<T> *root;

	huffmanTree();
	huffmanTree(T element);
	huffmanTree(huffmanTree<T> &x,huffmanTree<T> &y);
	void erase(binaryTreeNode<T> *t);
};


template <class T>
void huffmanTree<T>::erase(binaryTreeNode<T> *t){
	if(!t) return;
	erase(t->leftChild);
	erase(t->rightChild);
	delete t;
}


template <class T>
huffmanTree<T>::~huffmanTree(){
	if(root) erase(root);//可能有将root指向的二叉树转移给其它的情形
};


template <class T>
huffmanTree<T>::huffmanTree(){
	root = NULL;
};

template <class T>
huffmanTree<T>::huffmanTree(T element){
	root = new binaryTreeNode<T>(element);
}

template <class T>
huffmanTree<T>::huffmanTree(huffmanTree<T>&&  rhd){
	root = rhd.root;//将rhd的root指向的二叉链表转移给this
	rhd.root = NULL;//防止析构时出错
}


template <class T>
huffmanTree<T> & huffmanTree<T>::operator=(huffmanTree<T> && rhd){
	if(root)erase(root);//释放已有的二叉链表
	root = rhd.root;//转移
	rhd.root=NULL;//同上个函数
	return *this;
}


template <class T>
huffmanTree<T>::huffmanTree(huffmanTree<T> &x, huffmanTree<T> &y){
	binaryTreeNode<T> *t = new binaryTreeNode<T>(x.root->element+y.root->element, x.root, y.root);
	root = t;//转移
	x.root = y.root = NULL;//防止析构时出错
}


//比较2棵huffman树的大小
template <class T>
bool operator>(const huffmanTree<T> &fi,const huffmanTree<T> &se){
	return fi.root->element > se.root->element;
}


//比较2棵huffman树的大小
//优先队列的greater要调用opertor>
template <class T>
bool compHuffmanTree(const huffmanTree<T> &fi,const huffmanTree<T> &se){
	return fi.root->element > se.root->element;
}


template <class T>
huffmanTree<T>::huffmanTree(T weight[], int n){
	//使用STL的最小优先队列，如何提供比较功能，有以下的写法，目前提倡lambda表达式
   //第1种写法 C++98
   //std::priority_queue<huffmanTree<T>,std::vector<huffmanTree<T> >,std::greater<huffmanTree<T> > > heap;

   //下面的做法也可以
   //因为priority_queue定义了1个成员变量 Compare comp，Compare即模版的第3个类型参数，
   //所以，Compare必须是一个类（型），才能有Compare comp的表达方式，Compare不能是一个普通函数。
   //其构造函数heap(comp)，利用构造函数的参数comp去初始化成员变量comp。
   //才有了下面的function写法

	//以下的写法，都是将普通函数，转换为函数对象，或者说转换为某个类的对象，这个类是STL种的预定义的模版类
	//第2种写法，C++03
   //std::function<bool(const huffmanTree<T> &,const huffmanTree<T> &)> comp = compHuffmanTree<T>;
   //std::priority_queue<huffmanTree<T>,std::vector<huffmanTree<T> >,decltype(comp) > heap(comp);

/*
    //这个写法相对最好
	//第3种写法：下面使用了c++11的lambda函数，可以就地定义函数，不用像上面的operaot>那样，需要成为huffmanTree的友元
   auto comp=[](const huffmanTree<T> &fi,const huffmanTree<T> &se){
		return fi.root->element > se.root->element;
   };

   //但是lambda函数是匿名类的对象，这个匿名类实现了operator(),就是lambda函数。
   //模版参数是类型，所以下面要用decltype(comp)
   //又因为priority_queue要调用比较函数对象的默认构造函数，但是lambda没有默认构造函数，所以，要使用heap(comp)
   std::priority_queue<huffmanTree<T>,std::vector<huffmanTree<T> >,decltype(comp) > heap(comp);

*/
	//第4种写法，C++03 利用bind将普通函数，转换成function object
	//auto comp = std::bind(compHuffmanTree<T>,std::placeholders::_1,std::placeholders::_2);
	//std::priority_queue<huffmanTree<T>,std::vector<huffmanTree<T> >,decltype(comp) > heap(comp);

	//第5种写法，C++98，利用ptr_fun将普通函数转换成function object，已经过时的写法
	bool (*p)(const huffmanTree<T> &,const huffmanTree<T> &) = compHuffmanTree<T>;
	auto comp = std::ptr_fun(p);
	std::priority_queue<huffmanTree<T>,std::vector<huffmanTree<T> >,decltype(comp) > heap(comp);


	for (int i = 0; i < n; ++i)
	   //huffmanTree(weight[i])调用huffmanTree的构造函数，产生1个对象，不过，该对象不是放在堆空间，即不通过new生成。
	   heap.push(std::move(huffmanTree(weight[i])));

   huffmanTree<T> x, y,w;

   for(int i = 0; i < n-1;i++){
	   //heap.top()返回的是const引用，先用const_cast去掉const
	   //再用move将左值改为右值，让编译器调用函数
	   //huffmanTree<T> & huffmanTree<T>::operator=(huffmanTree<T> && rhd){

	   x=std::move(const_cast<huffmanTree<T>& >(heap.top()));
	   heap.pop();

	   y=std::move(const_cast<huffmanTree<T>& >(heap.top()));
	   heap.pop();

	   heap.push(std::move(huffmanTree(x,y)));
   }

   //不能使用
   //*this = const_cast<huffmanTree<T>& >(heap.top());
   //因为this还不存在
   w=std::move(const_cast<huffmanTree<T>& >(heap.top()));
   root = w.root;
   w.root = NULL;
}
