#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<algorithm>
#define MAX 10000

using namespace std;

typedef struct Point {
	int x, y; // ���� ��ġ
	int p, q; // ���������κ����� ��� ��ġ
	bool in_P; // P�� ���ϴ��� ������ �ʴ���. 
	bool operator <(Point O) { // p, q ���� �������� �����ϱ� ���� ���迬����
		if (1LL * q*O.p != 1LL * p*O.q) return 1LL * q*O.p < 1LL * p*O.q;
		if (y != O.y) return y > O.y;
		return x < O.x;
	}
	bool operator ==(Point O) {
		return x == O.x && y == O.y;
	}
}Point;

double Poly_Area(vector<Point> poly) { // �ٰ����� ���� ����
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

// ���� AB�� ���� AC�� CW/CCW	
long long ccw(Point A, Point B, Point C) {
	return 1LL * (B.x - A.x)*(C.y - A.y) - 1LL * (B.y - A.y)*(C.x - A.x);
}

vector<Point> Convexhull(Point p[MAX], int N) {
	// ������ y��ǥ -> x��ǥ ������ ����: 0�� ���� ���� �Ʒ� ���� ����
	sort(p, p + N);
	for (int i = 1; i<N; i++) {
		p[i].p = p[i].x - p[0].x;
		p[i].q = p[i].y - p[0].y;
	}
	// 0���� ������ ������ �ݽð� �������� ����
	sort(p + 1, p + N);

	stack<int> S;
	// ���ÿ� ó�� 2���� ���� ����
	S.push(0);
	S.push(1);
	int next = 2;
	// ��� ���� ����
	while (next < N) {
		// ���ÿ� 2�� �̻��� ���� �����ִ� ��...
		while (S.size() >= 2) {
			int first, second;
			first = S.top();
			S.pop();
			second = S.top();
			// ���� �ֻ�� �� 2���� ���� ���� ���谡 CCW�� ������ ���� pop
			if (ccw(p[second], p[first], p[next]) >= 0) {
				S.push(first);
				break;
			}
		}
		// ���� ���� ���ÿ� ����
		S.push(next++);
	}
	// ���� ���ÿ� ������ �� �������� ������� �׿� ����
	vector<Point> v;
	while (S.size()) {
		Point pnt; // ������ �̷�� ��
		pnt = p[S.top()];
		v.push_back(pnt);
		S.pop();
	}
	return v;
}

int input_Point(Point p[], vector<Point> P, vector<Point> Q) { // �迭 p���ٰ� ���� ���� ��� �������. => ��� ����
	int i, pSize = P.size(), qSize = Q.size();
	for (i = 0; i < pSize; i++) p[i] = P[i], p[i].p = 1, p[i].q = 0;
	for (int j = 0; j < qSize; i++, j++) p[i] = Q[j], p[i].p = 1, p[i].q = 0;
	return i;
}

vector<Point> clockwise(vector<Point> P, vector<Point> Q, Point p1, Point p2, Point q1, Point q2) {
	int start_p, start_q, i;
	for (start_p = 0; start_p < P.size(); start_p++) {
		if (P[start_p] == p1) break;
	} // ������ p1���� ���߱�.
	for (start_q = 0; start_q < Q.size(); start_q++) {
		if (Q[start_q] == q2) break;
	} // ������ q1���� ���߱�.
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
	} // ������ p1���� ���߱�.
	for (start_q = 0; start_q < Q.size(); start_q++) {
		if (Q[start_q] == q2) break;
	} // ������ q1���� ���߱�.
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
		P.resize(n); // vector P �籸��
		for (int i = 0; i < n; i++) inp >> P[i].x >> P[i].y, P[i].in_P = true;
		inp >> n;
		Q.resize(n); // vector Q �籸��
		for (int i = 0; i < n; i++) inp >> Q[i].x >> Q[i].y, Q[i].in_P = false;
		/* �ٰ��� P�� Q�Է� ���� */
		pSize = input_Point(p, P, Q); // �迭 p���ٰ� vector P, Q�� �������.
		convex = Convexhull(p, P.size() + Q.size()); // ��ü ���� convexhull.
		Point PP[2], QQ[2]; // P�� Q�� ����
		int pqc = 0;
		for (int i = 0; i < convex.size(); i++) {
			int j = (i + 1) % convex.size();
			if (convex[i].in_P != convex[j].in_P) { // convexhull�� �̷�� �� ���� �ٸ� �ٰ����̸�.
				if (convex[i].in_P) { // i��° ������ P�� ���ϸ�,
					PP[pqc] = convex[i], QQ[pqc] = convex[j];
				}
				else { // i��° ������ Q�� ���ϸ�,
					PP[pqc] = convex[j], QQ[pqc] = convex[i];
				}
				pqc++;
				if (pqc == 2) break;
			}
		} // convexhull���� P�� Q�� ���� ���ϱ�.

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