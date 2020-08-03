//============================================================================
// Name        : mixedIndex.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int blockSize = 32;
int blockNumberSize = 2;
int maxBlockNumber = blockSize/blockNumberSize;
int X,Y,Z;

int block[13];

void blockInit(){
	for(int i=0;i<10;i++){
		block[i] = blockSize;
	}
	block[10] = blockSize * maxBlockNumber;
	block[11] = blockSize * maxBlockNumber * maxBlockNumber;
	block[12] = blockSize * maxBlockNumber * maxBlockNumber * maxBlockNumber;
}

void allocation(int fileSize){
	if(fileSize == 0){
		cout<<"�ļ���СΪ0\n";
	}
	else if(fileSize <= blockSize * 10){
		cout<<"���ļ�������ֱ��������\nռ����ǰ";
		cout<<(fileSize -1) / blockSize + 1<<"��\n";
		cout<<"����ƫ�ƣ�"<<(fileSize%blockSize ? fileSize%blockSize :blockSize)<<"\n";
	}
	else if(fileSize <= blockSize * 10 + block[10]){
		X = (fileSize -1 - (blockSize * 10)) / blockSize + 1;
		cout<<"���ļ�������ֱ��������һ��������\nռ����ֱ��������һ��������ǰ";
		cout<<X<<"��\n";
		cout<<"����ƫ�ƣ�"<<(fileSize%blockSize ? fileSize%blockSize :blockSize)<<"\n";
	}
	else if(fileSize <= blockSize * 10 + block[10] + block[11]){
		X = 16;
		Y = (fileSize - 1 - (blockSize * 10) - block[10]) / block[10] + 1;
		cout<<"���ļ�������ֱ��������һ��������������\nռ����ֱ��������һ�������Ͷ���������ǰ";
		cout<<Y<<"��\n";
		cout<<"����ƫ�ƣ�"<<(fileSize%blockSize ? fileSize%blockSize :blockSize)<<"\n";
	}
	else if(fileSize <= blockSize * 10 + block[10] + block[11] + block[12]){
		X = 16;
		Y = 16;
		Z = (fileSize -1 - (blockSize * 10) - block[10] - block[11]) / block[11] + 1;
		cout<<"���ļ�������ֱ��������һ��������������������\nռ����ֱ��������һ������������������������ǰ";
		cout<<Z<<"��\n";
		cout<<"����ƫ�ƣ�"<<(fileSize%blockSize ? fileSize%blockSize :blockSize)<<"\n";
	}
	else{
		cout<<"�ļ�̫���޷����䣡";
	}

}

void search(int address){
	if(address <= blockSize * 10){
		cout<<"�õ�ַ�̿��Ϊ��"<<address/blockSize<<endl;
	}
	else if(address <= blockSize * 10 + block[10]){
		cout<<"�õ�ַ�̿��Ϊ��"<<9+(address - (blockSize * 10))/blockSize<<endl;
	}
	else if(address <= blockSize * 10 + block[10] + block[11]){
		cout<<"�õ�ַ�̿��Ϊ��"<<(9 + maxBlockNumber + ((address -1 - (blockSize * 10) - block[10])) / blockSize) +1<<endl;

	}
	else if(address <= blockSize * 10 + block[10] + block[11] + block[12]){
		cout<<"�õ�ַ�̿��Ϊ��"<<9 + maxBlockNumber + maxBlockNumber*maxBlockNumber + ((address -1 - (blockSize * 10) - block[10] - block[11]) / blockSize)<<endl;

	}
	else{
		cout<<"������Χ��";
	}
}

int main() {
	blockInit();
	int i;
//	allocation(9025);
//	search(33);
//	search(256);
//	search(9024);
//	search(9066);
	while(1){
		cout<<"1.���� 2.���̿��"<<endl;
		cin>>i;
		if(i==1){
			int filesize;
			cout<<"�����ļ���С��"<<endl;
			cin>>filesize;
			allocation(filesize);
		}
		else if(i==2){
			int add;
			cout<<"�����ַ��"<<endl;
			cin>>add;
			search(add);
		}
		else{
			cout<<"�������"<<endl;
		}
	}

	return 0;
}
