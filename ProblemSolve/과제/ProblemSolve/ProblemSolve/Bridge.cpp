#include<iostream>
#include<fstream>
#include<cstdlib>
#define MAX 99999999

using namespace std;

int Solve_One(int list[], int n) { // Simple Solution.
	int time = list[n - 1], index = n - 2;
	n -= 2;
	while (n != 0) {
		time += list[0]; // ���� �ӵ� ���� ����� ���ƿ�.
		n++;

		time += list[index];
		index--, n -= 2;
	}
	return time;
}
int Solve_Two(int list[], int n) { // a little bit Complex Solution
	int t = MAX, pre_t = MAX;
	bool exist_one = true, exist_two = true;
	int time = list[1], index = n - 1; // ���� �ӵ� ���� ����� �� ��°�� ���� ����� �̵�.
	n -= 2;
	while (n != 0) {
		if (exist_one) { // ������ ���� ���� ����� ������,
			time += list[0];
			exist_one = false;
		}
		else { // ������ ���� ���� ����� ������,
			time += list[1];
			exist_two = false;
		}
		n++;
		if (n == 3 && exist_two) {
			int l[3] = { list[0], list[2], list[3] };
			t = Solve_One(l, 3), pre_t = time;
		}
		if (!exist_one && !exist_two) { // ������ �� �� �� ������,
			time += list[1]; // �ٽ� �� ���� ���������� �̵�.
			exist_one = true, exist_two = true;
		}
		else { // ���� ��� �� ���� ū ��� ���� �̵�
			time += list[index];
			index -= 2;
		}
		n -= 2;
		
	}
	return (time > pre_t + t ? pre_t + t : time);
}
int compare(const void *first, const void *second) { // �� ���� �� �Լ� (�������� ����)
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
		t1 = list[index - 1] + list[0] + list[index] + list[0]; // ���� �� ȥ�� �Դٰ���.
		t2 = list[1] + list[0] + list[index] + list[1]; // ���� ���� �� ���� ���� ���� �� ���ƿ��� ū �� ���� ���� �� ��°�� ���� �� ���ƿ�
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
		qsort(list, n, sizeof(int), compare); // ����
		if (n == 1) { // ���� �� ���� ���
			out << list[0] << endl;
		}
		else {
			// int one = Solve_One(list, n), two = Solve_Two(list, n); // �� ���� �ַ�� ����
			// out << (one > two ? two : one) << endl; // �� �� �� �� ���� �� ���
			out << Solve(list, n) << endl;
		}
	}
	inp.close();
	out.close();
	return 0;
}