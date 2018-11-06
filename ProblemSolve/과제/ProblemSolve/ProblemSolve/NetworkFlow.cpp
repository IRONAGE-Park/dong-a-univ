#include<iostream>
#include<fstream>
#include<vector>
#define MAX 10000

using namespace std;

int n; // ������ ��.
int capacity[MAX][MAX], residual[MAX][MAX]; // ���� �׷����� ���� �뷮 �׷���(����ġ ��)
vector<vector<int>> graph; // �׷��� ���� ���� ���踦 ��Ÿ��.
vector<int> path; // ��θ� ��� �迭
int path_w; // �� ����� ����

bool Search_Path(int vertex) { // ��� ã�� �Լ�
	if (vertex != n - 1) { // �������� ������ �� ����.
		for (int i = 0; i < graph.at(vertex).size(); i++) {
			if (residual[vertex][graph.at(vertex).at(i)] > 0) { // �� ��η� �̵� ������ �� (���� �뷮�� 0 �̻��̴�!)
				path.push_back(graph.at(vertex).at(i));
				if (Search_Path(graph.at(vertex).at(i))) return true; // �� ������ �İ� ����� �� �������� ���� �����ϸ�,
				path.pop_back(); // ���� �Ұ����ϸ� �� ��� ���
			}
		}
		return false; // Ư�� �������� �� �� �ִ� ��� ��η� �̵����� �� ���� ���� �Ұ����ϸ�,
	}
	int max = residual[0][path.at(0)]; // 0�� �������� ù ��° ��η� �� ���� ���� �뷮
	for (int i = 1; i < path.size(); i++) {
		if (max > residual[path.at(i - 1)][path.at(i)])
			max = residual[path.at(i - 1)][path.at(i)];
		/* ��θ� ������ ���� �߿� ���� �߰� ���� �뷮�� ���� �� ���� */
	}
	path_w = max; // �� ����� ���� ���� �� �Լ� ����
	return true; // �������� �����ߴٸ�,
}



int main() {
	ifstream inp("NetworkFlow.inp");
	ofstream out("NetworkFlow.out");

	inp >> n;
	graph.resize(n);
	while (true) {
		int v1, v2, w;
		inp >> v1 >> v2 >> w;
		if (v1 == -1 && v2 == -1 && w == -1) break;
		capacity[v1][v2] = w;
		graph.at(v1).push_back(v2); graph.at(v2).push_back(v1);
	}
	/* Input Data */


	inp.close();
	out.close();
	return 0;
}