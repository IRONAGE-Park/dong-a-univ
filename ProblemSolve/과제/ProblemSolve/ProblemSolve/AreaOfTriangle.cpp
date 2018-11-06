#include<iostream>
#include<fstream>
#include<cmath>

double Abs(double n) {
	if (n > 0) return n;
	else return n * -1;
}

using namespace std;

typedef struct Point { // �� ����ü ����.
	double x;
	double y;
}Point;

class Circle { // �� Ŭ���� ����.
private:
	Point p; // ���� ���� ��ǥ
	double r; // ���� ������

public:
	Circle(double x, double y, double r) { // ������ -> x��ǥ, y��ǥ, ������
		this->p.x = x;
		this->p.y = y;
		this->r = r;
	}
	Point getPoint() { // ���� ���� ��ǥ ��ȯ
		return this->p;
	}

	double getRadius() { // ���� ������ ��ȯ
		return this->r;
	}

	bool InterCircle(Point p) { // �� ���ο� � ���� �����ϴ��� �Ǵ�
		Point diff;
		diff.x = p.x - this->getPoint().x; // �� p�� this�� ���� x��ǥ ����
		diff.y = p.y - this->getPoint().y; // �� p�� this�� ���� y��ǥ ����
		double l = sqrt((diff.x * diff.x) + (diff.y * diff.y)); // ������ �� ������ �Ÿ�.
		if (l > this->getRadius()) return false; // �� �Ÿ��� ���� this�� ���������� ũ�� �� �ȿ� �������� �ʴ� ��.
		else return true;
	}

	Point Intersection(Circle *oper, Circle *other) { // oper�� ������ ���ϴ� ��, other�� �� ���� �߿� �ϳ��� ������ ���� ����� ��.
		Point one, two; // ���� �� ���� ������ ����
		Point diff; // ���� ���� ��ġ ���� ����

		double l, k;
		diff.x = oper->getPoint().x - this->getPoint().x; // oper�� this�� ���� x��ǥ ����
		diff.y = oper->getPoint().y - this->getPoint().y; // oper�� this�� ���� y��ǥ ����
		l = sqrt((diff.x * diff.x) + (diff.y * diff.y)); // �� ���� ������ �Ÿ�.
		k = ((l * l) + (this->getRadius() * this->getRadius()) - (oper->getRadius() * oper->getRadius())) / (2 * l);

		one.x = this->getPoint().x + (diff.x * k / l) + (diff.y / l) * sqrt((this->getRadius() * this->getRadius()) - k * k);
		one.y = this->getPoint().y + (diff.y * k / l) - (diff.x / l) * sqrt((this->getRadius() * this->getRadius()) - k * k);
		two.x = this->getPoint().x + (diff.x * k / l) - (diff.y / l) * sqrt((this->getRadius() * this->getRadius()) - k * k);
		two.y = this->getPoint().y + (diff.y * k / l) + (diff.x / l) * sqrt((this->getRadius() * this->getRadius()) - k * k);

		if (other->InterCircle(one)) return one; // ���� one�� ������ ���� �����ִ�.
		if (other->InterCircle(two)) return two; // ���� two�� ������ ���� �����ִ�.
		return { -10000.0, -10000.0 }; // ������ �ٸ� ���� ������ ���� ���.
	}
};

double TrianlgeArea(Point p1, Point p2, Point p3) { // �� �� ���� ����� �ﰢ���� ����
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

		Point p1, p2, p3; // ���� �� ��
		p1 = circle1.Intersection(&circle2, &circle3);
		p2 = circle1.Intersection(&circle3, &circle2);
		p3 = circle2.Intersection(&circle3, &circle1);
		out << TrianlgeArea(p1, p2, p3) << "\n"; // ���� �� ���� ����� �ﰢ���� ���� ���
	}
	inp.close();
	out.close();
	return 0;
}