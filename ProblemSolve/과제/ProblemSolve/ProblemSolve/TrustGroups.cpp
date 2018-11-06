#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<vector>
#include<stack>

using namespace std;

typedef struct {
	string name; // ����� ��ȣ
	int idx; // �� ����� ��� �ε���
} Data; // �̸� ����Ʈ ����ü ����

typedef struct {
	string name; // ����� ��ȣ
	vector<int> trust; // �ŷ��ϴ� ������� �ε���
	bool visit; // �湮�ߴ��� ���ߴ���.
} Person; // ������� ����ü ����

bool cmp(Data x, Data y) {
	return x.name < y.name;
}

vector<Data> list; // �̸� ����Ʈ
vector<Person> graph, r_graph; // ������ �׷����� ������ �׷���
stack<int> st; // SCC Algorithm���� �̿��� ����

int name_Search(int first, int last, string data) { // �� �̸��� �ش��ϴ� �ε��� ã��(�����˻�)
	while (first <= last) {
		int mid = (first + last) / 2; // �߰�����
		if (list[mid].name == data) return list[mid].idx; // �߰������� ã�� �����Ϳ� ����. => �ε��� ��ȯ
		else if (list[mid].name > data) last = mid - 1; // �߰������� ã�� �����ͺ��� ũ�� => �߰������� ���� Ž��
		else first = mid + 1; // �߰������� ã�� �����ͺ��� �۴� => �߰������� ������ Ž��
	}
	return -1; // �����Ͱ� ����
}

void DFS(int index) { // Depth First Search Algorithm -> ������ �׷��� ��ȸ
	graph[index].visit = true; // ������ �湮������ �˸�.
	for (int i = 0; i < graph[index].trust.size(); i++) {
		int next = graph[index].trust[i];
		if (graph[next].visit) continue;
		DFS(next);
	}
	st.push(index);
}

void r_DFS(int index) { // Depth First Search Algorithm -> ������ �׷��� ��ȸ
	r_graph[index].visit = true; // ������ �湮������ �˸�.
	for (int i = 0; i < r_graph[index].trust.size(); i++) {
		int next = r_graph[index].trust[i];
		if (r_graph[next].visit) continue;
		r_DFS(next);
	}
}

int SCC(int P) { // Strongly Connected Component Algorithm
	int group = 0;
	for (int i = 0; i < P; i++) {
		if (graph[i].visit)
			continue;
		DFS(i);
	}
	/* ��� ������ ������� DFS */
	while (st.size()) {
		int top = st.top();
		st.pop();
		if (r_graph[top].visit) continue;
		r_DFS(top);
		group++;
	}
	/* ������ �ִ� ��Ҹ� Pop�Ͽ� ������ �׷��� DFS */
	return group;
}

int main() {
	ifstream inp("TrustGroups.inp");
	ofstream out("TrustGroups.out");

	string L;
	while (true) {
		int P = -1, T = -1; // ��� �� P�� ��������� �ŷڵ� �� T.
		inp >> P >> T;
		getline(inp, L); // �� ������ ���� �ڿ� �� ĭ �����
		if (!P && !T) break;

		list.resize(P); graph.resize(P); r_graph.resize(P); // ������ �Ҵ� ����

		for (int i = 0; i < P; i++) {
			getline(inp, graph[i].name);
			r_graph[i].name = graph[i].name;
			list[i].name = graph[i].name;
			list[i].idx = i;
		} // �̸� �Է�
		sort(list.begin(), list.end(), cmp); // �̸� �� ����
		/* �׷����� ���� ���� */
		while (T--) {
			string opt, opr;
			int optIndex, oprIndex;
			/* opt = �ŷ��ϴ»��, opr = �ŷڹ޴»��. */
			getline(inp, opt); getline(inp, opr);
			optIndex = name_Search(0, P - 1, opt); oprIndex = name_Search(0, P - 1, opr);
			/* �ŷڵ� ���� �Է¹ް� �ε��� ã�� */
			graph[optIndex].trust.push_back(oprIndex); // ������ �׷����� ���� �߰�.
			r_graph[oprIndex].trust.push_back(optIndex); // ������ �׷����� ���� �߰�.
		}
		/* �׷��� �ϼ� */
		int answer = SCC(P); // �������� �׷� ��
		out << answer << '\n'; // ���
		
		list.clear(); graph.clear(); r_graph.clear();
		/* �ʱ�ȭ */
	}
	inp.close();
	out.close();
	return 0;
}