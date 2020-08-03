/*
 * stackWithArrayList.h
 *
 *  Created on: 2019年4月6日
 *      Author: Eichi
 */

#ifndef STACKWITHARRAYLIST_H_
#define STACKWITHARRAYLIST_H_

#include "stack.h"
#include "arrayList.cpp"

template<typename T>
class stackWithArrayList : public stack<T>{
public:
	stackWithArrayList(int initialCapacity);
	~stackWithArrayList();
    bool empty() const {return list.empty();};
    int size() const {return list.size();};
    T& top()const;
    void pop();
    void push(const T& theElement);
    void output(std::ostream& out)const;
private:
	arrayList<T> list;
};


#endif /* STACKWITHARRAYLIST_H_ */
