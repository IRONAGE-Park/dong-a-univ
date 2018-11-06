#include<iostream>
#include<fstream>

using namespace std;

int x, y, z;

bool Solution(int A, int B, int C) {
	int i = 0, j, k;
	if (B > 0) i++; // �� ���� ������ 0���� ũ��.

	for (; i * i <= C; i++) {
		for (j = i; j * j <= C; j++) {
			for (k = j; k * k <= C; k++) {
				if ((i * i) + (j * j) + (k * k) == C) { // x^2 + y^2 + z^2 == C �̸�,
					if (i * j * k == B) { // x*y*z == B �̸�,
						
						if (i + j + k == A) {
							x = i, y = j, z = k;
							return true;
						}
						if (i - j - k == A) {
							x = i, y = k * -1, z = j * -1;
							return true;
						}
						if (j - i - k == A) {
							x = k * -1, y = j, z = i * -1;
							return true;
						}
						if (k - i - j == A) {
							x = j * -1, y = i * -1, z = k;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

int main() {
	ifstream inp("Equation.inp");
	ofstream out("Equation.out");
	int testcase;
	inp >> testcase;

	while (testcase--) {
		int A, B, C;
		inp >> A >> B >> C;
		bool exist = Solution(A, B, C);
		if (exist) out << x << " " << y << " " << z;
		else out << "No solution.";
		out << "\n";
	}
	inp.close();
	out.close();
	return 0;
}