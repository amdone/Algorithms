//============================================================================
// Name        : SSTF.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <cstdio>
#include <iostream>
using namespace std;



void SSTF(int n,int postion,int &sum,int arr[],int outArr[]){
	int p = postion;
	int index = 0;
	//int sum=0;
	int lastp = postion;
	int min ;
	for(int i=0;i<n;i++){

		min = arr[0];
		index = 0;
		lastp = p;
		for(int j = 0;j < n;j++){
			if(arr[j] > 0){
				if(abs(arr[index]-p) > abs(arr[j]-p)){
					index = j;
					min = arr[j];
				}
			}

		}
		outArr[i] = p = arr[index];
		sum += abs(lastp-p);
		arr[index] = -9999;
	}
}
int main() {

	int n = 8;
	int sum = 0;
	int arr[8] = {98,183,37,122,14,124,65,67};
	int postion = 53;
	int outArr[8] = {};
	SSTF(n,postion,sum,arr,outArr);
	for(int i:outArr){
		cout<<i<<" ";
	}
//	for(int i = 0;i< n;i++){
//		cout<<outArr[i]<<" ";
//	}
	cout<<"\n平均寻道时间："<<sum*1.0 / n<<endl;
	return 0;
}
