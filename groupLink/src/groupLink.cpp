// SCAN.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//


#include <iostream>
#include <vector>
using namespace std;

const int blockNum = 26;
const int blockNumInAGroup = 3;

class groupLink {
	int N;

	vector<int> Free;
	groupLink * next;

public:
	groupLink();
	void allocation();
	void recycle(int n);
	void output();
};

groupLink::groupLink() :N(0), next(NULL) {

}

void groupLink::allocation() {
	if (N == 0 && this->next == NULL) {
		cout << "��ǰϵͳû�п��п�" << endl;
		return;
	}
	this->Free.pop_back();
	this->N--;
	if (N == 0 && this->next == NULL) {
		return;
	}
	if (N == 0 && this->next) {
		Free.assign(this->next->Free.begin(), this->next->Free.end());
		N = this->next->N;
		if (this->next->next) {
			this->next = this->next->next;

		}
		else {
			delete this->next;
			this->next = NULL;
		}
	}
}


void groupLink::recycle(int n) {
	if (N < blockNumInAGroup) {
		Free.insert(Free.begin(), n);
		N++;
	}
	else if (N == blockNumInAGroup) {
		if (!next) {
			this->next = new groupLink();
			this->next->Free.assign(Free.begin() + 1, Free.end());
			this->next->Free.insert(this->next->Free.begin(), 0);
			this->next->N = blockNumInAGroup - 1;
			this->next->next = NULL;
			int tmp = Free[0];
			this->Free.clear();
			this->Free.insert(Free.begin(), tmp);
			this->Free.insert(Free.begin(), n);
			this->N = 2;
		}
		else {
			groupLink * temp = this->next;
			this->next = new groupLink();
			this->next->Free.assign(Free.begin(), Free.end());
			this->next->N = blockNumInAGroup;
			this->next->next = temp;
			this->Free.clear();
			this->Free.insert(Free.begin(), n);
			this->N = 1;


		}

	}

}

void groupLink::output() {

	groupLink * tmp = this;
	if (tmp->N == 0) {
		cout << "�޿��п�" << endl;
		return;
	}
	int count = 1;
	cout << "��" << count++ << "�飺\n";
	if (this->Free.at(0) == 0) {
		for (int i = N ; i > 0; i--) {
			cout << "[" << i << "]->" << tmp->Free[i] << "\t";
		}
	}
	else {
		for (int i = N - 1; i >= 0; i--) {
			cout << "[" << i << "]->" << tmp->Free[i] << "\t";
		}
	}
	tmp = tmp->next;
	cout << "\n\n";
	while (tmp) {
		cout << "��" << count++ << "�飺\n";

		for (int i = blockNumInAGroup - 1; i >= 0; --i) {
			cout << "[" << i << "]->" << tmp->Free[i] << "\t";
		}
		cout << "\n\n";
		tmp = tmp->next;
	}
}

int main() {
	//vector<int> a(10);
	groupLink gl;
	//for (int i = 201; i < 207; i++) {
	//	gl.recycle(i);
	//}
	//for (int i = 0; i < 4; i++) {
	//	gl.allocation();
	//}
	//gl.output();

	while (1) {
		cout << "1.����\t2.����\t3.��ʾ" << endl;
		int sw;
		cin >> sw;
		if (sw == 1) {
			cout << "������٣�" << endl;
			int n;
			cin >> n;
			for (int i = 0; i < n; i++) {
				gl.allocation();
			}

		}
		else if (sw == 2) {
			cout << "���ն��٣�" << endl;
			int n, h;
			cin >> n;
			cout << "��ʼ�̿��:" << endl;
			cin >> h;
			for (int i = h; i < h + n; i++) {
				gl.recycle(i);
			}
		}
		else if (sw == 3) {
			gl.output();
		}
		else {
			cout << "error!" << endl;
		}
	}

	return 0;
}

