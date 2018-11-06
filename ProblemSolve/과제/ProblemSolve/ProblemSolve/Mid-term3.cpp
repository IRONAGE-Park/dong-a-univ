#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int Divisor(int n) {
	int cnt = 0;
	for (int i = 1; i <= sqrt(n); i++) {
		if (n % i == 0) {
			cnt += 2;
			if (i == sqrt(n)) cnt--;
		}
	}
	return cnt;
}

int main() {
	ifstream inp("Mid-term3.inp");
	ofstream out("Mid-term3.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n;
		inp >> n;
		out << Divisor(n) << '\n';
	}
	inp.close();
	out.close();
	return 0;
}