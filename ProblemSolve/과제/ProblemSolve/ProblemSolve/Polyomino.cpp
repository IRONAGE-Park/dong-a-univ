#include<iostream>
#include<fstream>
#define MOD 1000000007

using namespace std;

int poly[501][501];
bool use[501][501];

int sol_Poly(int n, int fl) {
	if (n == fl) return 1; // 첫번째 줄에 모든 네모를 다 몰아 두는 경우 = 1
	if (use[n][fl]) return poly[n][fl]; // 이미 구한 답일 경우

	for (int i = 1; i <= n - fl; i++) {
		int num = (fl + i - 1) * sol_Poly(n - fl, i); // 첫번째 줄에 이미 fl개 사용하고, 나머지 네모로 만들 수 있는 경우의 수
		num %= MOD;
		poly[n][fl] += num; // 다시 쓸 수 있도록 배열에 저장
		poly[n][fl] %= MOD;
	}
	use[n][fl] = true; // 이미 구한 값은 다시 게산할 필요가 없도록 표시
	return poly[n][fl];
}

int search_Poly(int n) { // n개의 네모가 있을 때 답 도출
	int sol = 0;
	for (int i = 1; i <= n; i++) { // 첫번째 줄에 1개 ~ n개 까지 있는 경우
		sol += sol_Poly(n, i); // n개의 네모에서 첫번째 줄에 i개 뒀을 때 나올 수 있는 경우의 수
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