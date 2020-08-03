//============================================================================
// Name        : LRU.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

class LRU{

	unsigned int pages;
	vector<int> mem;
	vector<int> used;

public:
	LRU(int n);
	void visit(int pageNum);
	void output();

};

LRU::LRU(int n):pages(n){

}

void LRU::visit(int pageNum){
	for(unsigned int i=0;i<used.size();i++){
		used[i]++;
	}
	for(unsigned int i=0;i<mem.size();i++){
		if(this->mem.at(i)==pageNum){
			used[i] = 0;
			return;
		}
	}
	if(mem.size()==pages){
		int index = 0;
		for(unsigned int i=0;i<pages;i++){
			if(used[index] < used[i]){
				index = i;
			}
		}
		mem[index] = pageNum;
		used[index] = 0;
	}
	else{
		mem.push_back(pageNum);
		used.push_back(0);
	}
}


void LRU::output(){

	for(unsigned int i=0;i<mem.size();i++){
			cout<<mem.at(i)<<"\n";
	}
	cout<<endl;
}

int main() {
	int length;
	while(1){
		cout<<"请输入队列长度:"<<endl;
		cin>>length;
		if(length<1)cout<<"error!"<<endl;
		else break;
	}

	LRU p(length);


	p.output();
	while(1){
		int n;
		cout<<"请输入页号："<<endl;
		cin>>n;
		p.visit(n);
		p.output();
	}
	return 0;
}
