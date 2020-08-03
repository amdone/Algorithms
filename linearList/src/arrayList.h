/*
 * arrayList.h
 *
 *  Created on: 2017年3月19日
 *      Author: lsn
 */

#ifndef SRC_ARRAYLIST_H_
#define SRC_ARRAYLIST_H_
#include "linearList.h"
#include "chain.h"
template <typename T>
class arrayList :public linearList<T> {
public:

		//构造函数，还可能被做为类型转换，即将int转换为arrayList；加上explicit就不会被作为类型转换函数。
	    //这个函数也能成为缺省构造函数，很多场合需要缺省构造函数，例如 new T[]
		explicit arrayList(int initialCapacity = 10);

		~arrayList(){delete [] element;}//delete会对element中的每个对象，调用析构函数~T(),然后释放存储空间

		//对于成员变量使用了new分配空间的类，应该提供以下的两个函数，否则，会出错。
		arrayList(const arrayList&);//复制构造函数
		arrayList<T>& operator=(const arrayList<T>& rhs);//赋值操作
		arrayList<T>& operator=(const chain<T>& rhs);

		bool empty() const {return listSize == 0;}
		int size() const {return listSize;}
		T& get(int theIndex) const;
		int indexOf(const T& theElement) const;
		void erase(int theIndex);
		void insert(int theIndex, const T& theElement);
		void output(std::ostream& out) const;
		int capacity() const {return arrayLength;}

		void changeLength1D(T* & source, int oldLength, int newLength);

		void copy(const T* start, const T* end, T* target)const;
		void copy_backward(const T * start, const T* end, T* tartget)const;
		const T * find( const T* start, const T* end, const T &theElement) const;


		//以下的函数只是为了让编译通过（使用arrayList嵌套arrayList时）
		//函数逻辑肯定不对，应该使用书上题目要求的operator==
		bool operator==(arrayList const &rhs){
			return(this == &rhs);
		}




		typedef T* iterator;//对于连续存储的数据结构，指针就是迭代器，STL中的iterator_traits有部分特化支持。

		iterator begin() const{return element;}
		iterator end() const {return element + listSize;}

		//双向迭代器和随机迭代器可以定义reverse_iterator类模版生成与iterator绑定的reverse迭代器
		typedef std::reverse_iterator<T*> reverse_iterator;
		reverse_iterator rbegin() const{return reverse_iterator(element + listSize);}
		reverse_iterator rend() const {return reverse_iterator(element);}


protected:
			void checkIndex(int theIndex) const;
			T* element;//存储线性表的一维数组
			int arrayLength;//  容量
			int listSize;//线性表的元素个数
};

#endif /* SRC_ARRAYLIST_H_ */
