#include <iostream>
#include <time.h>
#include "FileOperation.h"
using namespace std;

string LCS(string str1, string str2) {
	int str1Size = str1.size();
	int str2Size = str2.size();
	int c[str1Size][str2Size] = {};
	for (int i = 1; i < str1Size; i++) {
		c[i][0] = 0;
	}
	for (int i = 0; i <str2Size; i++) {
		c[0][i] = 0;
	}
	for (int i = 1; i < str1Size; i++) {
		for (int j = 1; j < str2Size; j++) {
			if (str1[i] == str2[j]) {
				c[i][j] = c[i-1][j-1] + 1;
			} else if (c[i-1][j] >= c[i][j-1]) {
				c[i][j] = c[i-1][j];
			} else {
				c[i][j] = c[i][j-1];
			}
		}
	}

	int i = str1Size -1;
	int j = str2Size -1;
	string strLcs = "";
	while (i >= 0 && j >= 0) {
		if (str1[i] == str2[j]) {
			strLcs += str1[i];
			--i;
			--j;
		} else {
			if (c[i][j - 1] > c[i - 1][j]) {
				--j;
			} else {
				--i;
			}
		}
	}
	string result(strLcs.rbegin(), strLcs.rend());
	return result;
}

int main() {
	int startTime,endTime;
	createData(300,50);
	string s1, s2;
	readData(s1,s2);
	cout<<"Start LCS process...\n";
	startTime = clock();
	string lcs = LCS(s1,s2);
	endTime = clock();
	cout << "The LCS is:" << lcs<<endl;
	cout<<"time cost:"<<endTime-startTime<<"ms"<<endl;
	writeData(lcs,"output.txt");
	cin>>s1;
	return 0;
}
