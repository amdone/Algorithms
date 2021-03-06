/*
 * linearList.h
 *
 *  Created on: 2019��3��22��
 *      Author: Eichi
 */

#ifndef LINEARLIST_H_
#define LINEARLIST_H_

#include <iostream>

template <typename T>
class linearList {
public:
	virtual ~linearList(){};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int theIndex) const = 0;
	virtual int indexOf(const T& theElement) const = 0;
	virtual void erase(int theIndex) = 0;
	virtual void insert(int theIndex, const T& theElement) = 0;
	virtual void output(std::ostream& out) const = 0;
};


#endif /* LINEARLIST_H_ */
