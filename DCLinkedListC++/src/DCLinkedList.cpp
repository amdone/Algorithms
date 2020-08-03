//============================================================================
// Name        : DCLinkedList.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "DCLinkedList.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>


template<class T>
chain<T>::chain(int initialCapacity){
	   if (initialCapacity < 1)
	     throw std::invalid_argument("Initial capacity = " + std::to_string(initialCapacity) + " Must be > 0");
	   firstNode = new chainNode<T>();
	   firstNode->next = firstNode;
	   firstNode->pre = firstNode;
	   listSize = 0;
}

template<class T>
chain<T>::~chain()
{
	if(firstNode->next == firstNode) delete firstNode;		//删除头节点
	else{
		chainNode<T>* tmp = firstNode;
		   while (firstNode->next != tmp)
		   {// delete firstNode
		      chainNode<T>* nextNode = firstNode->next;
		      delete firstNode;
		      firstNode = nextNode;
		   }
	}
}


template<class T>
void chain<T>::checkIndex(int theIndex) const{
	if(theIndex < 0 || theIndex > listSize-1){
		throw std::out_of_range("index = " + std::to_string(theIndex) + " size = " + std::to_string(listSize)); //C++11标准引入的
	}
}


template<class T>
T& chain<T>::get(int theIndex) const
{
   checkIndex(theIndex);
   chainNode<T>* currentNode = firstNode->next;
   for (int i = 0; i < theIndex; i++)currentNode = currentNode->next;

   return currentNode->element;
}



template<class T>
int chain<T>::indexOf(const T& theElement) const{
	chainNode<T>* currentNode = firstNode->next;
	firstNode->element = theElement;
	int index = 0;
	while(currentNode->element != theElement){
		if(firstNode == currentNode->next)
			return -1;
		currentNode = currentNode->next;
		index++;
	}
	return index;

}


template<class T>
void chain<T>::insert(int theIndex, const T& theElement){
	if (theIndex != listSize)
	checkIndex(theIndex);
    chainNode<T>* p = firstNode;
    for (int i = 0; i < theIndex; ++i) p = p->next;
    p->next = new chainNode<T>(theElement, p->next,p);
    p->next->next->pre = p->next;
    ++listSize;
}

template<class T>
void chain<T>::update(int theIndex, const T& theElement){
	if (theIndex != listSize)
	checkIndex(theIndex);
    chainNode<T>* p = firstNode;
    for (int i = 0; i <= theIndex; ++i) p = p->next;
    p->element = theElement;

}


template<class T>
void chain<T>::erase(int theIndex){
	checkIndex(theIndex);
	chainNode<T>* deleteNode;
	chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex; ++i) p = p->next;

      deleteNode = p->next;
      p->next = p->next->next;
      p->next->pre = p;

   --listSize;
   delete deleteNode;
}

template<class T>
void chain<T>::reverse(){

	chainNode<T>* p = firstNode;
	chainNode<T>* q = firstNode->pre;
	chainNode<T>* r = q;
	for(int i = 0;i<(listSize+1)/2;i++){
		T tmp = p->element;
		p->element = q->element;
		q->element = tmp;
		p = p->next;
		q = q->pre;
	}
	firstNode = r;
}


template<class T>
void chain<T>::output(std::ostream& out) const
{
   chainNode<T> *p = firstNode->next;
   out <<std::endl;
   while(p != firstNode){
	   out << p->element <<" ";
	   p = p->next;
   }
   out << std::endl;
}

template<class T>
void chain<T>::preOutput(std::ostream& out) const
{
   chainNode<T> *p = firstNode->pre;
   out <<std::endl;
   while(p != firstNode){
	   out << p->element <<" ";
	   p = p->pre;
   }
   out << std::endl;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x){
	x.output(out);
	return out;
}
