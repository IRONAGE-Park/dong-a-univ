#include<iostream>
#include<fstream>
#include<queue>
#include<cstring>
#define MAX 100000000

using namespace std;

typedef struct Build {
	int x;
	int index;
	int height;
	bool state; // true = start, false = end
}Build;
typedef struct Current {
	int x;
	int index;
	int height;
}Current;
bool operator<(Build a, Build b) {
	return a.x > b.x;
}
bool operator<(Current a, Current b) {
	return a.height < b.height;
}

priority_queue<Build> ready;
priority_queue<Current> sweep;

bool endIdx[MAX];

int main() {
	ifstream inp("Skyline.inp");
	ofstream out("Skyline.out");

	int n = 0, idx = 0;
	while (true) {
		int start = -1, height = -1, end = -1;
		inp >> start >> height >> end;

		if (!start && !height && !end) { // �� Testcase�� ���Ͽ� Input Data�� ���� ������ => Start to Building Scan
			out << "Test Case #" << ++n << " :";
			long long int area = 0; // �ǹ��� ����
			int last_x = 0, last_height = 0; // ������ x�� ��ġ�� ������ ����

			while (ready.size() != 0) {
				if (ready.top().state) { // ���� ���� ������.
					if (last_height <= ready.top().height) { // ���� ���̰� �� ������
						area += last_height * (ready.top().x - last_x); // ������ ������ x���� �� ������ �ǹ� ���� ����
						last_height = ready.top().height; // ���� �ǹ��� ���� ����
						last_x = ready.top().x; // ���������� ����� x�� ��ġ ����
					}
					sweep.push({ ready.top().x, ready.top().index, ready.top().height }); // SweepLine�� push
				}
				else { // �� ���� ������.
					endIdx[ready.top().index] = true; // �� ������ ����ߴٴ� ǥ��
					if (last_height == ready.top().height) { // ���� ���� �� ���� �ְ�����̸�
						area += last_height * (ready.top().x - last_x); // ������ ������ x���� �� ������ �ǹ� ���� ����
						last_x = ready.top().x; // ���������� ����� x�� ��ġ ����
					}
					while (!sweep.empty()) {
						if (!endIdx[sweep.top().index]) { // ���� ���� sweep�� ���������� �簢���� �ִٸ�.
							last_height = sweep.top().height;
							break;
						}
						else { // �簢���� �̹� ����� ���¶�� sweep���� ����
							sweep.pop();
						}
					}
					if (sweep.empty()) {
						out << " " << area; // ������ְ�
						area = 0, last_height = 0; // ���̴� 0, ���̴� 0
					}
				}
				ready.pop();
			}
			out << '\n';
			idx = 0;
			memset(endIdx, false, sizeof(endIdx));
			continue;
		}
		// queue�� input
		if (start == -1) break;
		ready.push({ start, idx, height, true }); // ������
		ready.push({ end, idx++, height, false }); // ����
	}
	inp.close();
	out.close();
	return 0;
}

/*
while (ready.size() != 0) {
	if (ready.top().state) { // ���� ���� ��������.
		if (last_height < ready.top().height) { // ���� ���̰� �� ������.
			area += last_height * (ready.top().x - last_x);
			last_height = ready.top().height;
			last_x = ready.top().x;
		}
		sweep.push({ ready.top().x, ready.top().index, ready.top().height }); // SweepLine�� push;
	}
	else { // �� ���� ������ ��
		endIdx[ready.top().index] = true; // ����� �ε��� üũ
		if (last_height == ready.top().height) { // ������ ���̿� ����Ǵ� �ǹ��� ���̰� ������
			if (sweep.top().index == ready.top().index) { // �ε������� ������ = ���� �ǹ��̸� ==> area�� ����
				area += last_height * (ready.top().x - last_x);
				last_x = ready.top().x;
				while (endIdx[sweep.top().index]) {
					sweep.pop();
				}
				if (sweep.size() == 1) {
					out << " " << area;
					area = 0;
					last_height = 0;
				}
				else last_height = sweep.top().height;
			}
		}
	}
	ready.pop();
}
*/