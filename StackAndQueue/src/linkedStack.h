/*
 * linkedStack.h
 *
 *  Created on: 2017年3月26日
 *      Author: lsn
 */

#ifndef LINKEDSTACK_H_
#define LINKEDSTACK_H_

#include "stack.h"
template <typename T>
struct chainNode
{
   T element;
   chainNode *next;//可以将chainNode<T>简写为chainNode，因为这是在class chainNode的作用域内

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


template<typename T>
class linkedStack : public stack<T>
{
   public:
      linkedStack(int initialCapacity = 10) {stackTop = NULL; stackSize = 0;};
      ~linkedStack();
      bool empty() const {return stackSize == 0;};
      int size() const {return stackSize;};
      T& top() const{
    	  if(0 == stackSize )
    		  throw std::out_of_range("stackSize is 0");
    	  return stackTop->element;
      }
      void pop();
      void push(const T& theElement);
      void output(std::ostream& out)const;
      class iterator;
	  iterator begin() const {return iterator(stackTop);}
	  iterator end() const {return iterator(NULL);}

    private:
      chainNode<T>* stackTop;  // pointer to stack top
      int stackSize;           // number of elements in stack

    public:
       class iterator :public std::iterator<std::forward_iterator_tag,T>
          {

          public:
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
#endif /* LINKEDSTACK_H_ */
