#include<iostream>
#include<fstream>

using namespace std;

int A = 0, M = 1;

int gcd(int a, int b) {
	return a % b ? gcd(b, a%b) : b;
}

void Combine(int a, int m) { // 초기 식 {x = (M * t) + A}와 {x = a (mod m)} 결합
	int C_t = A, C_a = a - A, C_m = m;
	if (C_a < 0) C_a += m;
	/* C_t = C_a (mod C_m) 형태로 재구성 */
	int div = gcd(C_t, gcd(C_a, C_m));
	C_t /= div, C_a /= div, C_m /= div;
	/* 바꾼 형태에서 세 수의 최대 공약수로 나눠줌 */


}

int main() {
	ifstream inp("ChineseRemainderTheorem.inp");
	ofstream out("ChineseRemainderTheorem.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n; // 수식의 갯수
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