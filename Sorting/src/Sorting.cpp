//============================================================================
// Name        : Sorting.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "RandomNumber.h"
using namespace std;

#define MAX_SIZE 600000
int arr[MAX_SIZE];
int arr2[MAX_SIZE];
int arr3[MAX_SIZE];
int startTime;
int endTime;

void insertSort(int arr[], int length);
void merge(int arr[], int low, int mid, int high);
void mergeSort(int arr[], int low, int high);
void quickSort(int arr[], int left, int right);
void createData();
void readData(int arr[]);
void writeData(const int arr[], string fileName,int sortingTime);

void createData() {
	RandomNumber rn(0);
	ofstream fout("input.txt");
	if (!fout.is_open()) {
		cerr << "ERROR WHILE READING FILE..." << endl;
		exit(1);
	}
	for (int i = 0; i < MAX_SIZE; i++) {
		fout << rn.Random(MAX_SIZE) << endl;
	}
	cout << "create data success!" << endl;
	fout.close();
}

void readData(int arr[]) {
	ifstream fin("input.txt");
	if (!fin.is_open()) {
		cerr << "ERROR WHILE READING FILE..." << endl;
		exit(1);
	}
	for (int i = 0; i < MAX_SIZE; i++) {
		fin >> arr[i];
	}
	cout << "read data success!" << endl;
	fin.close();
}

void writeData(const int arr[], string fileName,int sortingTime) {
	ofstream fout(fileName);
	if (!fout.is_open()) {
		cerr << "ERROR WHILE OPENING FILE..." << endl;
		exit(1);
	}
	if(sortingTime>1000){
		fout <<"time cost of sorting:" <<sortingTime/1000.0<<"s" << endl;
	}else{
		fout <<"time cost of sorting:" <<sortingTime<<"ms" << endl;
	}
	for (int i = 0; i < MAX_SIZE; i++) {
		fout << arr[i] << endl;
	}
	cout << fileName << " write success!" << endl;
	fout.close();
}

void insertSort(int arr[], int length) {
	int temp, j;
	for (int i = 1; i < length; i++) {
		temp = arr[i];
		for (j = i; j > 0; j--) {
			if (arr[j - 1] > temp) {
				arr[j] = arr[j - 1];
			} else
				break;
		}
		arr[j] = temp;
	}
}


void merge(int arr[], int low, int mid, int high) {
	//low为第1有序区的第1个元素，i指向第1个元素, mid为第1有序区的最后1个元素
	int i = low, j = mid + 1, k = 0;  //mid+1为第2有序区第1个元素，j指向第1个元素
	int *temp = new int[high - low + 1]; //temp数组暂存合并的有序序列
	while (i <= mid && j <= high) {
		if (arr[i] <= arr[j]) //较小的先存入temp中
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}
	while (i <= mid) //若比较完之后，第一个有序区仍有剩余，则直接复制到t数组中
		temp[k++] = arr[i++];
	while (j <= high) //同上
		temp[k++] = arr[j++];
	for (i = low, k = 0; i <= high; i++, k++) //将排好序的存回arr中low到high这区间
		arr[i] = temp[k];
	delete[] temp; //释放内存，由于指向的是数组，必须用delete []
}

void mergeSort(int arr[], int low, int high) {
	if (low >= high) {
		return;
	} // 终止递归的条件，子序列长度为1
	int mid = low + (high - low) / 2;  // 取得序列中间的元素
	mergeSort(arr, low, mid);  // 对左半边递归
	mergeSort(arr, mid + 1, high);  // 对右半边递归
	merge(arr, low, mid, high);  // 合并
}

void quickSort(int arr[], int left, int right) {
	if (left >= right)
		return;
	int i, j, base, temp;
	i = left, j = right;
	base = arr[left];  //取最左边的数为基准数
	while (i < j) {
		while (arr[j] >= base && i < j)
			j--;
		while (arr[i] <= base && i < j)
			i++;
		if (i < j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//基准数归位
	arr[left] = arr[i];
	arr[i] = base;
	quickSort(arr, left, i - 1);  //递归左边
	quickSort(arr, i + 1, right);  //递归右边
}

int main() {
//	createData();
//	readData(arr);
//	copy(begin(arr), end(arr), begin(arr2));
//	copy(begin(arr), end(arr), begin(arr3));
//
//	cout<<"starting insertSort..."<<endl;
//	startTime = clock();
//	insertSort(arr,MAX_SIZE);
//	endTime = clock();
//	int timeCost1 = endTime - startTime;
//	cout<<"insertSort cost:"<<timeCost1<<"ms"<<endl;
//	writeData(arr,"insertSortReault.txt",timeCost1);
//
//	cout << "starting mergeSort..." << endl;
//	startTime = clock();
//	mergeSort(arr2, 0, MAX_SIZE - 1);
//	endTime = clock();
//	int timeCost2 = endTime - startTime;
//	cout << "mergeSort cost:" << timeCost2 << "ms" << endl;
//	writeData(arr2, "mergeSortReault.txt",timeCost2);
//
//	cout << "starting quickSort..." << endl;
//	startTime = clock();
//	quickSort(arr3, 0, MAX_SIZE - 1);
//	endTime = clock();
//	int timeCost3 = endTime - startTime;
//	cout << "quickSort cost:" << timeCost3 << "ms" << endl;
//	writeData(arr3, "quickSortReault.txt",timeCost3);
	RandomNumber rn(0);
	cout<<rn.Random(2)<<std::endl;
	cout<<rn.Random(2)<<std::endl;
	cout<<rn.Random(2)<<std::endl;
	cout<<rn.Random(2)<<std::endl;
	cout<<rn.Random(2)<<std::endl;
	return 0;
}

