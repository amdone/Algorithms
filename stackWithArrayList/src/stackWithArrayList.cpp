/*
 * stackWithArrayList.cpp
 *
 *  Created on: 2019年4月6日
 *      Author: Eichi
 */


#include "stackWithArrayList.h"

template<typename T>
stackWithArrayList<T>:: stackWithArrayList(int initialCapacity){
	if(initialCapacity < 1)
		throw std::invalid_argument("initialCapacity < 1");
	arrayList<T> list(initialCapacity);
}


template<typename T>
stackWithArrayList<T>:: ~stackWithArrayList(){
		for(int i=list.size()-1; i>=0; i--)
			list.erase(i);
}

template<typename T>
T& stackWithArrayList<T>:: top()const{
	  if (list.empty())
		  throw std::out_of_range("stack is null");
	  return list.get(list.size()-1);;
}


template<typename T>
void stackWithArrayList<T>::pop(){
	  if(list.empty())
		  throw std::out_of_range("stack is null");
	  list.erase(list.size()-1);
}

template<typename T>
void stackWithArrayList<T>:: push(const T& theElement){
	list.insert(list.size(),theElement);
}

template<class T>
void stackWithArrayList<T>::output(std::ostream& out) const{
	list.output(out);
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const stackWithArrayList<T>& x){
	x.output(out);
	return out;
}


