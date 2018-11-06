#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

typedef struct Node {
	int vertex; // vertex 번호
	int edge; // 이전 노드와 vertex 사이의 거리
}Node;

vector< vector<Node> > tree;
int len_MAX, update_COST; // 루트에서 리프까지의 길이 중 최댓값, 갱신 비용

int Length_DFS(int vertex, int len) { // Depth First Search(깊이 우선 탐색)을 통해 특정 노드에서 단말노드까지의 최대 거리.
	if (tree[vertex].size() != 0) { // 자식이 있으면 = 리프노드가 아니면
		int L, L_MAX = 0; // 자식노드의 길이 중 가장 긴 것
		for (int i = 0; i < tree[vertex].size(); i++) {
			L = Length_DFS(tree[vertex][i].vertex, len + tree[vertex][i].edge); // vertex의 자식 노드들 순회
			if (L_MAX < L) L_MAX = L;
		}
		/* 자식들로 재귀 */
		return L_MAX;
	}
	return len; // 리프노드이면 거기까지의 길이 반환.
}

void Update_DFS(int vertex, int len) { // Depth First Search(깊이 우선 탐색)을 통해 루트에서 리프까지의 길이를 모두 최대로 맞춰줌
	if (tree[vertex].size() != 0) { // 자식이 있으면 = 리프노드가 아니면
		int child_L;
		for (int i = 0; i < tree[vertex].size(); i++) {
			child_L = Length_DFS(tree[vertex][i].vertex, len + tree[vertex][i].edge); // 그 간선으로 이동했을때 최대 길이 반환
			tree[vertex][i].edge += (len_MAX - child_L); // 그 간선의 최대 길이와 총 최대길이의 차이만큼 더해줌
			update_COST += (len_MAX - child_L); // 거기서 발생한 비용
			Update_DFS(tree[vertex][i].vertex, len + tree[vertex][i].edge); // vertex의 자식 노드 순회
		}
	}
}

int main() {
	ifstream inp("Tree.inp");
	ofstream out("Tree.out");

	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n; // 정점의 수
		inp >> n;
		tree.resize(n);
		for (int i = 1; i <= n - 1; i++) { // 1번부터 n - 1번까지
			Node node;
			inp >> node.vertex >> node.edge;
			tree[node.vertex].push_back({ i, node.edge }); // 트리에다 간선 정보 기입
		}
		/* INPUT DATA */
		len_MAX = Length_DFS(0, 0); // 정점기준으로 DFS한 후 리프노드까지 최대 길이 return.
		Update_DFS(0, 0);
		out << update_COST << '\n';
		/* OUTPUT DATA */
		tree.clear(), len_MAX = 0, update_COST = 0; // init
	}
	inp.close();
	out.close();
	return 0;
}