#include<iostream>
#include<fstream>

using namespace std;

int main() {
	ifstream inp("Mid-term1.inp");
	ofstream out("Mid-term1.out");

	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n;
		inp >> n;
		bool check = false;
		long long int a = n - 1, b = n + 1, sumA = n + n - 1, sumB = n + n + 1;
		while (a > 0) {
			if (sumA > sumB) {
				sumB += ++b;
			}
			else if (sumA < sumB) {
				sumA += --a;
			}
			else {
				check = true;
				break;
			}
		}
		if (check) out << a << ' ' << b;
		else out << 0;
		out << '\n';
	}
	inp.close();
	out.close();
	return 0;
}