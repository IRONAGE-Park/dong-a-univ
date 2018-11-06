#include<iostream>
#include<fstream>

const int MAX = 10000, eta = 0.0001;

using namespace std;

typedef struct { int x, y; } Point; // 점 구조체 선언.

Point polygon[MAX]; // 다각형.
int n; // 다각형을 이루는 정점의 갯수.

double dabs(double n) {
	if (n > 0) return n;
	else return n * -1;
}

bool InterPolygon(Point point) { // 특정 점이 다각형 내부에 있는지 Check하는 함수.
	int cross = 0;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		if ((polygon[i].y > point.y != polygon[j].y > point.y)) {
			/* 직선의 두 점의 y좌표 중 하나만 Check할 점의 y좌표보다 크고, 나머지 하나는 y좌표보다 작음 == Check할 점이 두 직선 사이에 존재함. */
			if (polygon[i].x == point.x && polygon[j].x == point.x) {
				/* 직선의 두 점의 x좌표와 Check할 점의 x좌표가 같음 == 선과 점이 같은 수직선에 존재. */
				return true; // 다각형 선에 걸친다.
			}
			double line = (polygon[j].x - polygon[i].x)*(point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x;
			if (line > point.x) // 그 점으로 부터 연장된 수평선과 다각형을 이루는 직선의 교점이 그 점의 오른쪽에 있을 경우,
				cross++; // 교차하는 선 하나 추가.
			else if (line == point.x)
				return true;
		}
		else if (polygon[i].y == point.y && polygon[j].y == point.y) {
			/* 직선의 두 점의 y좌표와 Check할 점의 y좌표가 같음 == 선과 점이 같은 수평선에 존재. */
			if (polygon[i].x > point.x != polygon[j].x > point.x) {
				/* 같은 수평선인데 두 직선이 만드는 x좌표 사이에 Check할 점이 존재 */
				return true; // 다각형 선에 걸친다.
			}
		}
	}
	return cross % 2; // cross가 홀수 = 다각형 내부에 점이 존재한다. || cross가 짝수 = 다각형 외부에 점이 존재한다.
}

bool InterPoly(Point point) { // 특정 점이 다각형 내부에 있는지 Check하는 함수.
	int cross = 0;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		if (point.x == polygon[i].x && point.y == polygon[i].y)
			return true; // 다각형의 꼭지점에 걸침.
		else if (polygon[i].y > point.y != polygon[j].y > point.y) {
			/* 직선의 두 점의 y좌표 중 하나만 Check할 점의 y좌표보다 크고, 나머지 하나는 y좌표보다 작음 == Check할 점이 두 직선 사이에 존재함. */
			double line = (polygon[j].x - polygon[i].x)*(point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x;
			if (line > point.x) // 그 점으로 부터 연장된 수평선과 다각형을 이루는 직선의 교점이 그 점의 오른쪽에 있을 경우,
				cross++; // 교차하는 선 하나 추가.
			if (dabs(line - point.x) <= eta) return true; // 다각형의 선에 걸침.
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

	int testcase, answer; // 검사할 Testcase의 갯수와 답안.
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