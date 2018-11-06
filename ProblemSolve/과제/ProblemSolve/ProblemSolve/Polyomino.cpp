#include<iostream>
#include<fstream>
#define MOD 1000000007

using namespace std;

int poly[501][501];
bool use[501][501];

int sol_Poly(int n, int fl) {
	if (n == fl) return 1; // ù��° �ٿ� ��� �׸� �� ���� �δ� ��� = 1
	if (use[n][fl]) return poly[n][fl]; // �̹� ���� ���� ���

	for (int i = 1; i <= n - fl; i++) {
		int num = (fl + i - 1) * sol_Poly(n - fl, i); // ù��° �ٿ� �̹� fl�� ����ϰ�, ������ �׸�� ���� �� �ִ� ����� ��
		num %= MOD;
		poly[n][fl] += num; // �ٽ� �� �� �ֵ��� �迭�� ����
		poly[n][fl] %= MOD;
	}
	use[n][fl] = true; // �̹� ���� ���� �ٽ� �Ի��� �ʿ䰡 ������ ǥ��
	return poly[n][fl];
}

int search_Poly(int n) { // n���� �׸� ���� �� �� ����
	int sol = 0;
	for (int i = 1; i <= n; i++) { // ù��° �ٿ� 1�� ~ n�� ���� �ִ� ���
		sol += sol_Poly(n, i); // n���� �׸𿡼� ù��° �ٿ� i�� ���� �� ���� �� �ִ� ����� ��
		sol %= MOD;
	}
	sol %= MOD;
	return sol;
}

int main() {
	ifstream inp("Polyomino.inp");
	ofstream out("Polyomino.out");
	poly[1][1] = 1;
	int testcase;
	inp >> testcase;

	while (testcase--) {
		int n;
		inp >> n;
		out << search_Poly(n) << '\n';
	}
	inp.close();
	out.close();
	return 0;
}