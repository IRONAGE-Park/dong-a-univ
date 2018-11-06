#include<iostream>
#include<fstream>

using namespace std;

int main() {
	ifstream inp("Snail.inp");
	ofstream out("Snail.out");
	double H, U, D, F; // H = �칰�� ����, U = �Ϸ絿�� �ö� �� �ִ� ����, D = �ڴµ��� �������� ����, F = �ǰ�����
	while (true) {
		inp >> H >> U >> D >> F;
		if (!H && !U && !D && !F) break; // ��� 0 => ������ input
		/* INPUT DATA */
		double now = U, point = U * F / 100; // ���� ���̿� �ǰ������� ���� ���� �� �ִ� ���� ���ҷ�.
		bool success = true; // ���� ����
		int day = 1; // Check���� �ɸ��� �� ��.
		while (now <= H) { // H �ʰ��� ����������
			now -= D; // D��ŭ ������
			U = U - point;
			if (U < 0) U = 0;
			if (now < 0) { // Ż�� ����
				success = false;
				break;
			}
			day++;
			/* ������� �Ϸ簡 ���� */
			now += U;
			/* �ٽ� �ö�*/
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