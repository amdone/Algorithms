/*
 * stack.cpp
 *
 *  Created on: 2017年4月11日
 *      Author: lsn
 */

#include "stackNew.h"
template<typename T>
stackNew<T>::stackNew(int theCapacity) {
	front = -1;
	capacity = theCapacity;
	//malloc只是返回一片连续的空间，但没有创建对象
	element = (T *) std::malloc(sizeof(T)*capacity);
}

template<typename T>
stackNew<T>::~stackNew() {
	for(int i = 0; i <=front; i++){
		element[i].~T();//对栈中的每个数据元素，调用它的析构函数
	}
	std::free(element);//释放空间
}


template<typename T>
void stackNew<T>::push(T& theElement) {
	if(front == capacity - 1)
		throw std::out_of_range("stack is full");
	++front;
	//newplacement（下面的new) 调用T的复制构造函数，
	//在指定的位置(element+front),创造T的1个对象，这个对象等于theElement
	//T必须提供复制构造函数
	new(element + front) T(theElement);
}

template<typename T>
void stackNew<T>::pop() {
	if(-1 == front)
		throw std::out_of_range("stack is empty");
	element[front].~T();
	--front;
}


template<typename T>
T& stackNew<T>::top() {
	if(-1 == front)
		throw std::out_of_range("stack is empty");
	return element[front];
}

template<class T>
void stackNew<T>::output(std::ostream& out) const{
	std::copy(element,element + front + 1, std::ostream_iterator<T>(out, "  "));
	out<<std::endl;
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const stackNew<T>& x){
	x.output(out);
	return out;
}

