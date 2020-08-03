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
    cout << "ϵͳ��ȫ������:\n";
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
    cout << "����ÿ�������������ĸ�����Դ��:\n";
    for (int i = 0; i < processNum; i++) {
        cout << "P" << i << " : ";
        for (int j = 0; j < srcNum; j++)
            cin >> Max[i][j];
    }
    cout << "����ÿ�������Ѿ�����ĸ�����Դ��:\n";
    for (int i = 0; i < processNum; i++) {
        cout << "P" << i << " : ";
        for (int j = 0; j < srcNum; j++) {
            cin >> Allocation[i][j];
            Need[i][j] = Max[i][j] - Allocation[i][j];
            if (Need[i][j] < 0) {
                cout << "������Ľ���P" << i << "��ӵ�еĵ�" << j + 1 << "����Դ��������������:\n";
                j--;
                continue;
            }
        }
    }
    cout << "�����������Դ���е���Ŀ:\n";
    for (int i = 0; i < srcNum; i++)
        cin >> Available[i];
}
int requestP() {
    int Pi;
    cout << "����Ҫ������Դ�Ľ��̺�(0-4)��";
    cin >> Pi;
    //Pi;
    cout << "�������������ĸ���Դ������:";
    for (int i = 0; i < srcNum; i++)
        cin >> Request[i];
    for (int i = 0; i < srcNum; i++) {
        if (Request[i] > Need[Pi][i]) {
            cout << "��������Դ���������̵���������\n";
            return 1;
        }
        if (Request[i] > Available[i]) {
            cout << "��������Դ������ϵͳ���е���Դ����\n";
            return 1;
        }
    }
    for (int i = 0; i < srcNum; i++) {
        Available[i] -= Request[i];
        Allocation[Pi][i] += Request[i];
        Need[Pi][i] -= Request[i];
    }
    if (BankSafe()) {
        cout << "ϵͳ��ȫ!\n";
        outPath();
        cout << "ͬ���������!\n";
    }
    else {
        for (int i = 0; i < srcNum; i++) {
            Available[i] += Request[i];
            Allocation[Pi][i] -= Request[i];
            Need[Pi][i] += Request[i];
        }
        cout << "���󽫵���ϵͳ����ȫ,�޷���ɸ�����!\n";
    }
    return 0;
}


void outDATA() {
    int i, j;
    cout << "\nϵͳ���õ���Դ��Ϊ :";
    for (j = 0; j < srcNum; j++)
        cout << " " << Available[j];
    cout << endl << "�����̻���Ҫ����Դ��:" << endl;
    for (i = 0; i < processNum; i++) {
        cout << "���� P" << i << " :";
        for (j = 0; j < srcNum; j++)
            cout << " " << Need[i][j];
        cout << endl;
    }
    cout << endl << "�������Ѿ��õ�����Դ��:" << endl;
    for (i = 0; i < processNum; i++) {
        cout << "���� P" << i << " :";
        for (j = 0; j < srcNum; j++)
            cout << " " << Allocation[i][j];
        cout << endl;
    }
    cout << endl;
}


int main() {
    cout << "������̵���Ŀ:";
    cin >> processNum;
    cout << "������Դ������:";
    cin >> srcNum;
    input(processNum, srcNum);
    if (BankSafe()) {
        cout << "��ǰϵͳ��ȫ!\n";
        outPath();
    }
    else {
        cout << "��ǰϵͳ����ȫ!\n";
        return 0;
    }
    while (1) {
        requestP();
        outDATA();

    }
    return 0;
}
