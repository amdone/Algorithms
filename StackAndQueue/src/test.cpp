/*
 * stack.cpp
 *
 *  Created on: 2017年3月26日
 *      Author: lsn
 */
/*
//测试以下的stack实现
#include "arrayStack.cpp"
#include "linkedStack.cpp"

template class arrayStack<int>;
template class linkedStack<int>;

using std::cout;
using std::endl;
int main(){

	arrayStack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);


	cout << s<<endl;

	s.pop();
	s.pop();
	cout<<s<<endl;
	cout << s.top()<<endl;


	linkedStack<int> sl;

	sl.push(1);
	sl.push(2);
	sl.push(3);
	sl.push(4);
	sl.push(5);


	cout << sl<<endl;

	sl.pop();
	sl.pop();
	cout<<sl<<endl;
	cout << sl.top()<<endl;

	return 0;
}
*/
//测试satckNew
#include <iostream>
#include <vector>
#include "arrayQueue.cpp"
#include "stackNew.cpp"
using std::cout;
using std::endl;


template class stackNew<arrayQueue<int > >;
template class arrayQueue<int >;
int main(){

	arrayQueue<int> q;
	q.push(5);
	q.push(6);
	q.push(7);
	q.push(7);
	//q.push(7);//默认5个数据的空间，但循环队列有1个数据空间不能用，最多入队4个数据


	stackNew<arrayQueue<int > > s;
	s.push(q);
	s.push(q);
	//s.pop();
	//s.pop();

	cout<<s;

	//cout<<"Ok"<<endl;


	return 0;
}
