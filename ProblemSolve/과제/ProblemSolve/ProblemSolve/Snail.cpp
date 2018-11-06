#include<iostream>
#include<fstream>

using namespace std;

int main() {
	ifstream inp("Snail.inp");
	ofstream out("Snail.out");
	double H, U, D, F; // H = 우물의 높이, U = 하루동안 올라갈 수 있는 높이, D = 자는동안 떨어지는 높이, F = 피곤지수
	while (true) {
		inp >> H >> U >> D >> F;
		if (!H && !U && !D && !F) break; // 모두 0 => 마지막 input
		/* INPUT DATA */
		double now = U, point = U * F / 100; // 현재 높이와 피곤지수로 인한 오를 수 있는 높이 감소량.
		bool success = true; // 성공 유무
		int day = 1; // Check까지 걸리는 일 수.
		while (now <= H) { // H 초과로 오를때까지
			now -= D; // D만큼 떨어짐
			U = U - point;
			if (U < 0) U = 0;
			if (now < 0) { // 탈출 실패
				success = false;
				break;
			}
			day++;
			/* 여기까지 하루가 지남 */
			now += U;
			/* 다시 올라감*/
		}
		if (success) out << "success ";
		else out << "failure ";
		out << "on day " << day << '\n';
		/* OUTPUT DATA */
	}
	inp.close();
	out.close();
	return 0;
}