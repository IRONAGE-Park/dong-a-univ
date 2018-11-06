#include<iostream>
#include<fstream>
#include<vector>
#define MAX 10000

using namespace std;

int n; // 정점의 수.
int capacity[MAX][MAX], residual[MAX][MAX]; // 가용 그래프와 남은 용량 그래프(가중치 용)
vector<vector<int>> graph; // 그래프 간선 간의 관계를 나타냄.
vector<int> path; // 경로를 담는 배열
int path_w; // 그 경로의 유량

bool Search_Path(int vertex) { // 경로 찾는 함수
	if (vertex != n - 1) { // 도착지에 도달할 때 까지.
		for (int i = 0; i < graph.at(vertex).size(); i++) {
			if (residual[vertex][graph.at(vertex).at(i)] > 0) { // 그 경로로 이동 가능할 때 (남은 용량이 0 이상이다!)
				path.push_back(graph.at(vertex).at(i));
				if (Search_Path(graph.at(vertex).at(i))) return true; // 그 정점을 파고 들었을 때 도착지에 도달 가능하면,
				path.pop_back(); // 도달 불가능하면 그 경로 폐쇄
			}
		}
		return false; // 특정 정점에서 갈 수 있는 모든 경로로 이동했을 때 끝에 도달 불가능하면,
	}
	int max = residual[0][path.at(0)]; // 0번 정점에서 첫 번째 경로로 갈 때의 남은 용량
	for (int i = 1; i < path.size(); i++) {
		if (max > residual[path.at(i - 1)][path.at(i)])
			max = residual[path.at(i - 1)][path.at(i)];
		/* 경로를 지나는 간선 중에 가장 추가 가능 용량이 작은 것 선택 */
	}
	path_w = max; // 그 경로의 유량 저장 후 함수 종료
	return true; // 도착지에 도달했다면,
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