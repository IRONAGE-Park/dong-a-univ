#include<iostream>
#include<fstream>
#include<string>
// Not Complete.
using namespace std;

int index; // 참조 인덱스.

bool CheckSlump(string str) { // 슬럼프 확인.
	if (str[index] == 'F') {
		while (str[index] == 'F')
			index--;
		if ((str[index] == 'D' || str[index] == 'E')) { // F 나열 이전에 D 혹은 F이면
			index--;
			if (str[index] == 'F') { // 다시 F가 나열되면
				if (CheckSlump(str)) // 다시 슬럼프 체크
					return true;
			}
			else // 슬럼프의 시작점 이전에 H 혹은 C가 있으면
				return true;
		}
	}
	return false;
}

bool CheckSlimp(string str) { // 슬림프 확인.
	if (str[index] == 'C') {
		index--;
		if (str[index] == 'C' || str[index] == 'H') { // 다시 슬림프가 나오면
			if (CheckSlimp(str)) {
				if (index >= 0 &&str[index] == 'B') { // 제약조건 설정
					index--;
					if (str[index] == 'A') {
						index--;
						return true;
					}
				}
			}
		}
		else if (str[index] == 'G') { // 슬럼프가 나오면
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
		int length = str.length(); // 문자열의 길이.
		if (str[0] != 'A' || str[length - 1] != 'G') // 첫 문자가 A가 아니거나 마지막 문자가 G가 아니면 Slurpy일 수 없음.
			out << "NO\n";
		else { // 최소 조건을 만족했을 경우
			index = length - 2;
			if (CheckSlump(str)) { // 마지막 자리부터 슬럼프가 존재하면,
				if (CheckSlimp(str)) { // 슬럼프의 첫자리 - 1 부터 슬림프가 존재하면.
					if (index == -1) { // 슬림프의 시작점이 0이면
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