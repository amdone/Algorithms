/*
 * MemoryCell.cpp
 *
 *  Created on: 2017年2月12日
 *      Author: lsn
 */

#include "MemoryCell.h"

template<class T>
MemoryCell<T>::MemoryCell(const T& initialValue)
               :storedValue(initialValue){}
template<class T>
const T& MemoryCell<T>::read() const{
	return storedValue;
}
template<class T>
void MemoryCell<T>::write(const T& x){
		storedValue=x;
}
