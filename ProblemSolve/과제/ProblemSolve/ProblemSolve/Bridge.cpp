#include<iostream>
#include<fstream>
#include<cstdlib>
#define MAX 99999999

using namespace std;

int Solve_One(int list[], int n) { // Simple Solution.
	int time = list[n - 1], index = n - 2;
	n -= 2;
	while (n != 0) {
		time += list[0]; // 가장 속도 빠른 사람이 돌아옴.
		n++;

		time += list[index];
		index--, n -= 2;
	}
	return time;
}
int Solve_Two(int list[], int n) { // a little bit Complex Solution
	int t = MAX, pre_t = MAX;
	bool exist_one = true, exist_two = true;
	int time = list[1], index = n - 1; // 가장 속도 빠른 사람과 두 번째로 빠른 사람이 이동.
	n -= 2;
	while (n != 0) {
		if (exist_one) { // 우측에 가장 빠른 사람이 있으면,
			time += list[0];
			exist_one = false;
		}
		else { // 우측에 가장 빠른 사람이 없으면,
			time += list[1];
			exist_two = false;
		}
		n++;
		if (n == 3 && exist_two) {
			int l[3] = { list[0], list[2], list[3] };
			t = Solve_One(l, 3), pre_t = time;
		}
		if (!exist_one && !exist_two) { // 우측에 두 명 다 없으면,
			time += list[1]; // 다시 두 명이 오른쪽으로 이동.
			exist_one = true, exist_two = true;
		}
		else { // 남은 사람 중 가장 큰 사람 둘이 이동
			time += list[index];
			index -= 2;
		}
		n -= 2;
		
	}
	return (time > pre_t + t ? pre_t + t : time);
}
int compare(const void *first, const void *second) { // 퀵 정렬 비교 함수 (내림차순 정렬)
	if (*(int*)first > *(int*)second)
		return 1;
	else if (*(int*)first < *(int*)second)
		return -1;
	else
		return 0;
}

int Solve(int list[], int n) {
	int time = 0, t1, t2, index = n - 1;
	while (n > 3) {
		t1 = list[index - 1] + list[0] + list[index] + list[0]; // 작은 놈 혼자 왔다갔다.
		t2 = list[1] + list[0] + list[index] + list[1]; // 제일 작은 둘 가서 제일 작은 놈 돌아오고 큰 놈 둘이 가서 두 번째로 작은 놈 돌아옴
		time += t1 > t2 ? t2 : t1;
		index -= 2;
		n -= 2;
	}
	if (n == 2) {
		time += (list[1]);
	}
	else {
		time += (list[2] + list[0] + list[1]);
	}
	return time;
}

int main() {
	ifstream inp("Bridge.inp");
	ofstream out("Bridge.out");
	int testcase;
	inp >> testcase;

	while (testcase--) {
		int n, list[20000];
		inp >> n;
		for (int i = 0; i < n; i++) inp >> list[i]; // input scan
		qsort(list, n, sizeof(int), compare); // 정렬
		if (n == 1) { // 만약 한 명일 경우
			out << list[0] << endl;
		}
		else {
			// int one = Solve_One(list, n), two = Solve_Two(list, n); // 두 개의 솔루션 설정
			// out << (one > two ? two : one) << endl; // 그 답 둘 중 작은 것 출력
			out << Solve(list, n) << endl;
		}
	}
	inp.close();
	out.close();
	return 0;
}