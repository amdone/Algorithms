/*
 * chain.h
 *
 *  Created on: 2019年6月8日
 *      Author: Eichi
 */

#ifndef SRC_CHAIN_H_
#define SRC_CHAIN_H_

#include "linearList.h"
template <typename T>
struct chainNode
{
   T element;
   chainNode<T> *next;//可以将chainNode<T>简写为chainNode，因为这是在class chainNode的作用域内

   chainNode() {next = NULL;}
   chainNode(const T& element){
	   this->element = element;
	   next = NULL;
   }
   chainNode(const T& element, chainNode* next)//可以将chainNode<T>简写为chainNode，因为这是在class chainNode的作用域内
   {
	   this->element = element;
	   this->next = next;
   }
};



template<class T>
class chain : public linearList<T>{
   public:
      chain(int initialCapacity = 10);
      chain(const chain&);//可以将chain<T>简写为chain，因为这是在class chain的作用域内
      ~chain();
     bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      int indexOf(std::pair<int,T> v);
      int indexOf(int &theIndex);
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void output(std::ostream& out) const;
	  int capacity() const {return 0;}//只是为了和arrayList保持一致，这个值应该很大，这里取0

	  class iterator;
	  iterator begin() const{return iterator(firstNode);}
	  iterator end() const{return iterator(NULL);}

	  class iteratorRan;
	  iteratorRan beginRan() const {return iteratorRan(firstNode,firstNode);}
	  iteratorRan endRan() const{
		  return iteratorRan(firstNode,NULL);
	  }

   protected:
      void checkIndex(int theIndex) const;
      chainNode<T>* firstNode;  // pointer to first node in chain
      int listSize;             // number of elements in list

   public:
   class iterator :public std::iterator<std::forward_iterator_tag,T>
      {//前向迭代器，这是适合单向链表实现的一种迭代器

      public:
             //采用继承STL提供的迭代器基类 iterator，就不用像书上那样定义下面的参数
	   	   	 // typedefs required by C++ for a forward iterator
             //typedef std::forward_iterator_tag iterator_category;
             //typedef T value_type;
             //typedef std::ptrdiff_t difference_type;
             //typedef T* pointer;
             //typedef T& reference;

             // constructor
             iterator(chainNode<T>* theNode = NULL)
                {node = theNode;}
             // dereferencing operators
              T& operator*() const {return node->element;}
              T* operator->() const {return &node->element;}

              // equality testing
              bool operator!=(const iterator right) const
                    {return node != right.node;}
              bool operator==(const iterator right) const
                    {return node == right.node;}
              // increment
              iterator& operator++()   // preincrement
                        {node = node->next; return *this;}
              iterator operator++(int) // postincrement
              	      {iterator old = *this;
              	       node = node->next;
              	       return old;
              	      }
         protected:
            chainNode<T>* node;
      };  // end of iterator class


};

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
{// Copy constructor.
   listSize = theList.listSize;

   if (0 == listSize)
   {// theList is empty
      firstNode = NULL;
      return;
   }
   chainNode<T>* sourceNode = theList.firstNode;
                    // node in theList to copy from
   firstNode = new chainNode<T>(sourceNode->element);
                    // copy first element of theList
   sourceNode = sourceNode->next;
   chainNode<T>* targetNode = firstNode;
                    // current last node in *this
   while (sourceNode != NULL)
   {// copy remaining elements
      targetNode->next = new chainNode<T>(sourceNode->element);
      targetNode = targetNode->next;
      sourceNode = sourceNode->next;
   }
   targetNode->next = NULL; // end the chain
}

template<class T>
chain<T>::~chain()
{// Chain destructor. Delete all nodes in chain.
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
int chain<T>::indexOf(std::pair<int,T> v){
	  chainNode<T>* currentNode = firstNode;
	   int index = 0;  // index of currentNode
	   while (currentNode != NULL && currentNode->element.first != v.first){
	     currentNode = currentNode->next;
	      index++;
	   }
	  if (currentNode == NULL)
	      return -1;
	   else
	      return index;
}
template<class T>
int chain<T>::indexOf(int &theIndex){
	  chainNode<T>* currentNode = firstNode;
	   int index = 0;  // index of currentNode
	   while (currentNode != NULL && currentNode->element.first != theIndex){
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

template<class T>
void chain<T>::output(std::ostream& out) const
{
   chainNode<T> *p = firstNode;
   if(!p){
	   out<<"NULL"<<std::endl;
	   return;
   }
   while(p != NULL){
	   out << p->element.first <<"-"<<p->element.second<<" ";
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




#endif /* SRC_CHAIN_H_ */
