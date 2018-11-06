#include<iostream>
#include<fstream>

using namespace std;

int Solve(int n) {
	int cnt = 1;
	while (n != 1) {
		if (n % 2 == 0) {
			n /= 2;
		}
		else {
			n = (n * 3) + 1;
		}
		cnt++;
	}
	return cnt;
}

int main() {
	ifstream inp("3n+1.inp");
	ofstream out("3n+1.out");
	int a = -1, b = -1, max = 0;
	while (!inp.eof()) {
		inp >> a >> b;
		if (a != -1 && b != -1) {
			if (a > b) {
				for (int i = b; i <= a; i++) {
					int cnt = Solve(i);
					if (max < cnt)
						max = cnt;
				}
			}
			else {
				for (int i = a; i <= b; i++) {
					int cnt = Solve(i);
					if (max < cnt)
						max = cnt;
				}
			}
			out << a << " " << b << " " << max << endl;
		}
		a = -1, b = -1;
		max = 0;
	}
	inp.close();
	out.close();
	return 0;
}