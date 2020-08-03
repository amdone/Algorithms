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
	//lowΪ��1�������ĵ�1��Ԫ�أ�iָ���1��Ԫ��, midΪ��1�����������1��Ԫ��
	int i = low, j = mid + 1, k = 0;  //mid+1Ϊ��2��������1��Ԫ�أ�jָ���1��Ԫ��
	int *temp = new int[high - low + 1]; //temp�����ݴ�ϲ�����������
	while (i <= mid && j <= high) {
		if (arr[i] <= arr[j]) //��С���ȴ���temp��
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}
	while (i <= mid) //���Ƚ���֮�󣬵�һ������������ʣ�࣬��ֱ�Ӹ��Ƶ�t������
		temp[k++] = arr[i++];
	while (j <= high) //ͬ��
		temp[k++] = arr[j++];
	for (i = low, k = 0; i <= high; i++, k++) //���ź���Ĵ��arr��low��high������
		arr[i] = temp[k];
	delete[] temp; //�ͷ��ڴ棬����ָ��������飬������delete []
}

void mergeSort(int arr[], int low, int high) {
	if (low >= high) {
		return;
	} // ��ֹ�ݹ�������������г���Ϊ1
	int mid = low + (high - low) / 2;  // ȡ�������м��Ԫ��
	mergeSort(arr, low, mid);  // �����ߵݹ�
	mergeSort(arr, mid + 1, high);  // ���Ұ�ߵݹ�
	merge(arr, low, mid, high);  // �ϲ�
}

void quickSort(int arr[], int left, int right) {
	if (left >= right)
		return;
	int i, j, base, temp;
	i = left, j = right;
	base = arr[left];  //ȡ����ߵ���Ϊ��׼��
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
	//��׼����λ
	arr[left] = arr[i];
	arr[i] = base;
	quickSort(arr, left, i - 1);  //�ݹ����
	quickSort(arr, i + 1, right);  //�ݹ��ұ�
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

