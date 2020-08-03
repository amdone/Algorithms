#include <iostream>

#define maxP 10
#define maxS 10
using namespace std;

int Available[maxS];
int Max[maxP][maxS];
int Allocation[maxP][maxS];
int Need[maxP][maxS];
int Request[maxS];
int Finish[maxP];
int path[maxP] = { 0 };
int processNum, srcNum;


void outPath() {
    cout << "系统安全序列是:\n";
    cout << "P" << path[0] - 1;
    for (int i = 1; path[i] != 0; i++) {
        cout << "->P" << path[i] - 1;
    }
    for (int i = 0; i < processNum; i++) path[i] = 0;
    cout << endl;
}


int BankSafe() {
    int i, j, k = 0;
    int Work[maxS];
    for (i = 0; i < srcNum; i++) Work[i] = Available[i];
    for (i = 0; i < processNum; i++) Finish[i] = 0;
    for (i = 0; i < processNum; i++) {
        if (Finish[i] == 1)
            continue;
        else {
            for (j = 0; j < srcNum; j++) {
                if (Need[i][j] > Work[j])
                    break;
            }
            if (j == srcNum) {
                Finish[i] = 1;
                for (int k = 0; k < srcNum; k++)
                    Work[k] += Allocation[i][k];
                path[k++] = i + 1;
                i = -1;
            }
            else continue;
        }
        if (k == processNum) {
            return 1;
        }
    }
    return 0;
}
void input(int processNum, int srcNum) {
    cout << "输入每个进程最多所需的各类资源数:\n";
    for (int i = 0; i < processNum; i++) {
        cout << "P" << i << " : ";
        for (int j = 0; j < srcNum; j++)
            cin >> Max[i][j];
    }
    cout << "输入每个进程已经分配的各类资源数:\n";
    for (int i = 0; i < processNum; i++) {
        cout << "P" << i << " : ";
        for (int j = 0; j < srcNum; j++) {
            cin >> Allocation[i][j];
            Need[i][j] = Max[i][j] - Allocation[i][j];
            if (Need[i][j] < 0) {
                cout << "你输入的进程P" << i << "所拥有的第" << j + 1 << "个资源错误，请重新输入:\n";
                j--;
                continue;
            }
        }
    }
    cout << "请输入各个资源现有的数目:\n";
    for (int i = 0; i < srcNum; i++)
        cin >> Available[i];
}
int requestP() {
    int Pi;
    cout << "输入要申请资源的进程号(0-4)：";
    cin >> Pi;
    //Pi;
    cout << "输入进程所请求的各资源的数量:";
    for (int i = 0; i < srcNum; i++)
        cin >> Request[i];
    for (int i = 0; i < srcNum; i++) {
        if (Request[i] > Need[Pi][i]) {
            cout << "所请求资源数超过进程的需求量！\n";
            return 1;
        }
        if (Request[i] > Available[i]) {
            cout << "所请求资源数超过系统所有的资源数！\n";
            return 1;
        }
    }
    for (int i = 0; i < srcNum; i++) {
        Available[i] -= Request[i];
        Allocation[Pi][i] += Request[i];
        Need[Pi][i] -= Request[i];
    }
    if (BankSafe()) {
        cout << "系统安全!\n";
        outPath();
        cout << "同意分配请求!\n";
    }
    else {
        for (int i = 0; i < srcNum; i++) {
            Available[i] += Request[i];
            Allocation[Pi][i] -= Request[i];
            Need[Pi][i] += Request[i];
        }
        cout << "请求将导致系统不安全,无法完成该请求!\n";
    }
    return 0;
}


void outDATA() {
    int i, j;
    cout << "\n系统可用的资源数为 :";
    for (j = 0; j < srcNum; j++)
        cout << " " << Available[j];
    cout << endl << "各进程还需要的资源量:" << endl;
    for (i = 0; i < processNum; i++) {
        cout << "进程 P" << i << " :";
        for (j = 0; j < srcNum; j++)
            cout << " " << Need[i][j];
        cout << endl;
    }
    cout << endl << "各进程已经得到的资源量:" << endl;
    for (i = 0; i < processNum; i++) {
        cout << "进程 P" << i << " :";
        for (j = 0; j < srcNum; j++)
            cout << " " << Allocation[i][j];
        cout << endl;
    }
    cout << endl;
}


int main() {
    cout << "输入进程的数目:";
    cin >> processNum;
    cout << "输入资源的种类:";
    cin >> srcNum;
    input(processNum, srcNum);
    if (BankSafe()) {
        cout << "当前系统安全!\n";
        outPath();
    }
    else {
        cout << "当前系统不安全!\n";
        return 0;
    }
    while (1) {
        requestP();
        outDATA();

    }
    return 0;
}
