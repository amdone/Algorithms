//============================================================================
// Name        : MST.cpp
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
#define NOEDGE 0/*表示无边*/

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
	bool arr[numNodes][numNodes];
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; i < numNodes; i++) {
			arr[i][j] = false;
		}
	}
	//生成一个包含所有节点的连通图
	int markArr[numNodes], markNodes = 1;
	markArr[0] = rn.Random(numNodes) + 1;
	for (int i = 0; i < numNodes - 1; i++) {
		int v = rn.Random(numNodes) + 1;
		bool finded = false;
		for (int j = 0; j < markNodes; j++) {
			if (markArr[j] == v) {
				finded = true;
				--i;
				break;
			}
		}
		if (!finded) {
			v1 = markArr[rn.Random(markNodes)];
			v2 = v;
			fout << v1 << SPACE << v2 << SPACE << rn.Random(50) + 1 << endl;
			markArr[markNodes] = v2;
			++markNodes;
			arr[v1][v2] = true;

		}
	}
	//添加剩余边
	for (int i = 0; i < numEdges - numNodes + 1; i++) {
		v1 = rn.Random(numNodes) + 1;
		v2 = rn.Random(numNodes) + 1;
		if (!arr[v1][v2] && !arr[v2][v1]) {
			fout << v1 << SPACE << v2 << SPACE << rn.Random(50) + 1 << endl;
			arr[v1][v2] = true;
		} else {
			--i;
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
	for (int i = 0; i < Gp->numNodes; i++) {
		for (int j = 0; j < Gp->numNodes; j++) {
			if (i == j)
				Gp->edge[i][j] = NOEDGE;
			else
				Gp->edge[i][j] = INFINITY;
		}
	}
	for (int i = 0; i < Gp->numEdges; i++) {
		fin >> v1 >> v2 >> w;
		Gp->edge[v1 - 1][v2 - 1] = w;
		Gp->edge[v2 - 1][v1 - 1] = w;
	}
	std::cout << "read data success!" << std::endl;
	fin.close();
}

void writeData(int n,int mst[][3],string fileName) {
	ofstream fout(fileName);
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE OPENING FILE..." << std::endl;
		exit(1);
	}
	for(int i=0;i<n;i++){
		fout<<mst[i][0]<<"->"<<mst[i][1]<<SPACE<<mst[i][2]<<endl;
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

int MSTPrim(Graph *Gp, int rmst[][3]) {
	int n = Gp->numNodes;
	int sum = 0;
	int lowcost[n], mst[n];
	for (int i = 0; i < n; i++) {
		lowcost[i] = Gp->edge[0][i];
		mst[i] = 1;
	}
	int v = 1;
	lowcost[0] = -1;
	for (int i = 0; i < n - 1; i++) {
		int min = INFINITY;
		for (int j = 0; j < n; j++) {
			if (min > lowcost[j] && lowcost[j] != -1) {
				min = lowcost[j];
				v = j + 1;
			}
		}
		sum += min;
		rmst[i][0] = mst[v - 1];
		rmst[i][1] = v;
		rmst[i][2] = min;
		//cout<<mst[v-1]<<" "<<v<<" "<<min<<endl;
		lowcost[v - 1] = -1;
		for (int i = 0; i < n; i++) {
			if (lowcost[i] > Gp->edge[v - 1][i]) {
				lowcost[i] = Gp->edge[v - 1][i];
				mst[i] = v;
			}
		}
	}
	return sum;
}

int main() {
	int n=7;
	int e=16;
	createData(n, e);
	Graph g;
	readData(&g);
	//printG(&g);
	int mst[n-1][3];
	int sum = MSTPrim(&g, mst);
	cout<<"The sum of MST's weight is:"<<sum<<endl;
	writeData(n-1,mst,"output.txt");
	//CreateGraph(&g);
	return 0;
}
