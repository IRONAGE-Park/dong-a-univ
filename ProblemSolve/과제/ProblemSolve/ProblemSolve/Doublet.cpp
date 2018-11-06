#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>

using namespace std;

typedef struct Dict { // ���� ����ü ����
	string word; // �ܾ�
	vector<int> list; // Doublet ����Ʈ
	bool check;
}Dict;

typedef struct Route { // Queue���� ����� ����ü.
	int index;
	vector<string> r;
}Route;

vector<string> r, route;
deque<Route> BFSQueue;
Dict dict[30000];
int n;

bool CheckDoublet(string str1, string str2) { // Doublet Ȯ��
	if (str1.length() != str2.length())
		return false;
	else {
		int cnt = 0;
		for (int i = 0; i < str1.length(); i++) {
			if (str1.at(i) != str2.at(i))
				cnt++;
		}
		if (cnt == 1) return true;
		else return false;
	}
}
void MakeGraph() { // Create Graph
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (CheckDoublet(dict[i].word, dict[j].word))
				dict[i].list.push_back(j);
}
void DFS(Dict *d, string item) { // DFS Ž��
	if (!d->check) {
		d->check = true;
		r.push_back(d->word);

		if (d->word.compare(item) == 0) { // ���� DFS�� route�� ã����
			if (route.empty()) { // �׶� �̸� ������ route�� ������
				route = r;
				r.pop_back();
				d->check = false;
				return;
			}
			else {
				if (route.size() > r.size()) {
					route = r;
					r.pop_back();
					d->check = false;
					return;
				}
			}
		}
		for (int i = 0; i < d->list.size(); i++) {
			DFS(&dict[d->list.at(i)], item);
		}
		d->check = false;
		r.pop_back();
	}
}
void BFS(string item) {
	while (!BFSQueue.empty()) { // Queue�� ������� ��������.
		Route now = BFSQueue.front();
		BFSQueue.pop_front();
		if (!dict[now.index].check) { // �湮�����ʾ�����.
			dict[now.index].check = true;
			now.r.push_back(dict[now.index].word); // �̸��� ��Ʈ�� �ø�.
			if (dict[now.index].word.compare(item) == 0) { // ���� �� ��尡 �������̸�.
				route = now.r;
				return; // ����.
			}
			for (int i = 0; i < dict[now.index].list.size(); i++) {
				if (!dict[dict[now.index].list[i]].check) {
					Route add;
					add.index = dict[now.index].list[i];
					add.r = now.r;
					BFSQueue.push_back(add);
				}
			}
		}
	}
}

int main() {
	ifstream inp("Doublet.inp");
	ofstream out("Doublet.out");
	for (n = 0;;n++) {
		char str[20];
		inp.getline(str, 20);
		dict[n].word = str;
		if (dict[n].word.length() == 0)
			break;
	}
	// input.
	MakeGraph(); // graph ����

	while (true) { // testcase
		string depart, arrive;
		inp >> depart >> arrive;
		if (depart.length() == 0) break;
		for (int i = 0; i < n; i++) {
			if (dict[i].word.compare(depart) == 0) { // �������� ������.
				Route start;
				start.index = i;
				BFSQueue.push_back(start); // ������ ť�� ����.
				BFS(arrive);
				break;
			}
		}
		if (route.empty()) { // ���� Ž���� ��ΰ� ������.
			out << "No solution." << endl;
		}
		else {
			for (int i = 0; i < route.size(); i++) {
				out << route.at(i) << endl;
			}
		}
		out << endl;
		for (int i = 0; i < n; i++) {
			dict[i].check = false;
		}
		BFSQueue.clear();
		route.clear();
	}
	inp.close();
	out.close();
	return 0;
}