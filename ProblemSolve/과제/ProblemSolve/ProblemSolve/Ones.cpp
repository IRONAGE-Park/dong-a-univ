#include<iostream>
#include<fstream>

using namespace std;

int Ones(int n) {
	int len = 0, div = 1 % n;
	while (++len) {
		if (div == 0)
			break;
		div = ((div % n) * (10 % n) + 1) % n;
	}
	return len;
}

int main() {
	ifstream inp("Ones.inp");
	ofstream out("Ones.out");
	int n;
	while (inp >> n) {
		out << Ones(n) << "\n";
	}
	inp.close();
	out.close();
	return 0;
}