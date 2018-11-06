#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<algorithm>
#include<cstring>
#define MAX 10000

using namespace std;

struct Point {
	int x, y; // ���� ��ġ
	int p, q; // ���������κ����� ��� ��ġ
	// p, q ���� �������� �����ϱ� ���� ���迬����
	bool operator <(const Point& O) {
		if (1LL * q*O.p != 1LL * p*O.q) return 1LL * q*O.p < 1LL * p*O.q;
		if (y != O.y) return y < O.y;
		return x < O.x;
	}
};

int areaTriangle(Point p1, Point p2, Point p3) { // p1 = Ȯ���� ��, p2 = �ٰ��� �Ϻ� 1, p3 = �ٰ����� �Ϻ� 2
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
	double getArea() { // �� �ձ��� ����
		double area = 0.0;
		vector<Point> pnt = p;
		pnt.push_back(pnt.at(0));
		for (int i = 1; i < pnt.size(); i++) {
			area += (pnt.at(i - 1).x * pnt.at(i).y) - (pnt.at(i).x * pnt.at(i - 1).y);
		}
		return dabs(area * 0.5);
	}
	bool interArea(Point B) { // � ���� �� �ձ� ���ο� �����ϴ°�
		// crosses�� ��q�� ������ �������� �ٰ������� ������ ����
		int crosses = 0;
		for (int i = 0; i < p.size(); i++) {
			int j = (i + 1) % p.size();
			//�� B�� ���� (p[i], p[j])�� y��ǥ ���̿� ����
			if ((p[i].y >= B.y) != (p[j].y >= B.y)) {
				//atX�� �� B�� ������ ���򼱰� ���� (p[i], p[j])�� ����
				double atX = (p[j].x - p[i].x)*(B.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
				//atX�� ������ ���������� ������ ������ ������ ������ ������Ų��.
				if (B.x < atX)
					crosses++;
			}
		}
		return crosses % 2 > 0;
	}
};

// ���� AB�� ���� AC�� CW/CCW
long long ccw(const Point& A, const Point& B, const Point& C) {
	return 1LL * (B.x - A.x)*(C.y - A.y) - 1LL * (B.y - A.y)*(C.x - A.x);
}

vector<Point> Convexhull(Point p[], int N) {
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
			if (ccw(p[second], p[first], p[next]) > 0) {
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

int main() {
	ifstream inp("Scud.inp");
	ofstream out("Scud.out");

	Point p[MAX];
	vector<Kingdom> kingdom;
	int N;
	while (true) {
		inp >> N;
		if (N == -1) break; // ������ input
		for (int i = 0; i < N; i++) {
			inp >> p[i].x >> p[i].y; // �� �ձ��� ��ǥ�� �Է� �ް�
			p[i].p = 1, p[i].q = 0;
		}
		Kingdom k(Convexhull(p, N)); // Convexhull�� ���� �ձ��� ��� ��ǥ ��
		kingdom.push_back(k); // kingdom ����Ʈ�� �߰�.
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
			if (kingdom.at(i).interArea(m)) { // ���� �� �ձ� �ȿ� ���ԵǸ�
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