#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>

using namespace std;

bool node[1500000];

int dropBall(int D) {
	int index = 1;
	for (int i = 0; i < D - 1; i++) {
		if (node[index]) { // node[index]가 트루면,
			node[index] = false;
			index = (index * 2) + 1;
		}
		else {
			node[index] = true;
			index = index * 2;
		}
	}
	return index;
}

int main() {
	ifstream inp("DroppingBalls.inp");
	ofstream out("DroppingBalls.out");
	int n;
	inp >> n;
	while (n--) {
		int D, I, result;
		inp >> D >> I;
		for (int i = 0; i < I; i++) {
			result = dropBall(D);
		}
		out << result << endl;
		memset(node, false, pow(2, D) - 1);
	}
	inp.close();
	out.close();
	return 0;
}