/*
 * linearList.h
 *
 *  Created on: 2017年3月19日
 *      Author: lsn
 */

#ifndef SRC_LINEARLIST_H_
#define SRC_LINEARLIST_H_
#include <iostream>

template <typename T>
class linearList {
public:
	virtual ~linearList(){};//需要定义
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int theIndex) const = 0;
	virtual int indexOf(const T& theElement) const = 0;
	virtual void erase(int theIndex) = 0;
	virtual void insert(int theIndex, const T& theElement) = 0;
	virtual void output(std::ostream& out) const = 0;
};

#endif /* SRC_LINEARLIST_H_ */
