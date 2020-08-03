/*
 * FileOperation.h
 *
 *  Created on: 2020Äê5ÔÂ28ÈÕ
 *      Author: Eichi
 */

#ifndef FILEOPERATION_H_
#define FILEOPERATION_H_

#include <time.h>
#include <fstream>
#include <stdlib.h>
#include "RandomNumber.h"

void createData(int size,  int high) {
	RandomNumber rn(0);
	ofstream fout("input.txt");
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE READING FILE..." << std::endl;
		exit(1);
	}
	//fout << size << std::endl;
	int arr[size],temp;
	int i = 0;
	for (; i < size; i++) {
		arr[i]=rn.Random(high-1);
		fout << arr[i] << std::endl;
	}
	i=0;
	while(i<size){
		temp=rn.Random(high);
		if(temp>arr[i]){
			fout << temp << std::endl;
			++i;
		}
	}
	std::cout << "create data("<<size<<") success!" << std::endl;
	fout.close();
}

void readData(int size,int si[],int fi[]) {
	ifstream fin("input.txt");
	if (!fin.is_open()) {
		std::cerr << "ERROR WHILE READING FILE..." << std::endl;
		exit(1);
	}
	int i = 0;
	for ( ;i < size; i++) {
		fin >> si[i];
	}
	for (i = 0; i < size; i++) {
		fin >> fi[i];
	}
	std::cout << "read data success!" << std::endl;
	fin.close();
}



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

#endif /* FILEOPERATION_H_ */
