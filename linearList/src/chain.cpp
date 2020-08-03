/*
 * chain.cpp
 *
 *  Created on: 2017年3月19日
 *      Author: lsn
 */

#include "chain.h"
//#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>


template<class T>
chain<T>::chain(int initialCapacity)
{// Constructor.
   if (initialCapacity < 1)
     throw std::invalid_argument("Initial capacity = " + std::to_string(initialCapacity) + " Must be > 0");
   firstNode = NULL;
   listSize = 0;
}


template<class T>
chain<T>::chain(const chain& theList)
{// 因为是复制构造函数，要生成this，先给它的2个成员变量赋值，初始为空表
	firstNode = NULL;
	listSize = theList.listSize;


	if(0 == listSize) return;//theList是空表，则this也是空表，返回

	//theList中至少有1个节点，先复制第1个节点
	chainNode<T> *p = theList.firstNode;
	firstNode = new chainNode<T>(p->element,NULL);

	chainNode<T> *q = firstNode;
	while(p->next != NULL){//如果刚复制的节点不是theList的最后1个节点，则继续复制其它的节点
		p = p->next;
		q->next = new chainNode<T>(p->element,NULL);
		q = q->next;
	}

}


template<class T>
chain<T>::~chain()
{
   while (firstNode != NULL)
   {// delete firstNode
      chainNode<T>* nextNode = firstNode->next;
      delete firstNode;
      firstNode = nextNode;
   }
}


template<class T>
void chain<T>::checkIndex(int theIndex) const{
	if(theIndex < 0 || theIndex >=listSize){
		throw std::out_of_range("index = " + std::to_string(theIndex) + " size = " + std::to_string(listSize)); //C++11标准引入的
	}
}


template<class T>
T& chain<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);

   // move to desired node
   chainNode<T>* currentNode = firstNode;
   for (int i = 0; i < theIndex; i++)currentNode = currentNode->next;

   return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theElement) const{
  chainNode<T>* currentNode = firstNode;
   int index = 0;  // index of currentNode
   while (currentNode != NULL && currentNode->element != theElement){
     currentNode = currentNode->next;
      index++;
   }
  if (currentNode == NULL)
      return -1;
   else
      return index;
}



template<class T>
void chain<T>::insert(int theIndex, const T& theElement){
   if (theIndex != listSize)
	   checkIndex(theIndex);
   if (theIndex == 0)
      firstNode = new chainNode<T>(theElement, firstNode);
   else
   {  // find predecessor of new element
      chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex - 1; ++i) p = p->next;
      p->next = new chainNode<T>(theElement, p->next);
   }
   ++listSize;
}

template<class T>
void chain<T>::erase(int theIndex){
  checkIndex(theIndex);
  chainNode<T>* deleteNode;
   if (theIndex == 0){
     deleteNode = firstNode;
      firstNode = firstNode->next;
   }
   else
   {  // use p to get to predecessor of desired node
      chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex - 1; ++i) p = p->next;

      deleteNode = p->next;
      p->next = p->next->next; // remove deleteNode from chain
   }
   --listSize;
   delete deleteNode;
}


template <class T>
chain<T>& chain<T>::operator=(const chain<T>& rhs){
	if(this == &rhs) return *this;

	listSize = rhs.listSize;

	 while (firstNode != NULL)
	 {
	     chainNode<T>* nextNode = firstNode->next;
	     delete firstNode;
	     firstNode = nextNode;
	   }
	if(listSize == 0) return *this;
	chainNode<T> *p = rhs.firstNode;
	firstNode = new chainNode<T>(p->element,NULL);

	chainNode<T> *q = firstNode;
	while(p->next != NULL){
		p = p->next;
		q->next = new chainNode<T>(p->element,NULL);
		q = q->next;
	}
	return *this;
}


template<class T>
void chain<T>::reverse(){
	if(firstNode == NULL || firstNode->next == NULL)return;
	else{
	chainNode<T>* p = NULL;
	chainNode<T>* next = NULL;
	while(firstNode != NULL){
		next = firstNode->next;
		firstNode->next = p;
		p = firstNode;
		firstNode = next;
		}
		firstNode = p;
	}

}
template<class T>
void chain<T>::output(std::ostream& out) const
{
   chainNode<T> *p = firstNode;
   out <<std::endl;
   while(p != NULL){
	   out << p->element <<" ";
	   p = p->next;
   }
   out << std::endl;
}



// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x){
	x.output(out);
	return out;
}

template <class T>
bool chain<T>::operator==(const chain<T>& rhs){
	if(listSize != rhs.listSize)return false;
	chainNode<T>* p = firstNode;
	int i = 0;
	while(p != NULL){
		if(p->element != rhs.get(i))return false;
		p = p->next;
		++i;
	}
	return true;
}


template <class T>
bool chain<T>::operator!=(const chain<T>& rhs){
	return *this==rhs?false:true;
}

template <class T>
int chain<T>::iteratorRan::getIndex()const{
	chainNode<T> *p = originalNode;
	int index = 0;
	while(p != node){
		index++;
		p = p->next;
	}
	return index;
}

template <class T>
 bool chain<T>::iteratorRan::operator<(const iteratorRan right) const{
	return this->getIndex() < right.getIndex();
}
template <class T>
 bool chain<T>::iteratorRan::operator>(const iteratorRan right) const{
	return this->getIndex() > right.getIndex();
}
template <class T>
 bool chain<T>::iteratorRan::operator<=(const iteratorRan right) const{
	return this->getIndex() <= right.getIndex();
}
template <class T>
bool chain<T>::iteratorRan::operator>=(const iteratorRan right) const{
	return this->getIndex() >= right.getIndex();
}


template <class T>
T& chain<T>::iteratorRan::operator[](int index) const{
	chainNode<T> *p;
	p = originalNode;
	for(int i = 0; i < index; ++i) p = p->next;
	return p->element;

}
template <class T>
typename chain<T>::iteratorRan& chain<T>::iteratorRan::operator--(){   // preincrement
	chainNode<T> *p = originalNode;
	if(p == node) return *this;
	while(p->next != node) p = p->next;
	node = p;
	return *this;
}
template <class T>
typename chain<T>::iteratorRan chain<T>::iteratorRan::operator--(int){ // postincrement
	iteratorRan old = *this;
	chainNode<T> *p = originalNode;
	if(p == node) return old;
	while(p->next != node) p = p->next;
	old.node = p;
	return old;
}

template <class T>
typename chain<T>::iteratorRan& chain<T>::iteratorRan::operator+=(const int dist){
	chainNode<T> *p;
	p = node;
	for(int i = 0; i < dist; ++i) p = p->next;
	node = p;
	return *this;
}
template <class T>
typename chain<T>::iteratorRan& chain<T>::iteratorRan::operator-=(const int dist){
	chainNode<T> *p;
	p = originalNode;
	int index = this->getIndex();
	index -= dist;
	p = originalNode;
	for(int i = 0; i < index; i++) p =p->next;
	node = p;
	return *this;;
}
template <class T>
typename chain<T>::iteratorRan chain<T>::iteratorRan::operator+(const int dist){
	typename chain<T>::iteratorRan temp = *this;
	chainNode<T> *p = node;
	for(int i = 0; i < dist;i++) p =p->next;
	temp.node = p;
	return temp;
}
template <class T>
typename chain<T>::iteratorRan chain<T>::iteratorRan::operator-(const int dist){
	typename chain<T>::iteratorRan temp = *this;
	chainNode<T> *p = originalNode;
	int index = this->getIndex();
	index -= dist;
	p = originalNode;
	for(int i = 0; i < index; i++) p =p->next;
	temp.node = p;
	return temp;
}

/*
//两个指针相差的距离（单位：数据元素）
template <class T>
typename std::iterator<std::random_access_iterator_tag,T>::difference_type chain<T>::iteratorRan::operator-(const  iteratorRan right)const{
	return this->getIndex() - right.getIndex();
}
*/


//两个指针相差的距离（单位：数据元素）
template <class T>
typename chain<T>::iteratorRan::difference_type chain<T>::iteratorRan::operator-(const  iteratorRan right)const{
	return this->getIndex() - right.getIndex();
}
