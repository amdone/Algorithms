//============================================================================
// Name        : LL1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int lookahead;
int factor = 0;
int len[256];

void E();
void E2();
void T();
void T2();
void F();
void F2();
void P();

int getToken(){
	if(len[factor+1] == '#'){
		cout<<"correct!";
		exit(0);
	}
	return len[++factor];
}

void matchToken(int expected){
	if(lookahead != expected){
		cout<<"syntax error";
		exit(0);
	}
	else{
		lookahead = getToken();
	}
}



//E¡úTE'
void E(){
	T();
	E2();
}

//E'¡ú+E|¦Å
void E2(){
	switch(lookahead){
	case '+':
		matchToken('+');
		E();
		break;
	case '#':
		break;
	case ')':
		break;
	default:
		cout<<"syntax error!"<<endl;
		exit(0);
	}
}

//T¡úT|¦Å
void T(){
	F();
	T2();
}


//T'¡úT|¦Å
void T2(){
	switch(lookahead){
	case '(':
		T();
		break;
	case 'a':
		T();
		break;
	case 'b':
		T();
		break;
	case '^':
		T();
		break;
	case ')':
		break;
	case '#':
		break;
	case '+':
		break;
	default:
		cout<<"syntax error!"<<endl;
		exit(0);
	}
}

//F¡úPF'
void F(){
	P();
	F2();
}

//F'¡ú*F'|¦Å
void F2(){
	switch(lookahead){
	case '*':
		matchToken('*');
		F2();
		break;
	case '(':
		break;
	case ')':
		break;
	case 'a':
		break;
	case 'b':
		break;
	case '^':
		break;
	case '#':
		break;
	default:
		cout<<"syntax error!"<<endl;
		exit(0);
	}
}

//P¡ú(E)|a|b|^
void P(){
	switch(lookahead){
	case '(':
		matchToken('(');
		E();
		matchToken(')');
		break;
	case 'a':
		matchToken('a');
		break;
	case 'b':
		matchToken('b');
		break;
	case '^':
		matchToken('^');
		break;
	default:
		cout<<"syntax error!"<<endl;
		exit(0);
	}
}

int main() {
	cout<<"ÇëÊäÈëÎÄ·¨£º"<<endl;
	string str;
	cin>>str;

	int i=0;
	for(; i < str.length(); ++i){
	    len[i] = str[i];
	}
	len[i] = '#';
	lookahead = len[0];
	E();
	return 0;
}
