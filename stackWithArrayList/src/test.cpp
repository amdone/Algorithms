/*
 * test.cpp
 *
 *  Created on: 2019年4月6日
 *      Author: Eichi
 */
#include <iostream>
#include <vector>
#include "stackWithArrayList.cpp"

using std::cout;
using std::endl;



int main(){

	stackWithArrayList<int> q(2);
	cout<<"q is null ?"<<endl;
	cout<<(q.empty()?"yes":"no")<<endl;
	q.push(5);
	q.push(6);
	q.push(7);
	q.push(7);

	cout<<"the size of q is: "<<q.size()<<endl;

	q.pop();
	cout<<"once pop:"<<endl;
	cout<<"the size of q is: "<<q.size()<<endl;
	cout<<q<<endl;
	q.~stackWithArrayList();
	cout<<"q is null ?"<<endl;
	cout<<(q.empty()?"yes":"no")<<endl;
	cout<<q;

	//cout<<"Ok"<<endl;


	return 0;
}



