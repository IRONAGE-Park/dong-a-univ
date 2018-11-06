#include<iostream>
#include<fstream>

using namespace std;

typedef struct Point {
	int x, y; // (x, y)
}Point;

typedef struct Line {
	Point p1, p2; // ���� �� �� ��
}Line;
/* ���� ������ ����ü ���� */

int n; // ������ Ȯ���� ���� ����.
Line poly[4];

int Direction(Point A, Point B, Point C) { // �� ���� ����� ��ġ ����
	int dxAB, dxAC, dyAB, dyAC, dir;
	dxAB = B.x - A.x;
	dyAB = B.y - A.y;
	dxAC = C.x - A.x;
	dyAC = C.y - A.y;
	if (dxAB * dyAC < dyAB * dxAC) dir = 1;       // �ð����
	if (dxAB * dyAC > dyAB * dxAC) dir = -1;      // �ݽð����
	if (dxAB * dyAC == dyAB * dxAC) {     // ������ �� �ִ� ���
		if (dxAB == 0 && dyAB == 0) dir = 0;  // A = B 
		else if ((dxAB * dxAC < 0) || (dyAB * dyAC < 0)) dir = -1;   // A�� ���
		else if (dxAB * dxAB + dyAB * dyAB >= dxAC * dxAC + dyAC * dyAC) dir = 0;     // C�� ���
		else dir = 1;  // B�� ���
	}
	return dir;
}

int Intersection(Line AB, Line CD) { // �� ���� ���� ���� (AB, CD�� ���� �����ϸ� TRUE, �ƴϸ� FALSE)
	
	if ((Direction(AB.p1, AB.p2, CD.p1) * Direction(AB.p1, AB.p2, CD.p2) == 0) &&
		(Direction(CD.p1, CD.p2, AB.p1) * Direction(CD.p1, CD.p2, AB.p2) == 0)) {
		return -1;
	}
	else if((Direction(AB.p1, AB.p2, CD.p1) * Direction(AB.p1, AB.p2, CD.p2) <= 0) &&
		(Direction(CD.p1, CD.p2, AB.p1) * Direction(CD.p1, CD.p2, AB.p2) <= 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

int Inter_Count(Line L) {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int k = Intersection(poly[i], L);
		if (k == -1) {
			cnt = 4;
			break;
		}
		else if (k == 1) {
			cnt++;
		}
	}
	return cnt;
}

int main() {
	ifstream inp("Intersection.inp");
	ofstream out("Intersection.out");
	Line input; // �Է� ��

	inp >> n;
	while (n--) {
		inp >> input.p1.x >> input.p1.y >> input.p2.x >> input.p2.y;
		/* �簢�� ���� �Է� ���� */
		poly[0] = { input.p1.x, input.p1.y, input.p2.x, input.p1.y };
		poly[1] = { input.p2.x, input.p1.y, input.p2.x, input.p2.y };
		poly[2] = { input.p2.x, input.p2.y, input.p1.x, input.p2.y };
		poly[3] = { input.p1.x, input.p2.y, input.p1.x, input.p1.y };
		/* �簢�� ���� */
		inp >> input.p1.x >> input.p1.y >> input.p2.x >> input.p2.y;
		out << Inter_Count(input) << '\n';
	}
	inp.close();
	out.close();
	return 0;
}