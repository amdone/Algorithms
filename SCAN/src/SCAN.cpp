//============================================================================
// Name        : SCAN.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


void SCAN(int n,int postion,int &sum,int direction,int arr[],int outArr[]){
	int  minCount = 0, maxCount = 0, j = 0;
	int * minArr = new int[n];
	int * maxArr = new int[n];
	minArr[0] = 0;
	//maxArr[0] = 0;
	for (int i = 0; i < n; i++) {
		if (postion > arr[i]) {
			for (j = minCount - 1; j > -1; j--) {
				if (arr[i] < minArr[j]) {
					minArr[j + 1] = minArr[j];
				}
				else {
					minArr[j + 1] = arr[i];
					minCount++;
					break;
				}
			}
			if (j < 0) {
				minArr[0] = arr[i];
				minCount++;
			}
			//minArr[minCount++] = arr[i];
		}
		else {
			for (j = maxCount - 1; j > -1; j--) {
				if (arr[i] < maxArr[j]) {
					maxArr[j + 1] = maxArr[j];
				}
				else {
					maxArr[j + 1] = arr[i];
					maxCount++;
					break;
				}
			}
			if (j < 0) {
				maxArr[0] = arr[i];
				maxCount++;
			}
		}
	}
	j = 0;
	if (direction > 0) {
		for (int i = 0; i < maxCount; i++) {
			outArr[i] = maxArr[i];
		}
		for (int i = minCount; i > 0; i--) {
			outArr[maxCount + j++ ] = minArr[i-1];
		}
		sum += (maxArr[maxCount-1] - postion) + (maxArr[maxCount-1] - minArr[0]);
	}
	else {
		for (int i = minCount; i > 0; i--) {
			outArr[j++] = minArr[i-1];
		}
		for (int i = 0; i < maxCount; i++) {
			outArr[minCount + i] = maxArr[i];
		}
		if(maxCount == 0){
			sum += postion - minArr[0];
		}
		else{
			sum += (postion - minArr[0]) + (maxArr[maxCount-1] - minArr[0]);
		}
	}

	delete[] minArr;
	delete[] maxArr;
}


int main() {

	int n = 8;
	int sum = 0;
	int arr[8] = {98,183,37,122,14,124,65,67};
	int postion = 2;
	int outArr[8] = {};
	int direction = -1;
	SCAN(n,postion,sum,direction,arr,outArr);
	for(int i = 0;i< n;i++){
		cout<<outArr[i]<<" ";
	}
	cout<<"\n平均寻道时间："<<sum*1.0 / n<<endl;
	return 0;
}
