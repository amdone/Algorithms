//============================================================================
// Name        : MatrixChain.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// ��̬�滮�㷨��������˻�����...
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileOperation.h"
using namespace std;

#define MAX_SIZE 100

int p[MAX_SIZE]; //�������˻�A1A2...An�о����λ��һά���飬����Ai��ά��ΪPi-1*Pi��i=1,2,..,n
int n; //�������
int m[MAX_SIZE][MAX_SIZE]; //�������˴���
int s[MAX_SIZE][MAX_SIZE]; //A[i,j]�� ��ѶϿ�λ��

void DPMatrixChain(int p[MAX_SIZE], int n, int m[][MAX_SIZE],
		int s[][MAX_SIZE]) {
	int i, j, r;
	int t;
	int k;
	for (i = 1; i <= n; i++) {
		//��ʼ���Խ��ߣ���Ϊm[i][j]��ֵλ�����������򣬵�i=jʱΪ��һ�����������
		m[i][i] = 0;
	}

	for (r = 2; r <= n; r++) { //����r��ʾ���������ĵ�������r=2����ʾAiA(i+1)���˴�����2~n�����о�����,�ϱߵĶԽ��߳�ʼ���൱��r=1
		for (i = 1; i <= n - r + 1; i++) { //�˴�ȡ��������������Ϊr�ľ�����������n-r+1����Ϸ�ʽ
			j = i + r - 1;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;
			for (k = i + 1; k < j; k++) {
				t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j]) {
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
}

void printM(int m[][MAX_SIZE], int n) {
	int i, j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			printf("%d\t", m[i][j]);
		}
		printf("\n");
	}
}

void printS(int s[][MAX_SIZE], int n) {
	int i, j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			printf("%d\t", s[i][j]);
		}
		printf("\n");
	}
}

void printmatrix(int i, int j) {
	if (i == j)
		cout << "A" << i;
	else {
		printf("(");
		printmatrix(i, s[i][j]);
		printmatrix(s[i][j] + 1, j);
		printf(")");
	}
}

string strResult(int i,int j){
	if (i == j)
		if(i==17){
			return "A66";
		}
		else{
			return "A"+to_string(i);
		}

	else {
		return "("+strResult(i, s[i][j])+strResult(s[i][j] + 1, j)+")";
	}
}

int main() {
	int n = 20; //�������
	int size = n+1;
	int low = 5;
	int high = 50;
	cout<<"start..."<<endl;
	//createData(size,low,high);
	readData(p,size);
	DPMatrixChain(p, n, m, s);
	cout << "�������˴������� \n";
	printM(m, n);
	//cout << "��ѶϿ�λ�þ��� \n";
	//printS(s, n);
	cout << "�������:\n";
	string r = strResult(1,n);
	cout<<r<<endl;
	writeData(r,m[1][n],"output.txt");
	cout<<"end..."<<endl;

}
