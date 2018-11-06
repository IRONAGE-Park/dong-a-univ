#include<iostream>
#include<fstream>
#include<cmath>

double Abs(double n) {
	if (n > 0) return n;
	else return n * -1;
}

using namespace std;

typedef struct Point { // 점 구조체 선언.
	double x;
	double y;
}Point;

class Circle { // 원 클래스 선언.
private:
	Point p; // 원의 중점 좌표
	double r; // 원의 반지름

public:
	Circle(double x, double y, double r) { // 생성자 -> x좌표, y좌표, 반지름
		this->p.x = x;
		this->p.y = y;
		this->r = r;
	}
	Point getPoint() { // 원의 중점 좌표 반환
		return this->p;
	}

	double getRadius() { // 원의 반지름 반환
		return this->r;
	}

	bool InterCircle(Point p) { // 원 내부에 어떤 점이 존재하는지 판단
		Point diff;
		diff.x = p.x - this->getPoint().x; // 점 p와 this의 중점 x좌표 차이
		diff.y = p.y - this->getPoint().y; // 점 p와 this의 중점 y좌표 차이
		double l = sqrt((diff.x * diff.x) + (diff.y * diff.y)); // 중점과 점 사이의 거리.
		if (l > this->getRadius()) return false; // 그 거리가 만약 this의 반지름보다 크면 원 안에 존재하지 않는 것.
		else return true;
	}

	Point Intersection(Circle *oper, Circle *other) { // oper는 교점을 구하는 원, other는 두 교점 중에 하나를 선택할 때에 사용할 원.
		Point one, two; // 교점 두 곳을 저장할 변수
		Point diff; // 원의 중점 위치 차이 저장

		double l, k;
		diff.x = oper->getPoint().x - this->getPoint().x; // oper와 this의 중점 x좌표 차이
		diff.y = oper->getPoint().y - this->getPoint().y; // oper와 this의 중점 y좌표 차이
		l = sqrt((diff.x * diff.x) + (diff.y * diff.y)); // 두 중점 사이의 거리.
		k = ((l * l) + (this->getRadius() * this->getRadius()) - (oper->getRadius() * oper->getRadius())) / (2 * l);

		one.x = this->getPoint().x + (diff.x * k / l) + (diff.y / l) * sqrt((this->getRadius() * this->getRadius()) - k * k);
		one.y = this->getPoint().y + (diff.y * k / l) - (diff.x / l) * sqrt((this->getRadius() * this->getRadius()) - k * k);
		two.x = this->getPoint().x + (diff.x * k / l) - (diff.y / l) * sqrt((this->getRadius() * this->getRadius()) - k * k);
		two.y = this->getPoint().y + (diff.y * k / l) + (diff.x / l) * sqrt((this->getRadius() * this->getRadius()) - k * k);

		if (other->InterCircle(one)) return one; // 교점 one가 나머지 원에 속해있다.
		if (other->InterCircle(two)) return two; // 교점 two가 나머지 원에 속해있다.
		return { -10000.0, -10000.0 }; // 교점이 다른 원에 속하지 않을 경우.
	}
};

double TrianlgeArea(Point p1, Point p2, Point p3) { // 점 세 개가 만드는 삼각형의 넓이
	double area = 0.5;
	area *= (p1.x * p2.y) + (p2.x * p3.y) + (p3.x * p1.y) - (p1.x * p3.y) - (p3.x * p2.y) - (p2.x * p1.y);
	return Abs(area);
}

int main() {
	ifstream inp("AreaOfTriangle.inp");
	ofstream out("AreaOfTriangle.out");
	int testcase;
	inp >> testcase;
	out << fixed;
	out.precision(2);
	while (testcase--) {
		double x1, y1, r1, x2, y2, r2, x3, y3, r3;
		inp >> x1 >> y1 >> r1 >> x2 >> y2 >> r2 >> x3 >> y3 >> r3;
		Circle circle1(x1, y1, r1), circle2(x2, y2, r2), circle3(x3, y3, r3);

		Point p1, p2, p3; // 교점 세 곳
		p1 = circle1.Intersection(&circle2, &circle3);
		p2 = circle1.Intersection(&circle3, &circle2);
		p3 = circle2.Intersection(&circle3, &circle1);
		out << TrianlgeArea(p1, p2, p3) << "\n"; // 교점 세 곳이 만드는 삼각형의 넓이 출력
	}
	inp.close();
	out.close();
	return 0;
}