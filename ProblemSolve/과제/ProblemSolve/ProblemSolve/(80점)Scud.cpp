#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<algorithm>
#include<cstring>
#define MAX 10000

using namespace std;

struct Point {
	int x, y; // 실제 위치
	int p, q; // 기준점으로부터의 상대 위치
	// p, q 값을 기준으로 정렬하기 위한 관계연산자
	bool operator <(const Point& O) {
		if (1LL * q*O.p != 1LL * p*O.q) return 1LL * q*O.p < 1LL * p*O.q;
		if (y != O.y) return y < O.y;
		return x < O.x;
	}
};

int areaTriangle(Point p1, Point p2, Point p3) { // p1 = 확인할 점, p2 = 다각형 일부 1, p3 = 다각형의 일부 2
	return (p1.x * p2.y) + (p2.x * p3.y) + (p3.x * p1.y) - (p1.x * p3.y) - (p3.x * p2.y) - (p2.x * p1.y);
}
double dabs(double n) {
	if (n > 0) return n;
	return n * -1;
}

class Kingdom {
public:
	bool Missile;
	vector<Point> p;
	Kingdom() { Missile = false; }
	Kingdom(vector<Point> p) { this->p = p; }
	double getArea() { // 그 왕국의 넓이
		double area = 0.0;
		vector<Point> pnt = p;
		pnt.push_back(pnt.at(0));
		for (int i = 1; i < pnt.size(); i++) {
			area += (pnt.at(i - 1).x * pnt.at(i).y) - (pnt.at(i).x * pnt.at(i - 1).y);
		}
		return dabs(area * 0.5);
	}
	bool interArea(Point B) { // 어떤 점이 그 왕국 내부에 존재하는가
		// crosses는 점q와 오른쪽 반직선과 다각형과의 교점의 개수
		int crosses = 0;
		for (int i = 0; i < p.size(); i++) {
			int j = (i + 1) % p.size();
			//점 B가 선분 (p[i], p[j])의 y좌표 사이에 있음
			if ((p[i].y >= B.y) != (p[j].y >= B.y)) {
				//atX는 점 B를 지나는 수평선과 선분 (p[i], p[j])의 교점
				double atX = (p[j].x - p[i].x)*(B.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
				//atX가 오른쪽 반직선과의 교점이 맞으면 교점의 개수를 증가시킨다.
				if (B.x < atX)
					crosses++;
			}
		}
		return crosses % 2 > 0;
	}
};

// 벡터 AB와 벡터 AC의 CW/CCW
long long ccw(const Point& A, const Point& B, const Point& C) {
	return 1LL * (B.x - A.x)*(C.y - A.y) - 1LL * (B.y - A.y)*(C.x - A.x);
}

vector<Point> Convexhull(Point p[], int N) {
	// 점들을 y좌표 -> x좌표 순으로 정렬: 0번 점이 제일 아래 제일 왼쪽
	sort(p, p + N);
	for (int i = 1; i<N; i++) {
		p[i].p = p[i].x - p[0].x;
		p[i].q = p[i].y - p[0].y;
	}
	// 0번을 제외한 점들을 반시계 방향으로 정렬
	sort(p + 1, p + N);

	stack<int> S;
	// 스택에 처음 2개의 점을 넣음
	S.push(0);
	S.push(1);
	int next = 2;
	// 모든 점을 훑음
	while (next < N) {
		// 스택에 2개 이상의 점이 남아있는 한...
		while (S.size() >= 2) {
			int first, second;
			first = S.top();
			S.pop();
			second = S.top();
			// 스택 최상단 점 2개와 다음 점의 관계가 CCW일 때까지 스택 pop
			if (ccw(p[second], p[first], p[next]) > 0) {
				S.push(first);
				break;
			}
		}
		// 다음 점을 스택에 넣음
		S.push(next++);
	}
	// 이제 스택에 컨벡스 헐 정점들이 순서대로 쌓여 있음
	vector<Point> v;
	while (S.size()) {
		Point pnt; // 국경을 이루는 점
		pnt = p[S.top()];
		v.push_back(pnt);
		S.pop();
	}
	return v;
}

int main() {
	ifstream inp("Scud.inp");
	ofstream out("Scud.out");

	Point p[MAX];
	vector<Kingdom> kingdom;
	int N;
	while (true) {
		inp >> N;
		if (N == -1) break; // 마지막 input
		for (int i = 0; i < N; i++) {
			inp >> p[i].x >> p[i].y; // 그 왕국의 좌표를 입력 받고
			p[i].p = 1, p[i].q = 0;
		}
		Kingdom k(Convexhull(p, N)); // Convexhull을 통해 왕국의 경계 좌표 얻어서
		kingdom.push_back(k); // kingdom 리스트에 추가.
		memset(p, 0, sizeof(p));
	}
	double area = 0;
	while (true) {
		Point m;
		m.x = -1, m.y = -1;
		inp >> m.x >> m.y;
		if (m.x == -1 && m.y == -1) {
			for (int i = 0; i < kingdom.size(); i++) {
				if (kingdom.at(i).Missile) {
					area += kingdom.at(i).getArea();
				}
			}
			break;
		}
		for (int i = 0; i < kingdom.size(); i++) {
			if (kingdom.at(i).interArea(m)) { // 점이 그 왕국 안에 포함되면
				kingdom.at(i).Missile = true;
				break;
			}
		}
	}
	out << fixed;
	out.precision(2);
	out << area;
	/* OUTPUT */
	inp.close();
	out.close();
	return 0;
}