/*
 * test.cpp
 *
 *  Created on: 2019Äê6ÔÂ22ÈÕ
 *      Author: Eichi
 */

#include "DCLinkedList.cpp"
#include <numeric>//accumulate
#include <algorithm>


using std::cout;
using std::endl;

int main(){
	cout<<"test start£º"<<endl;
	chain<int> y, z;
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "Size of y = " << y.size() << endl;

	if (y.empty())
	cout << "y is empty" << endl;
	else
	cout << "y is not empty" << endl;
	y.output(cout);

	cout<<"test preOutput:"<<endl;
	y.preOutput(cout);

	cout << "Testing overloaded <<" << endl;
	cout << y << endl;

	if (y.indexOf(4) < 0)
	cout << "4 not found" << endl;
	else cout << "The index of 4 is " << y.indexOf(4) << endl;

	if ( y.indexOf(7) < 0)
	cout << "7 not found" << endl;
	else cout << "The index of 7 is " << y.indexOf(7) << endl;

	// test get
	cout << "Element with index 0 is " << y.get(0) << endl;
	cout << "Element with index 3 is " << y.get(3) << endl;


	// test erase
	y.erase(1);
	cout << "Element 1 erased" << endl;
	cout << "The list is "  << y << endl;
	y.erase(2);
	cout << "Element 2 erased" << endl;
	cout << "The list is "  << y << endl;

//	//test update
//	y.update(1, 2);
//	cout << "update list[1], element is 2" << endl;
//	cout << "The list is "  << y << endl;

	cout << "Size of y = " << y.size() << endl;
	cout << "Capacity of y = " << y.capacity() << endl;
	if (y.empty())
	cout << "y is empty" << endl;
	else
	cout << "y is not empty" << endl;

	cout<<"test iterator:\n output:"<<endl;
	for(chain<int>::iterator i = y.begin(); i != y.end();++i)
	cout << *i<<':';
	cout <<endl;
	cout<<"preOutput:"<<endl;
	for(chain<int>::iterator i = y.rbegin(); i != y.rend();--i)
	cout << *i<<':';
	cout <<endl;

	cout<<"The test is over"<<endl;


}



