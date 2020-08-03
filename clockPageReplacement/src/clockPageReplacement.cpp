//============================================================================
// Name        : clockPageReplacement.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

struct block{
	int number;
	bool access;
	bool modify;
};

class clockPR{

	int missCount;		//缺页次数
	int pages;			//总共几个页面
	int current;		//当前页面
	block blockArr[];

public:
	clockPR();
	clockPR(int Pages);
	void accessPage(int n);
	void modifyPage(int n);
	int searchOutPage();
	//void replacePage(int n);
	void print();

};

clockPR::clockPR(int Pages):missCount(0),pages(Pages),current(0){
	for(int i = 0;i < Pages ;i++ ){
		blockArr[i].number = -1;
		blockArr[i].access = 0;
		blockArr[i].modify = 0;
	}
}

int clockPR::searchOutPage(){

	for(int i = 0; i < pages; i++){
		if(blockArr[current].access == 0 && blockArr[current].modify == 0){
			return current;
		}
		else
			current = (current+1) % pages;
	}
	for(int i = 0; i < pages; i++){
		if(blockArr[current].access == 0 && blockArr[current].modify == 1){
			return current;
		}
		else{
			blockArr[current].access = 0;
			current = (current+1) % pages;
		}

	}
	for(int i = 0; i < pages; i++){
		blockArr[i].access = 0;
	}
	return searchOutPage();
}

void clockPR::accessPage(int n){
	for(int i = 0; i < pages; i++){
		if(blockArr[i].number == n){
			blockArr[i].access = 1;
			current = i;
			return;
		}
		else if(blockArr[i].number == -1){
			blockArr[i].number = n;
			blockArr[i].access = 1;
			blockArr[i].modify = 0;
			current = i;
			missCount++;
			return;
		}
	}
	current = (current+1) % pages;
	int replacePage = searchOutPage();
	blockArr[replacePage].number = n;
	blockArr[replacePage].access = 1;
	blockArr[replacePage].modify = 0;
	missCount++;
}

void clockPR::modifyPage(int n){
	for(int i = 0; i < pages; i++){
		if(blockArr[i].number == n){
			blockArr[i].modify = 1;
			current = i;
			return;
		}
		else if(blockArr[i].number == -1){
			blockArr[i].number = n;
			blockArr[i].access = 1;
			blockArr[i].modify = 1;
			current = i;
			missCount++;
			return;
		}
	}
	current = (current+1) % pages;
	int replacePage = searchOutPage();
	blockArr[replacePage].number = n;
	blockArr[replacePage].access = 1;
	blockArr[replacePage].modify = 1;
	missCount++;
}

void clockPR::print(){
	for(int i = 0; i < pages;i++){
		if(blockArr[i].number < 0){
			cout<<i<<"->"<<endl;
		}
		else
			cout<<i<<"->"<<blockArr[i].number<<" A:"<<blockArr[i].access<<" M:"<<blockArr[i].modify<<endl;
	}

	cout<<"缺页次数："<<missCount<<endl;
}

int main() {
	int length;
	while(1){
		cout<<"请输入队列长度:"<<endl;
		cin>>length;
		if(length<1)cout<<"error!"<<endl;
		else break;
	}

	clockPR p(length);

//	p.accessPage(0);
//	p.modifyPage(1);
//	p.accessPage(3);
//	p.accessPage(6);
//	p.modifyPage(2);
//	p.accessPage(4);
	p.print();
	while(1){
		int i,n;
		cout<<"请输入页号："<<endl;
		cin>>n;
		cout<<"访问：1，修改：2"<<endl;
		cin>>i;
		if(i == 1){
			p.accessPage(n);
		}
		else if(i == 2){
			p.modifyPage(n);
		}
		p.print();
	}
	return 0;
}

