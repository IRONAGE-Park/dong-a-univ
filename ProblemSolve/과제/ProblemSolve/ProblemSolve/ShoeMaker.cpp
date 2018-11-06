#include<iostream>
#include<fstream>

using namespace std;

typedef struct Data {
	int num;
	int t;
	int s;
}Data;

Data info[1000];
int n;

bool exchange(int idx1, int idx2) {
	bool check = false;
	if (info[idx1].t * info[idx2].s < info[idx2].t * info[idx1].s) {
		Data temp = info[idx1];
		info[idx1] = info[idx2];
		info[idx2] = temp;
		check = true;
	}
	else if (info[idx1].t * info[idx2].s == info[idx2].t * info[idx1].s) {
		if (info[idx1].num < info[idx2].num) {
			Data temp = info[idx1];
			info[idx1] = info[idx2];
			info[idx2] = temp;
			check = true;
		}		
	}
	return check;
}

void Solution() {
	for (int i = 0; i < n; i++) {
		bool check = false;
		for (int j = 0; j < n - 1; j++) {
			bool c = exchange(j, j + 1);
			if (!check) check = c;
		}
		if (!check) return;
	}
}

int main() {
	ifstream inp("ShoeMaker.inp");
	ofstream out("ShoeMaker.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> info[i].t >> info[i].s;
			info[i].num = i + 1;
		} // input
		Solution();
		for (int i = n - 1; i >= 0; i--)
			out << info[i].num << " ";
		out << '\n'; // output
	}
	inp.close();
	out.close();
	return 0;
}