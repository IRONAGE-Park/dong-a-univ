#include<iostream>
#include<fstream>
#include<queue>
#include<cstring>
#define MAX 100000000

using namespace std;

typedef struct Build {
	int x;
	int index;
	int height;
	bool state; // true = start, false = end
}Build;
typedef struct Current {
	int x;
	int index;
	int height;
}Current;
bool operator<(Build a, Build b) {
	return a.x > b.x;
}
bool operator<(Current a, Current b) {
	return a.height < b.height;
}

priority_queue<Build> ready;
priority_queue<Current> sweep;

bool endIdx[MAX];

int main() {
	ifstream inp("Skyline.inp");
	ofstream out("Skyline.out");

	int n = 0, idx = 0;
	while (true) {
		int start = -1, height = -1, end = -1;
		inp >> start >> height >> end;

		if (!start && !height && !end) { // 그 Testcase에 대하여 Input Data가 전부 들어오면 => Start to Building Scan
			out << "Test Case #" << ++n << " :";
			long long int area = 0; // 건물들 넓이
			int last_x = 0, last_height = 0; // 마지막 x축 위치와 마지막 높이

			while (ready.size() != 0) {
				if (ready.top().state) { // 시작 점이 들어오면.
					if (last_height <= ready.top().height) { // 지금 높이가 더 높으면
						area += last_height * (ready.top().x - last_x); // 마지막 저장한 x부터 그 때까지 건물 넓이 저장
						last_height = ready.top().height; // 현재 건물의 높이 저장
						last_x = ready.top().x; // 마지막으로 계산한 x축 위치 저장
					}
					sweep.push({ ready.top().x, ready.top().index, ready.top().height }); // SweepLine에 push
				}
				else { // 끝 점이 들어오면.
					endIdx[ready.top().index] = true; // 그 정보를 사용했다는 표시
					if (last_height == ready.top().height) { // 만약 들어온 끝 점이 최고높이이면
						area += last_height * (ready.top().x - last_x); // 마지막 저장한 x부터 그 때까지 건물 넓이 저장
						last_x = ready.top().x; // 마지막으로 계산한 x축 위치 저장
					}
					while (!sweep.empty()) {
						if (!endIdx[sweep.top().index]) { // 만약 아직 sweep에 끝나지않은 사각형이 있다면.
							last_height = sweep.top().height;
							break;
						}
						else { // 사각형이 이미 종료된 상태라면 sweep에서 빼냄
							sweep.pop();
						}
					}
					if (sweep.empty()) {
						out << " " << area; // 출력해주고
						area = 0, last_height = 0; // 높이는 0, 넓이는 0
					}
				}
				ready.pop();
			}
			out << '\n';
			idx = 0;
			memset(endIdx, false, sizeof(endIdx));
			continue;
		}
		// queue에 input
		if (start == -1) break;
		ready.push({ start, idx, height, true }); // 시작점
		ready.push({ end, idx++, height, false }); // 끝점
	}
	inp.close();
	out.close();
	return 0;
}

/*
while (ready.size() != 0) {
	if (ready.top().state) { // 시작 점이 들어왔을때.
		if (last_height < ready.top().height) { // 지금 높이가 더 높으면.
			area += last_height * (ready.top().x - last_x);
			last_height = ready.top().height;
			last_x = ready.top().x;
		}
		sweep.push({ ready.top().x, ready.top().index, ready.top().height }); // SweepLine에 push;
	}
	else { // 끝 점이 들어왔을 때
		endIdx[ready.top().index] = true; // 종료된 인덱스 체크
		if (last_height == ready.top().height) { // 마지막 높이와 종료되는 건물의 높이가 같으면
			if (sweep.top().index == ready.top().index) { // 인덱스까지 같으면 = 같은 건물이면 ==> area에 더함
				area += last_height * (ready.top().x - last_x);
				last_x = ready.top().x;
				while (endIdx[sweep.top().index]) {
					sweep.pop();
				}
				if (sweep.size() == 1) {
					out << " " << area;
					area = 0;
					last_height = 0;
				}
				else last_height = sweep.top().height;
			}
		}
	}
	ready.pop();
}
*/