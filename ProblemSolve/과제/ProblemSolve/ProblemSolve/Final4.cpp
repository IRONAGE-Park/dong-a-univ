#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

vector< vector<int> > graph; // �׷��� ����
vector<bool> visit; // ���� �湮 ����

void DFS(int n) {
	visit[n] = true; // �� ������ �湮������ ǥ��
	for (int i = 0; i < graph[n].size(); i++) {
		if (!visit[graph[n][i]]) { // ������ ����� �ٸ� ��忡 �湮���� �ʾ�����,
			DFS(graph[n][i]);
		}
	}
}

int Connected_Component(int V) {
	int cnt = 0;
	for (int i = 0; i < V; i++) {
		if (!visit[i]) { // �� ������ �湮���� �ʾ�����(���ο� Connected_Component �߰�)
			cnt++;
			DFS(i);
		}
	}
	return cnt;
}

int main() {
	ifstream inp("Final4.inp");
	ofstream out("Final4.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int V, E;
		inp >> V >> E;
		graph.resize(V); visit.resize(V); // ���� ������ŭ �Ҵ�
		while (E--) {
			int v1, v2; // �� ���� ����.
			inp >> v1 >> v2;
			graph[v1].push_back(v2); 
			graph[v2].push_back(v1);
		}
		// �Է� ���� �� �׷��� ����.
		out << Connected_Component(V) << '\n';
		graph.clear(); visit.clear(); // �ʱ�ȭ
	}
	inp.close();
	out.close();
	return 0;
}