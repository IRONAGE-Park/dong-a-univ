#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int seq, cnt, stack[1000], top, idx;
int arr[1000];

void toInt(string data) {
	while (seq--) {
		if (data[seq] == '(') { // ���� ��ȣ�� ���ÿ��� pop
			top--;
			arr[stack[top]] = cnt;
			cnt--;
		}
		else { // ������ ��ȣ�� �������� push
			stack[top] = idx;
			idx--, top++;
		}
	}
}

string toString(int left, int right) {
	for (int i = left; i < right; i++) {
		if (arr[i] == seq) {
			seq++; // ���� ������ �÷���
			string str = "(" + toString(left, i) + ")"; // ���� ����� ��� ��ȣ ���̿� �ְ�
			str += toString(i + 1, right); // ������ ����� ��� ��ȣ �����ʿ� �߰�
			return str;
		}
	}
	return "";
}

int main() {
	ifstream inp("Transform.inp");
	ofstream out("Transform.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int num, type;
		inp >> num >> type;
		out << num << " "; // ��� ������ ���߱� ���� �̸� ���.
		string str;
		
		if (type) { // type�� 1�� ��� -> ���ڿ��� �Է� �����ͷ� �־���.
			seq = (num * 2); // ���ʺ��� �������
			cnt = num, top = 0, idx = num - 1;
			inp >> str; // ���ڿ� �Է� ����.
			toInt(str);
			for (int i = 0; i < num; i++) out << arr[i] << " ";	// ���
		} else { // type�� 0�� ��� -> ���� �迭�� �Է� �����ͷ� �־���.
			seq = 1; // �켱 ù��° ������ 1
			for (int i = 0; i < num; i++) inp >> arr[i]; // �迭 �Է� ����.
			str = toString(0, num); // ��Ʈ������ ��ȯ
			for (int i = 0; i < str.length(); i++) out << str[i]; // ���
		}
		out << '\n';
	}
	inp.close();
	out.close();
	return 0;
}