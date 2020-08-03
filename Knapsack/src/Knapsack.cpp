//============================================================================
// Name        : Knapsack.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

void writeData(const float value,const int id[], const int count,const float lastW, const string fileName) {
	ofstream fout(fileName);
	if (!fout.is_open()) {
		std::cerr << "ERROR WHILE OPENING FILE..." << std::endl;
		exit(1);
	}
	fout<<"The max value is:"<<value<<endl;
	fout<<"Selection is:"<<endl;
	for(int i=0; i<=count-1; i++){
		fout<<"id:"<<id[i]+1<<" all"<<endl;
	}
	if(lastW != 0){
		fout<<"id:"<<id[count]+1<<" "<<lastW<<endl;
	}
	cout<<fileName<<" write success!"<<endl;
	fout.close();
}


void sort(float vw[], int id[], int n)
{
    int i, j;
    for (i=0; i<n; i++){
    	for (j=i+1; j<n; j++){
            if (vw[i] <= vw[j]){
            	std::swap(vw[i],vw[j]);
            	std::swap(id[i],id[j]);
            }
        }
    }
}


float knapsack(int n,float maxWight,float v[],float w[],int id[],int &count,float &lastW){
	float vw[n];float maxValue = 0;
	for(int i=0; i<n; i++){
		vw[i] = v[i]/w[i];
		id[i] = i;
	}

	sort(vw,id,n);
	lastW = 0;count = 0;
	for(int i=0; i<n; i++){
		if(maxWight >= w[id[i]]){
			maxWight -= w[id[i]];
			maxValue += v[id[i]];
			count = i;
		}
		else{
			maxValue += maxWight/w[id[i]] * v[id[i]];
			lastW = maxWight;
			count = i;
			maxWight = 0;
			break;
		}
	}
	return maxValue;
}

int main() {
	int n=3,count;
	float wight=50;
	float v[n] = {10,20,30};
	float w[n] = {10,100,120};
	int id[n];
	float lastW;

	float value = knapsack(n,wight,v,w,id,count,lastW);
	cout<<"The max value is:"<<value<<endl;
	writeData(value,id,count,lastW,"output2.txt");

	return 0;
}
