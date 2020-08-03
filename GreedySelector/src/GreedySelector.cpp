//============================================================================
// Name        : GreedySelector.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;

#define NUM 11

int si[NUM] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };          //存储活动开始时间
int fi[NUM] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };		//存储活动结束时间
bool b[NUM];  //存储被安排的活动编号

void writeData(const int size, const bool b[], const string fileName) {
	ofstream fout(fileName);
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE OPENING FILE..." << std::endl;
		exit(1);
	}
	fout<<"The best sequence of activities is:"<<endl;
	for (int i = 0; i < size; i++){
		if (b[i])
			fout<< i+1 <<" ";
	}
	fout<<endl;
	fout.close();
}

void GreedySelector(int n, int si[], int fi[], bool b[]) {
	b[0] = true;
	int j = 0;

	for (int i = 1; i < n; i++) {
		if (si[i] >= fi[j]) {
			b[i] = true;
			j = i;
		} else
			b[i] = false;
	}
}

int main() {

	int n = NUM;
	GreedySelector(n, si, fi, b);
	cout << "The best sequence of activities is:" << endl;
	for (int i = 0; i <= n; i++) {
		if (b[i])
			cout << i+1 << ":" << "(" << si[i] << "," << fi[i] << ")" << endl;
	}
	writeData(n,b,"output1.txt");
	return 0;
}
