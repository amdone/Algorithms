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
		cout<<"文件大小为0\n";
	}
	else if(fileSize <= blockSize * 10){
		cout<<"该文件启动了直接索引：\n占用了前";
		cout<<(fileSize -1) / blockSize + 1<<"块\n";
		cout<<"块内偏移："<<(fileSize%blockSize ? fileSize%blockSize :blockSize)<<"\n";
	}
	else if(fileSize <= blockSize * 10 + block[10]){
		X = (fileSize -1 - (blockSize * 10)) / blockSize + 1;
		cout<<"该文件启动了直接索引和一级索引：\n占用了直接索引和一级索引的前";
		cout<<X<<"块\n";
		cout<<"块内偏移："<<(fileSize%blockSize ? fileSize%blockSize :blockSize)<<"\n";
	}
	else if(fileSize <= blockSize * 10 + block[10] + block[11]){
		X = 16;
		Y = (fileSize - 1 - (blockSize * 10) - block[10]) / block[10] + 1;
		cout<<"该文件启动了直接索引和一级，二级索引：\n占用了直接索引，一级索引和二级索引的前";
		cout<<Y<<"块\n";
		cout<<"块内偏移："<<(fileSize%blockSize ? fileSize%blockSize :blockSize)<<"\n";
	}
	else if(fileSize <= blockSize * 10 + block[10] + block[11] + block[12]){
		X = 16;
		Y = 16;
		Z = (fileSize -1 - (blockSize * 10) - block[10] - block[11]) / block[11] + 1;
		cout<<"该文件启动了直接索引和一级，二级，三级索引：\n占用了直接索引，一级，二级索引和三级索引的前";
		cout<<Z<<"块\n";
		cout<<"块内偏移："<<(fileSize%blockSize ? fileSize%blockSize :blockSize)<<"\n";
	}
	else{
		cout<<"文件太大无法分配！";
	}

}

void search(int address){
	if(address <= blockSize * 10){
		cout<<"该地址盘块号为："<<address/blockSize<<endl;
	}
	else if(address <= blockSize * 10 + block[10]){
		cout<<"该地址盘块号为："<<9+(address - (blockSize * 10))/blockSize<<endl;
	}
	else if(address <= blockSize * 10 + block[10] + block[11]){
		cout<<"该地址盘块号为："<<(9 + maxBlockNumber + ((address -1 - (blockSize * 10) - block[10])) / blockSize) +1<<endl;

	}
	else if(address <= blockSize * 10 + block[10] + block[11] + block[12]){
		cout<<"该地址盘块号为："<<9 + maxBlockNumber + maxBlockNumber*maxBlockNumber + ((address -1 - (blockSize * 10) - block[10] - block[11]) / blockSize)<<endl;

	}
	else{
		cout<<"超出范围！";
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
		cout<<"1.分配 2.求盘块号"<<endl;
		cin>>i;
		if(i==1){
			int filesize;
			cout<<"输入文件大小："<<endl;
			cin>>filesize;
			allocation(filesize);
		}
		else if(i==2){
			int add;
			cout<<"输入地址："<<endl;
			cin>>add;
			search(add);
		}
		else{
			cout<<"输入错误！"<<endl;
		}
	}

	return 0;
}
