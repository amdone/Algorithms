//============================================================================
// Name        : EditDistance.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include "FileOperation.h"
using namespace std;

int minDistance(string str1, string str2) {
	int str1Size = str1.size();
	int str2Size = str2.size();
	int count[str1Size][str2Size];
	for (int i = 0; i <= str1Size; i++) {
		count[i][0] = i;
	}
	for (int i = 0; i <= str2Size; i++) {
		count[0][i] = i;
	}

	for (int i = 1; i <= str1Size; i++) {
		for (int j = 1; j <= str2Size; j++) {
			int tag = 0;
			if (str1[i - 1] != str2[j - 1]) {
				tag = 1;
			}
			count[i][j] = min(count[i - 1][j] + 1, count[i][j - 1] + 1);
			count[i][j] = min(count[i][j], tag + count[i - 1][j - 1]);
		}
	}
	return count[str1Size][str2Size];
}

int main() {
	string s1, s2;
	int startTime, endTime;
	createData(300, 50);
	readData(s1, s2);
	startTime = clock();
	int d = minDistance(s1, s2);
	endTime = clock();
	cout << "The d(s1,s2) is:" << d << endl;
	cout << "time cost:" << endTime - startTime << "ms" << endl;
	writeData(d, "output.txt");
	return 0;
}
