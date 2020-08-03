//============================================================================
// Name        : Dijkstra.cpp
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
#define MAXVEX 100/*最大顶点数*/
#define INFINITY 999999/*表示权值无穷*/


typedef struct {
	int vexs[MAXVEX];
	int edge[MAXVEX][MAXVEX];
	int numNodes, numEdges;
} Graph;

void createData(int numNodes, int numEdges) {
	if (numEdges < 2 * numNodes) {
		std::cerr << "ERROR:numEdges is too small!" << std::endl;
		exit(1);
	}
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
				arr[i][j] = 0;
			else {
				arr[i][j] = INFINITY;
			}
		}
	}

	for (int i = 0; i < numNodes; i++) {
		v1 = rn.Random(numNodes);
		v2 = rn.Random(numNodes);
		if (v1 == i)
			v1++;
		if (v2 == i)
			v2++;
		arr[i][v1] = rn.Random(50) + 1;
		arr[v2][i] = rn.Random(50) + 1;
	}

	for (int i = 0; i < numEdges - 2 * numNodes; i++) {
		v1 = rn.Random(numNodes);
		v2 = rn.Random(numNodes);
		if (arr[v1][v2] == INFINITY) {
			arr[v1][v2] = rn.Random(50) + 1;
		} else {
			--i;
		}
	}

	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			if (i != j && arr[i][j] != INFINITY) {
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
		//Gp->edge[v2][v1] = w;
	}
	std::cout << "read data success!" << std::endl;
	fin.close();
}

void writeData(int n, int s, int r[][MAXVEX], string fileName) {
	ofstream fout(fileName);
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE OPENING FILE..." << std::endl;
		exit(1);
	}
	for (int i = 1; i <= n; i++) {
		if (i != s) {
			int count = 0;
			while (r[i][count + 1]) {
				fout << r[i][count++] << "<-";
			}
			fout << r[i][count++] << " : " << r[i][count + 2] << endl;
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

bool Isfull(bool rec[], int n) {

	for (int i = 1; i <= n; i++)
		if (!rec[i])
			return 0;
	return 1;
}

int findmin(int arr[], bool rec[], int n) {
	int min, index;
	for (int i = 1; i <= n; i++)
		if (!rec[i]) {
			min = arr[i];
			index = i;
			break;
		}
	for (int i = 1; i <= n; i++)
		if (!rec[i] && min > arr[i]) {
			min = arr[i];
			index = i;
		}
	return index;
}

void Dijkstra(Graph g, int s, int r[][MAXVEX]) {
	int prev[g.numNodes + 1];//源s到顶点v的前驱顶点
	int dist[g.numNodes + 1];//记录源点s到顶点v的路程值
	bool rec[g.numNodes + 1];//rec是符合条件的顶点集合
	for (int i = 0; i < g.numNodes; i++)
		rec[i + 1] = 0;
	prev[s] = 0;
	for (int i = 1; i <= g.numNodes; i++) {
		dist[i] = g.edge[s][i];
		if (g.edge[s][i] != INFINITY)
			prev[i] = s;
		else
			prev[i] = 0;
	}
	dist[s] = 0;
	while (!Isfull(rec, g.numNodes)) {
		int min = findmin(dist, rec, g.numNodes);
		rec[min] = 1;
		for (int j = 1; j <= g.numNodes; j++) {
			if (g.edge[min][j] != INFINITY) {
				if (dist[j] > dist[min] + g.edge[min][j]) {
					dist[j] = dist[min] + g.edge[min][j];
					prev[j] = min;
				}
			}
		}
	}
	for (int i = 1; i <= g.numNodes; i++){
		if (i != s) {
			int index = i;
			int count = 0;
			while (prev[index]) {
				r[i][count++] = index;
				index = prev[index];
			}
			r[i][count++] = s;
			r[i][count + 1] = dist[i];
		}
	}
}

int main() {
	int n=7;
	int e=16;
	int s=1;//所求源点
	createData(n,e);
	Graph g;
	readData(&g);
	int r[n+1][MAXVEX];
	Dijkstra(g, s, r);
	cout<<"success!"<<endl;
	writeData(n, s, r, "output2.txt");
	return 0;
}
