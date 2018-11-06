#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>

using namespace std;

typedef struct Dict { // 사전 구조체 정의
	string word; // 단어
	vector<int> list; // Doublet 리스트
	bool check;
}Dict;

typedef struct Route { // Queue에서 사용할 구조체.
	int index;
	vector<string> r;
}Route;

vector<string> r, route;
deque<Route> BFSQueue;
Dict dict[30000];
int n;

bool CheckDoublet(string str1, string str2) { // Doublet 확인
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
void DFS(Dict *d, string item) { // DFS 탐색
	if (!d->check) {
		d->check = true;
		r.push_back(d->word);

		if (d->word.compare(item) == 0) { // 만약 DFS로 route를 찾으면
			if (route.empty()) { // 그때 미리 생성된 route가 없으면
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
	while (!BFSQueue.empty()) { // Queue가 비어있지 않을동안.
		Route now = BFSQueue.front();
		BFSQueue.pop_front();
		if (!dict[now.index].check) { // 방문하지않았으면.
			dict[now.index].check = true;
			now.r.push_back(dict[now.index].word); // 이름을 루트에 올림.
			if (dict[now.index].word.compare(item) == 0) { // 만약 그 노드가 도착점이면.
				route = now.r;
				return; // 종료.
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
	MakeGraph(); // graph 생성

	while (true) { // testcase
		string depart, arrive;
		inp >> depart >> arrive;
		if (depart.length() == 0) break;
		for (int i = 0; i < n; i++) {
			if (dict[i].word.compare(depart) == 0) { // 시작점이 같으면.
				Route start;
				start.index = i;
				BFSQueue.push_back(start); // 시작점 큐에 삽입.
				BFS(arrive);
				break;
			}
		}
		if (route.empty()) { // 만약 탐색된 경로가 없으면.
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