/*
 * FileOperation.h
 *
 * 该头文件用于文件的各类操作
 */

#ifndef FILEOPERATION_H_
#define FILEOPERATION_H_

#include <fstream>
#include <stdlib.h>
#include "RandomNumber.h"

void createData(int length, int range) {
	RandomNumber rn(0);
	ofstream fout("input.txt");
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE READING FILE..." << std::endl;
		exit(1);
	}
	//string 1
	int randomRange = (rn.Random(1) ? rn.Random(range) : 0 - rn.Random(range));
	int randomLength = (int) (length * (randomRange + 100) / 100.0);
	for (int i = 0; i < randomLength; i++) {
		fout << (char) ('A' + rn.Random(26));
	}
	fout << endl;
	//string 2
	randomRange = (rn.Random(1) ? rn.Random(range) : 0 - rn.Random(range));
	randomLength = (int) length * (randomRange + 100) / 100.0;
	for (int i = 0; i < randomLength; i++) {
		fout << (char) ('A' + rn.Random(26));
	}
	std::cout << "create data(length ~= " << length << "*(+-)" << range
			<< "%)success!" << std::endl;
	fout.close();
}

void readData(string &str1, string &str2) {
	ifstream fin("input.txt");
	if (!fin.is_open()) {
		std::cerr << "ERROR WHILE READING FILE..." << std::endl;
		exit(1);
	}
	getline(fin, str1);
	getline(fin, str2);
	std::cout << "read data success!" << std::endl;
	fin.close();
}

void writeData(const int distance, const string fileName) {
	ofstream fout(fileName);
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE OPENING FILE..." << std::endl;
		exit(1);
	}
	fout << "The d(A,B) is:"<<distance << endl;
	std::cout << fileName << " write success!" << std::endl;
	fout.close();
}

#endif /* FILEOPERATION_H_ */
