//============================================================================
// Name        : FindMaxSubArray.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "FileOperation.h"
using namespace std;

#define MAX_SIZE 900000

int arr[MAX_SIZE];

int* FindMaxSubArr(int* Arr, int n) {
	int MSALeft = 0;
	int MSARight = 0;
	int MSALength = 0;
	int temp = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			temp += Arr[j];
			if (temp > MSALength) {
				MSALength = temp;
				MSALeft = i;
				MSARight = j;
			}
		}
		temp = 0;
	}
	int res[3] = { MSALeft, MSARight, MSALength };
	int *p2res = res;
	return p2res;
}

int* FindMaxCrossSubArray(int arr[], int low, int mid, int high) {
	int leftSum = -999999, rightSum = -999999;
	int res[3];
	for (int i = mid, sum = 0; i >= low; i--) {
		sum += arr[i];
		if (sum > leftSum) {
			leftSum = sum;
			res[0] = i;
		}
	}
	for (int i = mid + 1, sum = 0; i <= high; i++) {
		sum += arr[i];
		if (sum > rightSum) {
			rightSum = sum;
			res[1] = i;
		}
	}
	res[2] = leftSum + rightSum;
	int *p = res;
	return p;
}

int* FindMaxSubArray(int arr[], int low, int high) {
	if (low == high) {
		int res[3] = { low, high, arr[low] };
		int *p2res = res;
		return p2res;
	} else {
		int mid = (low + high) / 2;
		int *left = FindMaxSubArray(arr, low, mid);
		int *right = FindMaxSubArray(arr, mid + 1, high);
		int *cross = FindMaxCrossSubArray(arr, low, mid, high);
		if (left[2] >= right[2] && left[2] >= cross[2]) {
			return left;
		} else if (left[2] <= right[2] && cross[2] <= right[2]) {
			return right;
		} else {
			return cross;
		}
	}
}


int main() {
	int startTime, endTime;
	createData(MAX_SIZE);
	readData(arr, MAX_SIZE);
	startTime = clock();
	int *result = FindMaxSubArray(arr, 0, MAX_SIZE - 1);
	int begin = *result;
	int end = *(result + 1);
	int sum = *(result + 2);
	endTime = clock();
	//writeData(arr,begin,end,sum,endTime-startTime,"output.txt");
	cout << "The MaxSubArray is:[" << begin << "," << end
			<< "]\nThe sum of MaxSubArray is:" << sum << endl;
	cout << "Time cost:" << endTime - startTime << "ms" << endl;
	return 0;
}
