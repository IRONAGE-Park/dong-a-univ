#include<iostream>
#include<fstream>

using namespace std;

int A = 0, M = 1;

int gcd(int a, int b) {
	return a % b ? gcd(b, a%b) : b;
}

void Combine(int a, int m) { // �ʱ� �� {x = (M * t) + A}�� {x = a (mod m)} ����
	int C_t = A, C_a = a - A, C_m = m;
	if (C_a < 0) C_a += m;
	/* C_t = C_a (mod C_m) ���·� �籸�� */
	int div = gcd(C_t, gcd(C_a, C_m));
	C_t /= div, C_a /= div, C_m /= div;
	/* �ٲ� ���¿��� �� ���� �ִ� ������� ������ */


}

int main() {
	ifstream inp("ChineseRemainderTheorem.inp");
	ofstream out("ChineseRemainderTheorem.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n; // ������ ����
		inp >> n;

		while (n--) {
			int a, m;
			inp >> a >> m;
			Combine(a, m);
		}
		out << A << '\n';
		A = 0, M = 1;
	}
	inp.close();
	out.close();
	return 0;
}