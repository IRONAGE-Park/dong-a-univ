#include<iostream>
#include<fstream>

const int MAX = 10000, eta = 0.0001;

using namespace std;

typedef struct { int x, y; } Point; // �� ����ü ����.

Point polygon[MAX]; // �ٰ���.
int n; // �ٰ����� �̷�� ������ ����.

double dabs(double n) {
	if (n > 0) return n;
	else return n * -1;
}

bool InterPolygon(Point point) { // Ư�� ���� �ٰ��� ���ο� �ִ��� Check�ϴ� �Լ�.
	int cross = 0;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		if ((polygon[i].y > point.y != polygon[j].y > point.y)) {
			/* ������ �� ���� y��ǥ �� �ϳ��� Check�� ���� y��ǥ���� ũ��, ������ �ϳ��� y��ǥ���� ���� == Check�� ���� �� ���� ���̿� ������. */
			if (polygon[i].x == point.x && polygon[j].x == point.x) {
				/* ������ �� ���� x��ǥ�� Check�� ���� x��ǥ�� ���� == ���� ���� ���� �������� ����. */
				return true; // �ٰ��� ���� ��ģ��.
			}
			double line = (polygon[j].x - polygon[i].x)*(point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x;
			if (line > point.x) // �� ������ ���� ����� ���򼱰� �ٰ����� �̷�� ������ ������ �� ���� �����ʿ� ���� ���,
				cross++; // �����ϴ� �� �ϳ� �߰�.
			else if (line == point.x)
				return true;
		}
		else if (polygon[i].y == point.y && polygon[j].y == point.y) {
			/* ������ �� ���� y��ǥ�� Check�� ���� y��ǥ�� ���� == ���� ���� ���� ���򼱿� ����. */
			if (polygon[i].x > point.x != polygon[j].x > point.x) {
				/* ���� �����ε� �� ������ ����� x��ǥ ���̿� Check�� ���� ���� */
				return true; // �ٰ��� ���� ��ģ��.
			}
		}
	}
	return cross % 2; // cross�� Ȧ�� = �ٰ��� ���ο� ���� �����Ѵ�. || cross�� ¦�� = �ٰ��� �ܺο� ���� �����Ѵ�.
}

bool InterPoly(Point point) { // Ư�� ���� �ٰ��� ���ο� �ִ��� Check�ϴ� �Լ�.
	int cross = 0;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		if (point.x == polygon[i].x && point.y == polygon[i].y)
			return true; // �ٰ����� �������� ��ħ.
		else if (polygon[i].y > point.y != polygon[j].y > point.y) {
			/* ������ �� ���� y��ǥ �� �ϳ��� Check�� ���� y��ǥ���� ũ��, ������ �ϳ��� y��ǥ���� ���� == Check�� ���� �� ���� ���̿� ������. */
			double line = (polygon[j].x - polygon[i].x)*(point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x;
			if (line > point.x) // �� ������ ���� ����� ���򼱰� �ٰ����� �̷�� ������ ������ �� ���� �����ʿ� ���� ���,
				cross++; // �����ϴ� �� �ϳ� �߰�.
			if (dabs(line - point.x) <= eta) return true; // �ٰ����� ���� ��ħ.
		}
	}
	return cross % 2;
}

int main() {
	ifstream inp("Mid-term5.inp");
	ofstream out("Mid-term5.out");

	inp >> n;
	for (int i = 0; i < n; i++) inp >> polygon[i].x >> polygon[i].y;
	/* Input Data. */

	int testcase, answer; // �˻��� Testcase�� ������ ���.
	inp >> testcase;

	while (testcase--) {
		Point point;
		inp >> point.x >> point.y;
		if (InterPoly(point)) answer = 1;
		else answer = 0;
		out << answer << '\n';
	}
	/* Output Answer. */

	inp.close();
	out.close();
	return 0;
}