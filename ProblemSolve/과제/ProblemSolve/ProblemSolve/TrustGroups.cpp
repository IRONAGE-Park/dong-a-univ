#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<vector>
#include<stack>

using namespace std;

typedef struct {
	string name; // 사람의 번호
	int idx; // 그 사람의 행렬 인덱스
} Data; // 이름 리스트 구조체 정의

typedef struct {
	string name; // 사람의 번호
	vector<int> trust; // 신뢰하는 사람들의 인덱스
	bool visit; // 방문했는지 안했는지.
} Person; // 인접행렬 구조체 정의

bool cmp(Data x, Data y) {
	return x.name < y.name;
}

vector<Data> list; // 이름 리스트
vector<Person> graph, r_graph; // 정방향 그래프와 역방향 그래프
stack<int> st; // SCC Algorithm에서 이용할 스택

int name_Search(int first, int last, string data) { // 그 이름에 해당하는 인덱스 찾기(이진검색)
	while (first <= last) {
		int mid = (first + last) / 2; // 중간지점
		if (list[mid].name == data) return list[mid].idx; // 중간지점이 찾는 데이터와 같다. => 인덱스 반환
		else if (list[mid].name > data) last = mid - 1; // 중간지점이 찾는 데이터보다 크다 => 중간지점의 왼쪽 탐색
		else first = mid + 1; // 중간지점이 찾는 데이터보다 작다 => 중간지점의 오른쪽 탐색
	}
	return -1; // 데이터가 없음
}

void DFS(int index) { // Depth First Search Algorithm -> 정방향 그래프 순회
	graph[index].visit = true; // 정점에 방문했음을 알림.
	for (int i = 0; i < graph[index].trust.size(); i++) {
		int next = graph[index].trust[i];
		if (graph[next].visit) continue;
		DFS(next);
	}
	st.push(index);
}

void r_DFS(int index) { // Depth First Search Algorithm -> 역방향 그래프 순회
	r_graph[index].visit = true; // 정점에 방문했음을 알림.
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
	/* 모든 정점을 대상으로 DFS */
	while (st.size()) {
		int top = st.top();
		st.pop();
		if (r_graph[top].visit) continue;
		r_DFS(top);
		group++;
	}
	/* 스택의 있는 요소를 Pop하여 역방향 그래프 DFS */
	return group;
}

int main() {
	ifstream inp("TrustGroups.inp");
	ofstream out("TrustGroups.out");

	string L;
	while (true) {
		int P = -1, T = -1; // 사람 수 P와 사람끼리의 신뢰도 수 T.
		inp >> P >> T;
		getline(inp, L); // 두 정수를 받은 뒤에 한 칸 띄워줌
		if (!P && !T) break;

		list.resize(P); graph.resize(P); r_graph.resize(P); // 사이즈 할당 받음

		for (int i = 0; i < P; i++) {
			getline(inp, graph[i].name);
			r_graph[i].name = graph[i].name;
			list[i].name = graph[i].name;
			list[i].idx = i;
		} // 이름 입력
		sort(list.begin(), list.end(), cmp); // 이름 순 정렬
		/* 그래프의 형태 구축 */
		while (T--) {
			string opt, opr;
			int optIndex, oprIndex;
			/* opt = 신뢰하는사람, opr = 신뢰받는사람. */
			getline(inp, opt); getline(inp, opr);
			optIndex = name_Search(0, P - 1, opt); oprIndex = name_Search(0, P - 1, opr);
			/* 신뢰도 관계 입력받고 인덱스 찾음 */
			graph[optIndex].trust.push_back(oprIndex); // 정방향 그래프에 간선 추가.
			r_graph[oprIndex].trust.push_back(optIndex); // 역방향 그래프에 간선 추가.
		}
		/* 그래프 완성 */
		int answer = SCC(P); // 안정적인 그룹 수
		out << answer << '\n'; // 출력
		
		list.clear(); graph.clear(); r_graph.clear();
		/* 초기화 */
	}
	inp.close();
	out.close();
	return 0;
}