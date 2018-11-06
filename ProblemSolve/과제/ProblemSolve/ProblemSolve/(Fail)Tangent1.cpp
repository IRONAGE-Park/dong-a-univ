#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<algorithm>
#define MAX 10000

using namespace std;

typedef struct Point {
	int x, y; // 실제 위치
	int p, q; // 기준점으로부터의 상대 위치
	bool in_P; // P에 속하는지 속하지 않는지. 
	bool operator <(Point O) { // p, q 값을 기준으로 정렬하기 위한 관계연산자
		if (1LL * q*O.p != 1LL * p*O.q) return 1LL * q*O.p < 1LL * p*O.q;
		if (y != O.y) return y > O.y;
		return x < O.x;
	}
	bool operator ==(Point O) {
		return x == O.x && y == O.y;
	}
}Point;

double Poly_Area(vector<Point> poly) { // 다각형의 넓이 구함
	double area = 0.0;
	for (int i = 0; i < poly.size(); i++) {
		int j = (i + 1) % poly.size();
		area += (poly[i].x * poly[j].y) - (poly[j].x * poly[i].y);
	}
	return area;
}

double dabs(double n) {
	if (n > 0) return n;
	return n * -1;
}

// 벡터 AB와 벡터 AC의 CW/CCW	
long long ccw(Point A, Point B, Point C) {
	return 1LL * (B.x - A.x)*(C.y - A.y) - 1LL * (B.y - A.y)*(C.x - A.x);
}

vector<Point> Convexhull(Point p[MAX], int N) {
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
			if (ccw(p[second], p[first], p[next]) >= 0) {
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

int input_Point(Point p[], vector<Point> P, vector<Point> Q) { // 배열 p에다가 정점 정보 모두 집어넣음. => 모든 정점
	int i, pSize = P.size(), qSize = Q.size();
	for (i = 0; i < pSize; i++) p[i] = P[i], p[i].p = 1, p[i].q = 0;
	for (int j = 0; j < qSize; i++, j++) p[i] = Q[j], p[i].p = 1, p[i].q = 0;
	return i;
}

vector<Point> clockwise(vector<Point> P, vector<Point> Q, Point p1, Point p2, Point q1, Point q2) {
	int start_p, start_q, i;
	for (start_p = 0; start_p < P.size(); start_p++) {
		if (P[start_p] == p1) break;
	} // 시작점 p1으로 맞추기.
	for (start_q = 0; start_q < Q.size(); start_q++) {
		if (Q[start_q] == q2) break;
	} // 시작점 q1으로 맞추기.
	vector<Point> newPoly;
	for (i = start_p; ; i--) {
		if (i == -1) i = P.size() - 1;
		newPoly.push_back(P[i]);
		if (P[i] == p2) break;
	}
	for (i = start_q; ; i--) {
		if (i == -1) i = Q.size() - 1;
		newPoly.push_back(Q[i]);
		if (Q[i] == q1) break;
	}
	return newPoly;
}

vector<Point> unclockwise(vector<Point> P, vector<Point> Q, Point p1, Point p2, Point q1, Point q2) {
	int start_p, start_q, i;
	for (start_p = 0; start_p < P.size(); start_p++) {
		if (P[start_p] == p1) break;
	} // 시작점 p1으로 맞추기.
	for (start_q = 0; start_q < Q.size(); start_q++) {
		if (Q[start_q] == q2) break;
	} // 시작점 q1으로 맞추기.
	vector<Point> newPoly;
	for (i = start_p; ; i++) {
		if (i == P.size()) i = 0;
		newPoly.push_back(P[i]);
		if (P[i] == p2) break;
	}
	for (i = start_q; ; i++) {
		if (i == Q.size()) i = 0;
		newPoly.push_back(Q[i]);
		if (Q[i] == q1) break;
	}
	return newPoly;
}

int main() {
	ifstream inp("Tangent1.inp");
	ofstream out("Tangent1.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n, pSize;
		inp >> n;
		vector<Point> P, Q, convex;
		Point p[MAX];
		P.resize(n); // vector P 재구성
		for (int i = 0; i < n; i++) inp >> P[i].x >> P[i].y, P[i].in_P = true;
		inp >> n;
		Q.resize(n); // vector Q 재구성
		for (int i = 0; i < n; i++) inp >> Q[i].x >> Q[i].y, Q[i].in_P = false;
		/* 다각형 P와 Q입력 받음 */
		pSize = input_Point(p, P, Q); // 배열 p에다가 vector P, Q를 집어넣음.
		convex = Convexhull(p, P.size() + Q.size()); // 전체 정점 convexhull.
		Point PP[2], QQ[2]; // P와 Q의 교점
		int pqc = 0;
		for (int i = 0; i < convex.size(); i++) {
			int j = (i + 1) % convex.size();
			if (convex[i].in_P != convex[j].in_P) { // convexhull을 이루는 두 점이 다른 다각형이면.
				if (convex[i].in_P) { // i번째 정점이 P에 속하면,
					PP[pqc] = convex[i], QQ[pqc] = convex[j];
				}
				else { // i번째 정점이 Q에 속하면,
					PP[pqc] = convex[j], QQ[pqc] = convex[i];
				}
				pqc++;
				if (pqc == 2) break;
			}
		} // convexhull에서 P와 Q의 교점 구하기.

		vector<Point> clock, unclock;
		clock = clockwise(P, Q, PP[0], PP[1], QQ[0], QQ[1]);
		unclock = unclockwise(P, Q, PP[0], PP[1], QQ[0], QQ[1]);
		double clockArea, unclockArea;
		clockArea = dabs(Poly_Area(clock)) / 2;
		unclockArea = dabs(Poly_Area(unclock)) / 2;
		out << fixed;
		out.precision(1);
		out << (clockArea > unclockArea ? unclockArea : clockArea) << '\n';
	}
	inp.close();
	out.close();
	return 0;
}