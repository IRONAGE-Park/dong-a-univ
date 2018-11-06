#include<iostream>
#include<fstream>

using namespace std;

int R, X, Y;

int abs(int n) {
	if (n > 0) return n;
	else return n * -1;
}

int gcd(int a, int b) {
	return a % b ? gcd(b, a%b) : b;
}

void extended_Euclid(int a, int b) {
	int q, r, s, t;
	int r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1;
	while (r2 != 0) {
		q = r1 / r2; r = r1 - (q * r2); s = s1 - (q * s2); t = t1 - (q * t2);
		r1 = r2; r2 = r; s1 = s2; s2 = s; t1 = t2; t2 = t;
	}
	R = r1; X = s1; Y = t1;
}

int Solution(int a, int b, int c) {
	if (c % gcd(a, b) != 0) return -1; // 디오판토스 방정식의 조건을 만족하지 못하면,
	extended_Euclid(a, b);
	int mul = c / R, MODE;
	X *= mul; Y *= mul;
	int min_UP = abs(X) + abs(Y); int min_DOWN = min_UP;
	int pre, new_X = X, new_Y = Y;
	while (true) {
		pre = abs(new_X) + abs(new_Y);
		new_X -= b, new_Y += a;
		if (pre < abs(new_X) + abs(new_Y)) break;
	}
	min_UP = pre;
	new_X = X, new_Y = Y;
	while (true) {
		pre = abs(new_X) + abs(new_Y);
		new_X += b, new_Y -= a;
		if (pre < abs(new_X) + abs(new_Y)) break;
	}
	min_DOWN = pre;
	return min_UP > min_DOWN ? min_DOWN : min_UP;
}

int main() {
	ifstream inp("Final3.inp");
	ofstream out("Final3.out");

	int testcase;
	inp >> testcase;
	while (testcase--) {
		int a, b, c;
		inp >> a >> b >> c;
		int div = gcd(a, gcd(b, c));
		a /= div, b /= div, c /= div;
		out << Solution(a, b, c) << '\n';
	}
	inp.close();
	out.close();
	return 0;
}