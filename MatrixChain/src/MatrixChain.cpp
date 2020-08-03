//============================================================================
// Name        : MatrixChain.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// 动态规划算法求矩阵连乘积问题...
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileOperation.h"
using namespace std;

#define MAX_SIZE 100

int p[MAX_SIZE]; //矩阵连乘积A1A2...An中矩阵的位数一维数组，其中Ai的维数为Pi-1*Pi，i=1,2,..,n
int n; //矩阵个数
int m[MAX_SIZE][MAX_SIZE]; //最少数乘次数
int s[MAX_SIZE][MAX_SIZE]; //A[i,j]的 最佳断开位置

void DPMatrixChain(int p[MAX_SIZE], int n, int m[][MAX_SIZE],
		int s[][MAX_SIZE]) {
	int i, j, r;
	int t;
	int k;
	for (i = 1; i <= n; i++) {
		//初始化对角线，因为m[i][j]的值位于上三角区域，当i=j时为单一矩阵，无需计算
		m[i][i] = 0;
	}

	for (r = 2; r <= n; r++) { //变量r表示矩阵链长的递增，如r=2，表示AiA(i+1)，此处处理2~n的所有矩阵链,上边的对角线初始化相当于r=1
		for (i = 1; i <= n - r + 1; i++) { //此处取矩阵子链，长度为r的矩阵子链共有n-r+1中组合方式
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
	int n = 20; //矩阵个数
	int size = n+1;
	int low = 5;
	int high = 50;
	cout<<"start..."<<endl;
	//createData(size,low,high);
	readData(p,size);
	DPMatrixChain(p, n, m, s);
	cout << "最少数乘次数矩阵 \n";
	printM(m, n);
	//cout << "最佳断开位置矩阵 \n";
	//printS(s, n);
	cout << "最佳序列:\n";
	string r = strResult(1,n);
	cout<<r<<endl;
	writeData(r,m[1][n],"output.txt");
	cout<<"end..."<<endl;

}
