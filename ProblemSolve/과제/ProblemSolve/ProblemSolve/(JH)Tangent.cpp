#pragma warning(disable:4996)
#include<cstdio>
#include<algorithm>
#include<deque>
#define IFI 99999999
#define LEFT -1
#define MID 0
#define RIGHT 1
#define P1 -1
#define P2 1
using namespace std;

struct point {
	int idx = 0, kind = 0;
	double x = 0, y = 0, pAngle = 0; // 기준점과의 기울기
	point(double _x, double _y, int _idx, int _kind) {
		this->x = _x; this->y = _y;
		this->idx = _idx;
		this->kind = _kind;
	}
};

bool com(point a, point b) {
	return a.idx < b.idx;
}

bool SortCor(point a, point b) {
	// 좌표 순으로 정렬한다.
	if (a.y < b.y) {
		return true;
	}
	else if (a.y == b.y) {
		if (a.x < b.x) return true;
	} return false;
}

bool SortAngle(point a, point b) {
	// 각도 순으로 정렬한다. */
	if (a.pAngle < b.pAngle) {
		return true;
	}
	else if (a.pAngle == b.pAngle) {
		if (a.pAngle == 0) {
			if (a.x < b.x) return true;
		}
		else if (a.pAngle == IFI) {
			if (a.y > b.y) return true;
		}
		else {
			if (a.x < b.x) return true;
		}
	} return false;
}

int isPosition(point a, point b, point c) {
	/* 선분 A->B 벡터에 대해서 좌표 C의 방향을 결정함 */
	double isIn = (((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x)));
	if (isIn > 0) { // Point C 가 왼쪽 일 때 
		return LEFT;
	}
	else if (isIn == 0) { // Point C 가 직선 일 때 
		return MID;
	}
	else { // Point C가 오른쪽 일 때
		return RIGHT;
	}
}

void convexhull_algorithm(deque<point> *p, deque <point> *c) { 
	// 전체 좌표 정보, convex 좌표 정보
	/* ---------- 두개의 다각형에 대해 convex hull을 구한다. ---------- */
	/* 피벗이 되는 점과의 각 점들의 기울기 계산 */
	int size = p->size();
	for (int i = 1; i < size; i++) {
		// P[0]이 sort에 의해 피벗이 되는 점이 된다.
		double op1 = (p->at(i).y - p->at(0).y), op2 = (p->at(i).x - p->at(0).x);
		if (op2 == 0) {
			p->at(i).pAngle = (IFI); // y축과 평행하면 기울기가 무한
		}
		else {
			p->at(i).pAngle = (op1 / op2);
		}
	}

	/* 각도 순으로 반시계 방향으로 정렬 */
	sort(p->begin(), p->end(), SortAngle); // 내림 차순으로 정렬한다.
	while (p->front().pAngle < 0) {
		p->push_back(p->front());
		p->pop_front();
	}// 반시계방향으로 정렬 이기에 front부분에 마이너스가 있으면 뒤로 옮겨줌
	p->push_back(p->front());

	/* convex 구하기*/
	/*
	Convex[0], Convex[1] (Point A,B)의 직선과 각도순으로 정렬된 Point[0] (Point C)을 비교했을때,
	1. Point C 가 A,B의 왼쪽 또는 직선 이라면 Point C를 Convex.front에 Push
	3. Point C 가 A,B의 오른쪽이라면 최적의 Convex가 아니므로 Convex[0]를 Pop 하고, 다시 1번부터 수행
	*/
	c->push_front(p->front()); p->pop_front(); // 0 은 무조건 확정이다.
	c->push_front(p->front()); p->pop_front(); // 1 은 무조건 확정이다.
	while (!p->empty()) {
		point C(p->front().x, p->front().y, p->front().idx, p->front().kind);
		p->pop_front();
		while (1) {
			point A(c->at(1).x, c->at(1).y, c->at(1).idx, c->at(1).kind);
			point B(c->at(0).x, c->at(0).y, c->at(0).idx, c->at(0).kind);
			int ret = isPosition(A, B, C);
			if (ret == LEFT or ret == MID) { // 1.
				c->push_front(C); break;
			}
			else if (ret == RIGHT) { // 3.
				c->pop_front();
			}
		}
	}
	/* 중복 제거 */
	int Size = c->size();
	if (c->at(0).x == c->at(Size - 1).x and c->at(0).y == c->at(Size - 1).y) {
		c->pop_back();
	}
	reverse(c->begin(), c->end());

}

double area_Cal(deque<point> p) {
	/* 다각형의 넓이를 구하는 함수 */
	double area = 0.0;
	int size = p.size();
	for (int i = 0; i < size; i++) {
		int j = (i + 1) % size;
		area += ((p.at(i).x + p.at(j).x) * (p.at(i).y - p.at(j).y));
	}
	if (area < 0) area *= -1;
	return area /= 2;
}

double find_cor(deque<point> p, deque <point> c, deque <point> tc, int kind, int direction) { 
	// 전체 좌표 정보, 한 다각형의 convex 정보, 두 다각형의 convex 정보 
	// convex Hull로 결정된 양 끝점 즉, Poly1, Poly2 다각형의 접선을 그었을때 해당 다각형의 접점을 start, end로 설정하고
	// 위에서 결정한 방향으로 start에서 출발해서 end까지 돌면서 좌표를 추가한다. 

	// 접점 찾기
	int tCnt = tc.size(), cPoint[2], cpIdx = 0;
	for (int i = 0; i < tCnt; i++) {
		int j = (i + 1) % tCnt;
		if (tc.at(i).kind != tc.at(j).kind) { // 접점이 발생하는 지점
			if (tc.at(i).kind == kind) {
				cPoint[cpIdx++] = tc.at(i).idx;
			}
			else if (tc.at(j).kind == kind) {
				cPoint[cpIdx++] = tc.at(j).idx;
			}
		}
		if (cpIdx == 2)
			break;
	}

	// 시계 또는 반시계 방향으로 돎녀서 좌표 추가하기
	int Cnt = p.size();
	int ConvexStart = cPoint[0];
	int ConvexEnd = cPoint[1];

	while (1) {
		if (direction == RIGHT) { // 오른쪽
			ConvexStart = (ConvexStart + 1) % Cnt;
		}
		else if (direction == LEFT) { // 왼쪽
			ConvexStart--;
			if (ConvexStart < 0) { ConvexStart = Cnt - 1; }
		}

		if (ConvexStart == ConvexEnd) { // 한바퀴 다 돌았다면 break
			break;
		}
		else { // 계속 돌면서 좌표를 추가한다.
			c.push_back(p.at(ConvexStart));
		}
	}
	sort(c.begin(), c.end(), com);
	return area_Cal(c);
}

int main() {
	FILE *input = fopen("tangent.inp", "r");
	FILE *output = fopen("tangent.out", "w");
	int T = 0; fscanf(input, "%d", &T);
	while (T--) {
		deque <point> Poly1, Poly2, PolyT; // poly_1 ,poly_2, total_poly
										   /* 두개의 다각형 입력 받기   */
		double in_x = 0, in_y = 0;
		int p1Cnt; fscanf(input, "%d", &p1Cnt);
		for (int i = 0; i < p1Cnt; i++) {
			fscanf(input, "%lf %lf", &in_x, &in_y);
			point p(in_x, in_y, i, P1); // 왼쪽이나 위에 있는 다각형이라고 기본적으로 지정
			Poly1.push_back(p); // Poly1에 대한 다각형 좌표
			PolyT.push_back(p); // 전체 ConvexHull을 구하기 위해서
		}

		int p2Cnt; fscanf(input, "%d", &p2Cnt);
		for (int i = 0; i < p2Cnt; i++) {
			fscanf(input, "%lf %lf", &in_x, &in_y);
			point p(in_x, in_y, i, P2); // 오른쪽이나 아래에 있는 다각형이라고 기본적으로 지정
			Poly2.push_back(p); // Poly2에 대한 다각형 좌표
			PolyT.push_back(p); // 전체 ConvexHull을 구하기 위해서
		}
		// 좌표순으로 정렬
		sort(PolyT.begin(), PolyT.end(), SortCor);

		// Convex : 두 다각형의 ConvexHull 좌표
		// ConvexPoly1 : Poly1 다각형의 ConvexHull에서, Poly1 다각형의 접점 기준 안쪽 좌표를 같이 저장
		// ConvexPoly1 : Poly2 다각형의 ConvexHull에서, Poly2 다각형의 접점 기준 안쪽 좌표를 같이 저장
		deque<point> Convex, ConvexPoly1, ConvexPoly2;
		convexhull_algorithm(&PolyT, &Convex);

		int cCnt = Convex.size();
		for (int i = 0; i < cCnt; i++) {
			if (Convex.at(i).kind == P1) {
				ConvexPoly1.push_back(Convex.at(i));
			}
			else {
				ConvexPoly2.push_back(Convex.at(i));
			}
		}
		sort(ConvexPoly1.begin(), ConvexPoly1.end(), com);
		sort(ConvexPoly2.begin(), ConvexPoly2.end(), com);

		/* Convex + 각 도형의 좌표 값 계산 후 넓이 계산 */
		double area1, area2;
		area1 = area2 = area_Cal(Convex);
		area1 = area1 - find_cor(Poly1, ConvexPoly1, Convex, P1, LEFT) - find_cor(Poly2, ConvexPoly2, Convex, P2, RIGHT);
		area2 = area2 - find_cor(Poly1, ConvexPoly1, Convex, P1, RIGHT) - find_cor(Poly2, ConvexPoly2, Convex, P2, LEFT);
		fprintf(output, "%.1lf\n", area1 < area2 ? area1 : area2);
	}
}