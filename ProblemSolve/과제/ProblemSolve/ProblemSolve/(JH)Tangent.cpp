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
	double x = 0, y = 0, pAngle = 0; // ���������� ����
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
	// ��ǥ ������ �����Ѵ�.
	if (a.y < b.y) {
		return true;
	}
	else if (a.y == b.y) {
		if (a.x < b.x) return true;
	} return false;
}

bool SortAngle(point a, point b) {
	// ���� ������ �����Ѵ�. */
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
	/* ���� A->B ���Ϳ� ���ؼ� ��ǥ C�� ������ ������ */
	double isIn = (((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x)));
	if (isIn > 0) { // Point C �� ���� �� �� 
		return LEFT;
	}
	else if (isIn == 0) { // Point C �� ���� �� �� 
		return MID;
	}
	else { // Point C�� ������ �� ��
		return RIGHT;
	}
}

void convexhull_algorithm(deque<point> *p, deque <point> *c) { 
	// ��ü ��ǥ ����, convex ��ǥ ����
	/* ---------- �ΰ��� �ٰ����� ���� convex hull�� ���Ѵ�. ---------- */
	/* �ǹ��� �Ǵ� ������ �� ������ ���� ��� */
	int size = p->size();
	for (int i = 1; i < size; i++) {
		// P[0]�� sort�� ���� �ǹ��� �Ǵ� ���� �ȴ�.
		double op1 = (p->at(i).y - p->at(0).y), op2 = (p->at(i).x - p->at(0).x);
		if (op2 == 0) {
			p->at(i).pAngle = (IFI); // y��� �����ϸ� ���Ⱑ ����
		}
		else {
			p->at(i).pAngle = (op1 / op2);
		}
	}

	/* ���� ������ �ݽð� �������� ���� */
	sort(p->begin(), p->end(), SortAngle); // ���� �������� �����Ѵ�.
	while (p->front().pAngle < 0) {
		p->push_back(p->front());
		p->pop_front();
	}// �ݽð�������� ���� �̱⿡ front�κп� ���̳ʽ��� ������ �ڷ� �Ű���
	p->push_back(p->front());

	/* convex ���ϱ�*/
	/*
	Convex[0], Convex[1] (Point A,B)�� ������ ���������� ���ĵ� Point[0] (Point C)�� ��������,
	1. Point C �� A,B�� ���� �Ǵ� ���� �̶�� Point C�� Convex.front�� Push
	3. Point C �� A,B�� �������̶�� ������ Convex�� �ƴϹǷ� Convex[0]�� Pop �ϰ�, �ٽ� 1������ ����
	*/
	c->push_front(p->front()); p->pop_front(); // 0 �� ������ Ȯ���̴�.
	c->push_front(p->front()); p->pop_front(); // 1 �� ������ Ȯ���̴�.
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
	/* �ߺ� ���� */
	int Size = c->size();
	if (c->at(0).x == c->at(Size - 1).x and c->at(0).y == c->at(Size - 1).y) {
		c->pop_back();
	}
	reverse(c->begin(), c->end());

}

double area_Cal(deque<point> p) {
	/* �ٰ����� ���̸� ���ϴ� �Լ� */
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
	// ��ü ��ǥ ����, �� �ٰ����� convex ����, �� �ٰ����� convex ���� 
	// convex Hull�� ������ �� ���� ��, Poly1, Poly2 �ٰ����� ������ �׾����� �ش� �ٰ����� ������ start, end�� �����ϰ�
	// ������ ������ �������� start���� ����ؼ� end���� ���鼭 ��ǥ�� �߰��Ѵ�. 

	// ���� ã��
	int tCnt = tc.size(), cPoint[2], cpIdx = 0;
	for (int i = 0; i < tCnt; i++) {
		int j = (i + 1) % tCnt;
		if (tc.at(i).kind != tc.at(j).kind) { // ������ �߻��ϴ� ����
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

	// �ð� �Ǵ� �ݽð� �������� ���༭ ��ǥ �߰��ϱ�
	int Cnt = p.size();
	int ConvexStart = cPoint[0];
	int ConvexEnd = cPoint[1];

	while (1) {
		if (direction == RIGHT) { // ������
			ConvexStart = (ConvexStart + 1) % Cnt;
		}
		else if (direction == LEFT) { // ����
			ConvexStart--;
			if (ConvexStart < 0) { ConvexStart = Cnt - 1; }
		}

		if (ConvexStart == ConvexEnd) { // �ѹ��� �� ���Ҵٸ� break
			break;
		}
		else { // ��� ���鼭 ��ǥ�� �߰��Ѵ�.
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
										   /* �ΰ��� �ٰ��� �Է� �ޱ�   */
		double in_x = 0, in_y = 0;
		int p1Cnt; fscanf(input, "%d", &p1Cnt);
		for (int i = 0; i < p1Cnt; i++) {
			fscanf(input, "%lf %lf", &in_x, &in_y);
			point p(in_x, in_y, i, P1); // �����̳� ���� �ִ� �ٰ����̶�� �⺻������ ����
			Poly1.push_back(p); // Poly1�� ���� �ٰ��� ��ǥ
			PolyT.push_back(p); // ��ü ConvexHull�� ���ϱ� ���ؼ�
		}

		int p2Cnt; fscanf(input, "%d", &p2Cnt);
		for (int i = 0; i < p2Cnt; i++) {
			fscanf(input, "%lf %lf", &in_x, &in_y);
			point p(in_x, in_y, i, P2); // �������̳� �Ʒ��� �ִ� �ٰ����̶�� �⺻������ ����
			Poly2.push_back(p); // Poly2�� ���� �ٰ��� ��ǥ
			PolyT.push_back(p); // ��ü ConvexHull�� ���ϱ� ���ؼ�
		}
		// ��ǥ������ ����
		sort(PolyT.begin(), PolyT.end(), SortCor);

		// Convex : �� �ٰ����� ConvexHull ��ǥ
		// ConvexPoly1 : Poly1 �ٰ����� ConvexHull����, Poly1 �ٰ����� ���� ���� ���� ��ǥ�� ���� ����
		// ConvexPoly1 : Poly2 �ٰ����� ConvexHull����, Poly2 �ٰ����� ���� ���� ���� ��ǥ�� ���� ����
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

		/* Convex + �� ������ ��ǥ �� ��� �� ���� ��� */
		double area1, area2;
		area1 = area2 = area_Cal(Convex);
		area1 = area1 - find_cor(Poly1, ConvexPoly1, Convex, P1, LEFT) - find_cor(Poly2, ConvexPoly2, Convex, P2, RIGHT);
		area2 = area2 - find_cor(Poly1, ConvexPoly1, Convex, P1, RIGHT) - find_cor(Poly2, ConvexPoly2, Convex, P2, LEFT);
		fprintf(output, "%.1lf\n", area1 < area2 ? area1 : area2);
	}
}