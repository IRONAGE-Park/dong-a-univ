#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

vector< vector<int> > graph; // 그래프 선언
vector<bool> visit; // 정점 방문 정보

void DFS(int n) {
	visit[n] = true; // 그 정점에 방문했음을 표시
	for (int i = 0; i < graph[n].size(); i++) {
		if (!visit[graph[n][i]]) { // 정점에 연결된 다른 노드에 방문하지 않았으면,
			DFS(graph[n][i]);
		}
	}
}

int Connected_Component(int V) {
	int cnt = 0;
	for (int i = 0; i < V; i++) {
		if (!visit[i]) { // 그 정점에 방문하지 않았으면(새로운 Connected_Component 발견)
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
		graph.resize(V); visit.resize(V); // 정점 갯수만큼 할당
		while (E--) {
			int v1, v2; // 두 연결 정점.
			inp >> v1 >> v2;
			graph[v1].push_back(v2); 
			graph[v2].push_back(v1);
		}
		// 입력 받은 후 그래프 형성.
		out << Connected_Component(V) << '\n';
		graph.clear(); visit.clear(); // 초기화
	}
	inp.close();
	out.close();
	return 0;
}