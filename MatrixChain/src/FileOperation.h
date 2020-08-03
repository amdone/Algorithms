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

void createData(int size, int low, int high) {
	RandomNumber rn(0);
	ofstream fout("input.txt");
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE READING FILE..." << std::endl;
		exit(1);
	}
	for (int i = 0, temp; i < size; i++) {
		temp = rn.Random(high);
		if (temp < low)
			--i;
		else
			fout << temp << std::endl;
	}
	std::cout << "create data("<<size<<" Matrixes) success!" << std::endl;
	fout.close();
}

void readData(int arr[], int size) {
	ifstream fin("input.txt");
	if (!fin.is_open()) {
		std::cerr << "ERROR WHILE READING FILE..." << std::endl;
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		fin >> arr[i];
	}
	std::cout << "read data success!" << std::endl;
	fin.close();
}



void writeData(const string strRes, const int sum, const string fileName) {
	ofstream fout(fileName);
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE OPENING FILE..." << std::endl;
		exit(1);
	}
	fout<<"The times of multiplication is :"<<sum<<endl;
	fout<<"The best order of multiplication is:"<<strRes<<endl;
	std::cout << fileName << " write success!" << std::endl;
	fout.close();
}

#endif /* FILEOPERATION_H_ */
