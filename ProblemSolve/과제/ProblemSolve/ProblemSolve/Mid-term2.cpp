#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

int n, jolly[100], firstJolly[100], secondJolly[100];
bool check[100];

int abs(int n) {
	if (n > 0) return n;
	else return n * -1;
}

void Jumper(int *sour, int *dest, int size) {
	for (int i = 0; i < size - 1; i++) {
		dest[i] = abs(sour[i] - sour[i + 1]);
	}
}

bool checkArray(int size) {
	for (int i = 1; i <= size; i++) {
		if (!check[i]) return false;
	}
	return true;
}

bool SecondOrderJollyJumper() {
	Jumper(jolly, firstJolly, n);
	Jumper(firstJolly, secondJolly, n - 1);
	for (int i = 0; i < n - 2; i++) {
		check[secondJolly[i]] = true;
	}
	return checkArray(n - 2);
}

int main() {
	ifstream inp("Mid-term2.inp");
	ofstream out("Mid-term2.out");

	int testcase;
	inp >> testcase;
	while (testcase--) {
		inp >> n;
		for (int i = 0; i < n; i++) inp >> jolly[i];
		if (SecondOrderJollyJumper()) out << "Yes";
		else out << "No";
		out << '\n';
		memset(jolly, 0, sizeof(jolly)), memset(firstJolly, 0, sizeof(jolly)), memset(secondJolly, 0, sizeof(jolly));
		memset(check, false, sizeof(check));
	}
	inp.close();
	out.close();
	return 0;
}