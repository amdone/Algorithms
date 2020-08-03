//============================================================================
// Name        : circularLinearList.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "circularChain.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>


template<class T>
chain<T>::chain(int initialCapacity)
{
   if (initialCapacity < 1)
     throw std::invalid_argument("Initial capacity = " + std::to_string(initialCapacity) + " Must be > 0");
   firstNode = new chainNode<T>();
   firstNode->next = firstNode;
   listSize = 0;
}


template<class T>
chain<T>::chain(const chain& theList)
{
	//构造头结点
	firstNode = new chainNode<T>();
	firstNode->next = firstNode;
	listSize = theList.listSize;
	//原链表大小为空不用复制
	if(listSize == 0) return;

	chainNode<T> *q = firstNode;
	chainNode<T> *p = theList.firstNode;
	while(p->next != theList.firstNode){
		p = p->next;
		q->next = new chainNode<T>(p->element,NULL);
		q = q->next;
	}
	q->next = firstNode;
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
	if(theIndex < 0 || theIndex >=listSize){
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
   int index = 0;
   while (currentNode != firstNode && currentNode->element != theElement){
     currentNode = currentNode->next;
      index++;
   }
  if (currentNode == firstNode)
      return -1;
   else
      return index;
}



template<class T>
void chain<T>::insert(int theIndex, const T& theElement){
	if (theIndex != listSize)
	checkIndex(theIndex);
    chainNode<T>* p = firstNode;
    for (int i = 0; i < theIndex; ++i) p = p->next;
    p->next = new chainNode<T>(theElement, p->next);

   ++listSize;
}

template<class T>
void chain<T>::erase(int theIndex){
	checkIndex(theIndex);
	chainNode<T>* deleteNode;
	chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex; ++i) p = p->next;

      deleteNode = p->next;
      p->next = p->next->next;

   --listSize;
   delete deleteNode;
}

template<class T>
void chain<T>::reverse(){
	   chainNode<T> *q, *p, *head;
	   q = firstNode->next->next;
	   p = firstNode->next;
	   head = firstNode->next;
	    while (q != firstNode)
	    {
	    	chainNode<T> *temp = q->next;
	        q->next = p;
	        p = q;
	        if (temp == firstNode)
	        {
	            firstNode->next = p;
	        }
	        q = temp;
	    }
	    head->next = firstNode;

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

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x){
	x.output(out);
	return out;
}





