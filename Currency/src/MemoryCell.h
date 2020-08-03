/*
 * MemoryCell.h
 *
 *  Created on: 2017年2月12日
 *      Author: lsn
 */

#ifndef MEMORYCELL_H_
#define MEMORYCELL_H_

template<class T>
class MemoryCell {
public:
	public:
	explicit MemoryCell(const T& initialValue = T());
	virtual ~MemoryCell(){}
	const T& read() const;
	void write(const T& x);
private:
	T storedValue;
};

#endif /* MEMORYCELL_H_ */
