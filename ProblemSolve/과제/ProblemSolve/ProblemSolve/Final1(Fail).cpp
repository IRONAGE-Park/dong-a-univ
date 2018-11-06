#include<iostream>
#include<fstream>

using namespace std;

typedef unsigned long long int lint;
typedef struct { int x, y; }Point;

lint Factorial(int n, int stop) {
	if (n == stop) return 1;
	if (n <= 1) return 1;
	return n * Factorial(n - 1, stop);
}

void Swap(Point *p1, Point *p2) {
	if (p1->x > p2->x && p1->y > p2->y) {
		Point temp = *p1;
		*p1 = *p2;
		*p2 = temp;
	}
}

lint Count_Path(Point S, Point T) {
	int d_x = T.x - S.x;
	int d_y = T.y - S.y;
	if (d_x < 0 || d_y < 0) return 0;
	lint cnt;
	if (d_x < d_y) cnt = Factorial(d_y + d_x, d_y) / Factorial(d_x, 1);
	else cnt = Factorial(d_y + d_x, d_x) / Factorial(d_y, 1);
	return cnt;
}

lint Search_Path(Point T, Point p1, Point p2) {
	Point S = { 0, 0 }; // 시작점
	Swap(&p1, &p2); // 만약 p2가 p1보다 왼쪽 아래에 있다면 바꿔줌
	lint cnt = (Count_Path(S, p1) * Count_Path(p1, T)) + (Count_Path(S, p2) * Count_Path(p2, T));
	cnt -= (Count_Path(S, p1) * Count_Path(p1, p2) * Count_Path(p2, T));
	return cnt;
}

int main() {
	ifstream inp("Final2.inp");
	ofstream out("Final2.out");

	int testcase;
	inp >> testcase;
	while (testcase--) {
		Point p1, p2, T;
		inp >> T.x >> T.y >> p1.x >> p1.y >> p2.x >> p2.y;
		out << Search_Path(T, p1, p2) << '\n';
	}
	inp.close();
	out.close();
	return 0;
}