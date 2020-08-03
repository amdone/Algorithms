//============================================================================
// Name        : Floyd-Warshall.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "RandomNumber.h"
using namespace std;

#define SPACE " "
#define MAXVEX 100//最大顶点数
#define INFINITY 999999//表示权值无穷
#define MAXWEIGHT 50//最大权重

typedef struct {
	int vexs[MAXVEX];
	int edge[MAXVEX][MAXVEX];
	int numNodes, numEdges;
} Graph;

void createData(int numNodes, int numEdges) {
	RandomNumber rn(0);
	ofstream fout("input.txt");
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE READING FILE..." << std::endl;
		exit(1);
	}
	fout << numNodes << SPACE << numEdges << endl;
	int v1, v2;
	int arr[numNodes][numNodes];

	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			if (i == j)
				arr[i][j] = INFINITY;
			else {
				arr[i][j] = INFINITY;
			}
		}
	}

	for (int i = 0; i < numNodes; i++) {
		v1 = rn.Random(numNodes);
		v2 = rn.Random(numNodes);
		if (v1 == i)
			v1=(v1+1 == numNodes)?v1-1:v1;
		if (v2 == i)
			v2=(v2+1 == numNodes)?v2-1:v2;
		arr[i][v1] = rn.Random(MAXWEIGHT) + 1;
		arr[v2][i] = rn.Random(MAXWEIGHT) + 1;
	}

	for (int i = 0; i < numEdges - 2 * numNodes; i++) {
		v1 = rn.Random(numNodes);
		v2 = rn.Random(numNodes);
		if (v1!=v2 && arr[v1][v2] == INFINITY) {
			arr[v1][v2] =(rn.Random(2) ?rn.Random(MAXWEIGHT) + 1 : -1 - rn.Random(MAXWEIGHT));
		} else {
			--i;
			continue;
		}
	}

	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			if (arr[i][j] != INFINITY) {
				fout << i + 1 << SPACE << j + 1 << SPACE << arr[i][j] << endl;
			}
		}
	}

	std::cout << "create data success!" << std::endl;
	fout.close();
}

void readData(Graph *Gp) {
	ifstream fin("input.txt");
	if (!fin.is_open()) {
		std::cerr << "ERROR WHILE READING FILE..." << std::endl;
		exit(1);
	}
	int v1, v2, w;
	fin >> Gp->numNodes >> Gp->numEdges;
	for (int i = 0; i < Gp->numNodes; i++)
		Gp->vexs[i] = i + 1;
	for (int i = 1; i <= Gp->numNodes; i++) {
		for (int j = 1; j <= Gp->numNodes; j++) {
			if (i == j)
				Gp->edge[i][j] = INFINITY;
			else
				Gp->edge[i][j] = INFINITY;
		}
	}
	for (int i = 0; i < Gp->numEdges; i++) {
		fin >> v1 >> v2 >> w;
		Gp->edge[v1][v2] = w;
	}
	std::cout << "read data success!" << std::endl;
	fin.close();
}

void writeData(int n, int path[][MAXVEX], string fileName) {
	ofstream fout(fileName);
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE OPENING FILE..." << std::endl;
		exit(1);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			fout << i << "->" << j << " = ";
			int k = i;
			fout << i << " -> ";
			while (k) {
				k = path[k][j];
				if (!k)
					break;
				else
					fout << k << " -> ";
			}
			fout << j << endl;
		}
	}

	std::cout << fileName << " write success!" << std::endl;
	fout.close();
}

void printG(Graph *Gp) {
	for (int i = 0; i < Gp->numNodes; i++) {
		for (int j = 0; j < Gp->numNodes; j++) {
			if (Gp->edge[i][j] == INFINITY) {
				cout << "@" << "\t";
			} else {
				cout << Gp->edge[i][j] << "\t";
			}
		}
		cout << endl;
	}
}

void floyd(Graph g, int path[][MAXVEX]) {

	int c[g.numNodes + 1][g.numNodes + 1];

	for (int i = 1; i <= g.numNodes; i++)
		for (int j = 1; j <= g.numNodes; j++) {
			if (i == j)
				c[i][i] = 0;
			else
				c[i][j] = g.edge[i][j];
			path[i][j] = 0;
		}
	for (int k = 1; k <= g.numNodes; k++) {
		for (int i = 1; i <= g.numNodes; i++)
			for (int j = 1; j <= g.numNodes; j++) {
				int t1, t2, t3;
				t1 = c[i][k];
				t2 = c[k][j];
				t3 = c[i][j];
				if (t1 != INFINITY && t2 != INFINITY
						&& (t3 == INFINITY || t3 > t1 + t2)) {
					c[i][j] = t1 + t2;
					path[i][j] = k;
				}
			}

	}
}
void printPath(int path[][MAXVEX]) {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			cout << path[i][j] << SPACE;
		}
		cout << endl;
	}
}

int main() {
	int n = 10;
	int e = 65;
	Graph g;
	g.numEdges=65;
	g.numNodes=10;
	int arr[11][11] = {
			{0,0,0,0,0,0,0,0,0,0,0},
			{0,0,INFINITY,74,85,43,60,INFINITY,27,19,INFINITY},
			{0,86,0,93,59,22,INFINITY,INFINITY,93,29},
			{0,76   , INFINITY  , 0   , INFINITY   , 31  ,  93  ,  50  ,  28   , 29 ,   44},
			{0,INFINITY,29 ,   38 ,   0   , 87,    67   , 50  ,  83  ,  90   , 46},
			{0,86, INFINITY ,   37  ,  INFINITY  ,  0  , INFINITY   , 35 ,   INFINITY   , 71 ,   INFINITY},
			{0,INFINITY  , 33 ,   55  ,  74  ,  35  ,  0  ,  83   , 30  ,  14   , 75},
			{0,44  ,  32  ,  41  ,  3  ,  INFINITY ,   82 ,   0,    66 ,   66   , 66},
			{0,INFINITY  ,  10  ,  64  ,  50  ,  55   , 84  ,  12  ,  0  ,  50 ,   INFINITY},
			{0,INFINITY   , 82  ,  71   , 51   , INFINITY ,   78 ,   INFINITY  ,  77  ,  0  ,  INFINITY},
			{0,INFINITY  ,  76  ,  INFINITY  ,  73   , 14  ,  INFINITY   , INFINITY   , 70  ,  64   , 0}
	};

	for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++){
			g.edge[i][j] = arr[i][j];
		}
	}

	//createData(n, e);
	//readData(&g);
	int path[MAXVEX][MAXVEX];
	floyd(g, path);
	//printPath(path);
	writeData(n, path, "output.txt");
	return 0;
}
