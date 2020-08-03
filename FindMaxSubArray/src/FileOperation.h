/*
 * FileOperation.h
 *
 *  Created on: 2020Äê5ÔÂ28ÈÕ
 *      Author: Eichi
 */

#ifndef FILEOPERATION_H_
#define FILEOPERATION_H_

#include <fstream>
#include <stdlib.h>
#include "RandomNumber.h"

void createData(int MAX_SIZE) {
	RandomNumber rn(0);
	ofstream fout("input.txt");
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE READING FILE..." << std::endl;
		exit(1);
	}
	for (int i = 0; i < MAX_SIZE; i++) {
		fout << (rn.Random(2) ? rn.Random(MAX_SIZE) : 0 - rn.Random(MAX_SIZE))
				<< std::endl;
	}
	std::cout << "create data(" << MAX_SIZE << ") success!" << std::endl;
	fout.close();
}


void readData(int arr[], int MAX_SIZE) {
	ifstream fin("input.txt");
	if (!fin.is_open()) {
		std::cerr << "ERROR WHILE READING FILE..." << std::endl;
		exit(1);
	}
	for (int i = 0; i < MAX_SIZE; i++) {
		fin >> arr[i];
	}
	std::cout << "read data success!" << std::endl;
	fin.close();
}

void writeData(const int arr[], int begin, int end,int sum,int timeCost, string fileName) {
	ofstream fout(fileName);
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE OPENING FILE..." << std::endl;
		exit(1);
	}
	if (timeCost > 1000) {
		fout << "time cost:" <<timeCost / 1000.0 << "s" << endl;
	} else {
		fout << "time cost:" << timeCost << "ms" << endl;
	}
	fout << "the sum of MaxSubArr is:" << sum<<"\nMaxSubArr:"<< endl;
	for (int i = begin; i <= end; i++) {
		fout << arr[i] << std::endl;
	}
	std::cout << fileName << " write success!" << std::endl;
	fout.close();
}

#endif /* FILEOPERATION_H_ */
