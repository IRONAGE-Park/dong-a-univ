#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

typedef struct Node {
	int vertex; // vertex ��ȣ
	int edge; // ���� ���� vertex ������ �Ÿ�
}Node;

vector< vector<Node> > tree;
int len_MAX, update_COST; // ��Ʈ���� ���������� ���� �� �ִ�, ���� ���

int Length_DFS(int vertex, int len) { // Depth First Search(���� �켱 Ž��)�� ���� Ư�� ��忡�� �ܸ��������� �ִ� �Ÿ�.
	if (tree[vertex].size() != 0) { // �ڽ��� ������ = ������尡 �ƴϸ�
		int L, L_MAX = 0; // �ڽĳ���� ���� �� ���� �� ��
		for (int i = 0; i < tree[vertex].size(); i++) {
			L = Length_DFS(tree[vertex][i].vertex, len + tree[vertex][i].edge); // vertex�� �ڽ� ���� ��ȸ
			if (L_MAX < L) L_MAX = L;
		}
		/* �ڽĵ�� ��� */
		return L_MAX;
	}
	return len; // ��������̸� �ű������ ���� ��ȯ.
}

void Update_DFS(int vertex, int len) { // Depth First Search(���� �켱 Ž��)�� ���� ��Ʈ���� ���������� ���̸� ��� �ִ�� ������
	if (tree[vertex].size() != 0) { // �ڽ��� ������ = ������尡 �ƴϸ�
		int child_L;
		for (int i = 0; i < tree[vertex].size(); i++) {
			child_L = Length_DFS(tree[vertex][i].vertex, len + tree[vertex][i].edge); // �� �������� �̵������� �ִ� ���� ��ȯ
			tree[vertex][i].edge += (len_MAX - child_L); // �� ������ �ִ� ���̿� �� �ִ������ ���̸�ŭ ������
			update_COST += (len_MAX - child_L); // �ű⼭ �߻��� ���
			Update_DFS(tree[vertex][i].vertex, len + tree[vertex][i].edge); // vertex�� �ڽ� ��� ��ȸ
		}
	}
}

int main() {
	ifstream inp("Tree.inp");
	ofstream out("Tree.out");

	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n; // ������ ��
		inp >> n;
		tree.resize(n);
		for (int i = 1; i <= n - 1; i++) { // 1������ n - 1������
			Node node;
			inp >> node.vertex >> node.edge;
			tree[node.vertex].push_back({ i, node.edge }); // Ʈ������ ���� ���� ����
		}
		/* INPUT DATA */
		len_MAX = Length_DFS(0, 0); // ������������ DFS�� �� ���������� �ִ� ���� return.
		Update_DFS(0, 0);
		out << update_COST << '\n';
		/* OUTPUT DATA */
		tree.clear(), len_MAX = 0, update_COST = 0; // init
	}
	inp.close();
	out.close();
	return 0;
}