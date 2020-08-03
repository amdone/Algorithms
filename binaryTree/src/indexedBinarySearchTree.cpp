
#include "indexedBinarySearchTree.h"
#include <stack>

template<class K, class E>
int indexedBinarySearchTree<K,E>::size() const{
	return this->treeSize;
}


template<class K, class E>
bool indexedBinarySearchTree<K,E>::empty() const{
	return (0 == this->treeSize);
}

template<class K, class E>
void indexedBinarySearchTree<K,E>::ascend(){
	this->inOrderOutput();
}


template<class K, class E>
std::pair<const K, E>* indexedBinarySearchTree<K,E>::find(const K& theKey) const{
	static std::pair<K, E> result;//缺点是引入了关联，在多线程会有问题，另一般法见get的解释
	binaryTreeNode<indexedBinarySearchTreeElement<K, E> > *p = this->root;
	while(p){
		if(theKey == p->element.key){
			result = std::pair<const K, E>(p->element.key,p->element.value);//生成对象，或者用make_pair
			return (std::pair<const K, E>*)&result;
		}
		if(theKey < p->element.key)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	return NULL;
}

template<typename K,typename E>
std::pair<const K, E>* indexedBinarySearchTree<K,E>::get(int theIndex) const{
	//需要检查theIndex 的有效性
	;

	binaryTreeNode<indexedBinarySearchTreeElement<K, E> > *p = this->root;
	while(p){
		if( theIndex == p->element.leftSize + 1)
			//接口必须要返回一个指针，只好new一个，调用完这个函数后，要delete。
			return new std::pair<const K,E>(p->element.key,p->element.value);
		if(theIndex <= p->element.leftSize)
			p = p->leftChild;
		else{
			theIndex -= p->element.leftSize + 1;
			p = p->rightChild;
		}

	}
	return NULL;
}

template<class K, class E>
void indexedBinarySearchTree<K,E>::insert(const std::pair<const K,E>& theData){
	K theKey = theData.first;
	E theValue = theData.second;

	std::stack<binaryTreeNode<indexedBinarySearchTreeElement<K, E>>*> ancestors;
	binaryTreeNode<indexedBinarySearchTreeElement<K, E> > *p = this->root,*pp;
	if(!p){//插入前是空树
		indexedBinarySearchTreeElement<K, E> newElement;
		newElement.key = theKey;
		newElement.value = theValue;
		newElement.leftSize = 0;
	    this->root = new binaryTreeNode<indexedBinarySearchTreeElement<K, E> > (newElement);
	    this->treeSize = 1;
	    return;
	}
	while (p){//找到插入的位置
		 ancestors.push(p);
		 if(theKey == p->element.key) break;
		 if(theKey < p->element.key)
			 p = p ->leftChild;
		 else
			 p = p->rightChild;
	}
	if(p){
		p->element.value= theValue;//该key-value已有，替换value
		return;
	}
    //插入新节点
	indexedBinarySearchTreeElement<K, E> newElement;
	newElement.key = theKey;
	newElement.value = theValue;
	newElement.leftSize = 0;
    p = new binaryTreeNode<indexedBinarySearchTreeElement<K, E> > (newElement);
 	pp = ancestors.top();
 	if(theKey < pp->element.key)
 		pp->leftChild = p;
 	else
 		pp->rightChild = p;
 	++this->treeSize;
 	//调整祖先节点的索引值
 	while(!ancestors.empty()){
 		pp = ancestors.top();
 		ancestors.pop();
 		if(p == pp->leftChild)
 			++pp->element.leftSize;
 		p = pp;
 	}
}
template<class K, class E>
void indexedBinarySearchTree<K,E>::erase(const K& theKey){
	if(!this->root) return; //空树，不做处理

	std::stack<binaryTreeNode<indexedBinarySearchTreeElement<K, E>>*> ancestors;
	binaryTreeNode<indexedBinarySearchTreeElement<K, E> > *p = this->root,*pp=NULL,*c=NULL;
	while (p){//找到删除节点
		 ancestors.push(p);
		 if(theKey == p->element.key) break;
		 if(theKey < p->element.key)
			 p = p ->leftChild;
		 else
			 p = p->rightChild;
	}
	if(!p) return;//无该key-value

	ancestors.pop();//p是待删除节点，但已经在栈里,栈里只存放待删除节点的父节点
	//p指向待删除节点
	if (p->leftChild != NULL && p->rightChild != NULL){
		//p有左右孩子，找到左孩子中值最大的节点，它在左子树中最右面
		pp = p->leftChild;
		while (pp->rightChild){
			ancestors.push(pp);
			pp = pp->rightChild;
		}
		//用p节点的值替代pp节点
		p->element.key = pp->element.key;
		p->element.value = pp->element.value;
		//p成为待删除节点
		p = pp;
	}

	// 待删除节点p只有左孩子或右孩子

	if(ancestors.empty()){//待删除节点是root
		if(!p->leftChild)
			this->root = p->rightChild;
		else
			this->root = p->leftChild;

		--this->treeSize;
		delete p;
		return;
	}
	if(p->leftChild)
		c = p->leftChild;
	else
		c = p->rightChild;

	pp = ancestors.top();
	if(p == pp->leftChild)
		pp->leftChild = c;
	else
		pp->rightChild = c;
	--this->treeSize;
	delete p;
	//修改祖先节点的index值
	while(!ancestors.empty()){
		pp = ancestors.top();
		ancestors.pop();
		if(c == pp->leftChild)//c代替了p
			--pp->element.leftSize;
		c = pp;
	}

}

