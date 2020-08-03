/*
 * test.cpp
 *
 *  Created on: 2019Äê3ÔÂ22ÈÕ
 *      Author: Eichi
 */

#include "circularChain.cpp"
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

	   cout << "Testing overloaded <<" << endl;
	   cout << y << endl;

	   int index = y.indexOf(4);
	   	   if (index < 0)
	   		   cout << "4 not found" << endl;
	   	   else
	   		   cout << "The index of 4 is " << index << endl;

	   	   index = y.indexOf(7);
	   	   if (index < 0)
	   		   cout << "7 not found" << endl;
	   	   else
	   		   cout << "The index of 7 is " << index << endl;

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

	   	   cout << "Size of y = " << y.size() << endl;
	   	   cout << "Capacity of y = " << y.capacity() << endl;
	   	   if (y.empty())
	   		   cout << "y is empty" << endl;
	   	   else
	   		   cout << "y is not empty" << endl;



		   chain<int> w(y);
		   cout << "w=y"<<endl;
		   cout << w << endl;

		   try {
			   y.insert(-3, 0);
		   }
		   catch (std::out_of_range &e)
		   {
		      cout << e.what()<< endl;
		   }

		   //insert more ,make the list is 1 2 3 4 5 6 7 8 9

		   y.insert(1,2);
		   y.insert(3,4);
		   y.insert(6,7);
		   y.insert(7,8);
		   y.insert(8,9);

		   int sum = std::accumulate(y.begin(), y.end(), 0);
		   cout << "The sum of the elements is " << sum << endl;

		   for(chain<int>::iterator i = y.begin(); i != y.end();++i)
			   cout << *i<<':';
		   cout <<endl;

		   y.reverse();
		   cout << "The reversed list is"<< endl;
		   y.output(cout);

		   cout<<"The test is over"<<endl;

}
