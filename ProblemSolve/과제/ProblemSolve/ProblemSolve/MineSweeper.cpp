#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

char Map[102][102];

int Discover(int i, int j) { // ÁÖÀ§ Å½»ö
	int num = 0;
	if (Map[i - 1][j - 1] == '*') {
		num++;
	}
	if (Map[i - 1][j] == '*') {
		num++;
	}
	if (Map[i - 1][j + 1] == '*') {
		num++;
	}
	if (Map[i][j - 1] == '*') {
		num++;
	}
	if (Map[i][j + 1] == '*') {
		num++;
	}
	if (Map[i + 1][j - 1] == '*') {
		num++;
	}
	if (Map[i + 1][j] == '*') {
		num++;
	}
	if (Map[i + 1][j + 1] == '*') {
		num++;
	}
	return num;
}

int main() {
	int n, m, cnt = 1;
	ifstream inp("MineSweeper.inp");
	ofstream out("MineSweeper.out");
	while (true) {
		inp >> n >> m;
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= n; i++) {
				inp >> (Map[i] + 1);
		} // input.

		out << "Field #" << cnt << ":" << endl;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (Map[i][j] == '*') out << '*';
				else out << Discover(i, j);
			}
			out << endl;
		} // output.
		memset(Map, 0, 102 * 102);
		cnt++;
		out << endl;
	}
	inp.close();
	out.close();
	return 0;
}