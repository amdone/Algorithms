/*
 * test.cpp
 *
 *  Created on: 2019Äê7ÔÂ14ÈÕ
 *      Author: amdoing
 */

#include "BTree.cpp"
using std::cout;
using std::endl;
using std::cin;

int main(){

	cout<<"Test Start!"<<endl;
		BTree<int,char> a(5);
		//a.print();

		a.insert(std::pair<int,char>(1,'x'));
		a.insert(std::pair<int,char>(2,'x'));
		a.insert(std::pair<int,char>(6,'x'));
		a.insert(std::pair<int,char>(7,'x'));
		a.insert(std::pair<int,char>(11,'x'));
		a.insert(std::pair<int,char>(4,'x'));
		a.insert(std::pair<int,char>(8,'x'));
		a.insert(std::pair<int,char>(13,'x'));
		a.insert(std::pair<int,char>(10,'x'));
		a.insert(std::pair<int,char>(5,'x'));
		a.insert(std::pair<int,char>(17,'x'));
		a.insert(std::pair<int,char>(9,'x'));
		a.insert(std::pair<int,char>(16,'x'));
		a.insert(std::pair<int,char>(20,'x'));
		a.insert(std::pair<int,char>(3,'x'));
		a.insert(std::pair<int,char>(12,'x'));
		a.insert(std::pair<int,char>(14,'x'));
		a.insert(std::pair<int,char>(18,'x'));
		a.insert(std::pair<int,char>(19,'x'));
		a.insert(std::pair<int,char>(15,'x'));
//
//
		a.print();

		 return 0;
}
