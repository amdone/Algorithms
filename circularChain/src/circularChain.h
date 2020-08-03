/*
 * circularChain.h
 *
 *  Created on: 2019Äê3ÔÂ22ÈÕ
 *      Author: Eichi
 */

#ifndef CIRCULARCHAIN_H_
#define CIRCULARCHAIN_H_

#include "linearList.h"
template <typename T>
struct chainNode
{
   T element;
   chainNode<T> *next;

   chainNode() {next = NULL;}
   chainNode(const T& element) :element(element){
	   next = NULL;
   }

   chainNode(const T& element, chainNode* next):element(element)
   {
	   this->next = next;
   }

};


template<class T>
class chain : public linearList<T>
{
   public:
      chain(int initialCapacity = 10);
      chain(const chain&);
      ~chain();
     bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      void erase(int theIndex);
      void reverse();
      void insert(int theIndex, const T& theElement);
      void output(std::ostream& out) const;

	  int capacity() const {return 0;}

	  class iterator;
	  iterator begin() const{return iterator(firstNode->next);}
	  iterator end() const{return iterator(firstNode);}



   	  protected:
      void checkIndex(int theIndex) const;
      chainNode<T>* firstNode;
      int listSize;

   public:

      class iterator :public std::iterator<std::forward_iterator_tag,T>{

          public:
                 iterator(chainNode<T>* theNode = NULL)
                    {
                	 node = theNode;
                    }

                  T& operator*() const {return node->element;}
                  T* operator->() const {return &node->element;}


                  bool operator!=(const iterator right) const
                        {return node != right.node;}
                  bool operator==(const iterator right) const
                        {return node == right.node;}

                  iterator& operator++()   //
                            {node = node->next; return *this;}
                  iterator operator++(int) //
                  	      {iterator old = *this;
                  	       node = node->next;
                  	       return old;
                  	      }

             protected:
                chainNode<T>* node;
          };
};
#endif /* CIRCULARCHAIN_H_ */
