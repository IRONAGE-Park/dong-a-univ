#include<iostream>
#include<fstream>
#include<string>
// Not Complete.
using namespace std;

int index; // ���� �ε���.

bool CheckSlump(string str) { // ������ Ȯ��.
	if (str[index] == 'F') {
		while (str[index] == 'F')
			index--;
		if ((str[index] == 'D' || str[index] == 'E')) { // F ���� ������ D Ȥ�� F�̸�
			index--;
			if (str[index] == 'F') { // �ٽ� F�� �����Ǹ�
				if (CheckSlump(str)) // �ٽ� ������ üũ
					return true;
			}
			else // �������� ������ ������ H Ȥ�� C�� ������
				return true;
		}
	}
	return false;
}

bool CheckSlimp(string str) { // ������ Ȯ��.
	if (str[index] == 'C') {
		index--;
		if (str[index] == 'C' || str[index] == 'H') { // �ٽ� �������� ������
			if (CheckSlimp(str)) {
				if (index >= 0 &&str[index] == 'B') { // �������� ����
					index--;
					if (str[index] == 'A') {
						index--;
						return true;
					}
				}
			}
		}
		else if (str[index] == 'G') { // �������� ������
			index--;
			if (CheckSlump(str)) {
				if (str[index] == 'A') {
					index--;
					return true;
				}
			}
		}
	}
	else if (str[index] == 'H') {
		index--;
		if (str[index] == 'A') {
			index--;
			return true;
		}
	}
	return false;
}

int main() {
	ifstream inp("Slurpys.inp");
	ofstream out("Slurpys.out");
	int n;
	inp >> n;
	out << "SLURPYS OUTPUT\n";
	while (n--) {
		bool slurpy = false;
		string str;
		inp >> str;
		int length = str.length(); // ���ڿ��� ����.
		if (str[0] != 'A' || str[length - 1] != 'G') // ù ���ڰ� A�� �ƴϰų� ������ ���ڰ� G�� �ƴϸ� Slurpy�� �� ����.
			out << "NO\n";
		else { // �ּ� ������ �������� ���
			index = length - 2;
			if (CheckSlump(str)) { // ������ �ڸ����� �������� �����ϸ�,
				if (CheckSlimp(str)) { // �������� ù�ڸ� - 1 ���� �������� �����ϸ�.
					if (index == -1) { // �������� �������� 0�̸�
						slurpy = true;
					}
				}
			}
			if (slurpy)
				out << "YES\n";
			else
				out << "NO\n";
		}
	}
	out << "END OF OUTPUT\n";
	inp.close();
	out.close();
	return 0;
}