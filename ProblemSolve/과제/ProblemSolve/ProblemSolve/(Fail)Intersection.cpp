#include<iostream>
#include<fstream>

using namespace std;

typedef struct Point {
	int x, y; // (x, y)
}Point;

typedef struct Line {
	Point p1, p2; // 선의 양 끝 점
}Line;
/* 선에 관련한 구조체 선언 */

int n; // 교점을 확인할 선의 갯수.
Line poly[4];

int Direction(Point A, Point B, Point C) { // 세 점의 상대적 위치 결정
	int dxAB, dxAC, dyAB, dyAC, dir;
	dxAB = B.x - A.x;
	dyAB = B.y - A.y;
	dxAC = C.x - A.x;
	dyAC = C.y - A.y;
	if (dxAB * dyAC < dyAB * dxAC) dir = 1;       // 시계방향
	if (dxAB * dyAC > dyAB * dxAC) dir = -1;      // 반시계방향
	if (dxAB * dyAC == dyAB * dxAC) {     // 일직선 상에 있는 경우
		if (dxAB == 0 && dyAB == 0) dir = 0;  // A = B 
		else if ((dxAB * dxAC < 0) || (dyAB * dyAC < 0)) dir = -1;   // A가 가운데
		else if (dxAB * dxAB + dyAB * dyAB >= dxAC * dxAC + dyAC * dyAC) dir = 0;     // C가 가운데
		else dir = 1;  // B가 가운데
	}
	return dir;
}

int Intersection(Line AB, Line CD) { // 두 선분 교차 여부 (AB, CD가 서로 교차하면 TRUE, 아니면 FALSE)
	
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
	Line input; // 입력 선

	inp >> n;
	while (n--) {
		inp >> input.p1.x >> input.p1.y >> input.p2.x >> input.p2.y;
		/* 사각형 정보 입력 받음 */
		poly[0] = { input.p1.x, input.p1.y, input.p2.x, input.p1.y };
		poly[1] = { input.p2.x, input.p1.y, input.p2.x, input.p2.y };
		poly[2] = { input.p2.x, input.p2.y, input.p1.x, input.p2.y };
		poly[3] = { input.p1.x, input.p2.y, input.p1.x, input.p1.y };
		/* 사각형 만듬 */
		inp >> input.p1.x >> input.p1.y >> input.p2.x >> input.p2.y;
		out << Inter_Count(input) << '\n';
	}
	inp.close();
	out.close();
	return 0;
}