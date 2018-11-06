#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#define MAX_SIZE 500

using namespace std;

class Bigint {
public:
	char dec[MAX_SIZE];
	int lastdec;
	int sign;

	Bigint() {
		memset(this->dec, '\0', MAX_SIZE);
		this->lastdec = 0;
		this->sign = 1;
	}
	Bigint add(Bigint *oper) {
		Bigint addNum;
		addNum.lastdec = (this->lastdec > oper->lastdec ? this->lastdec : oper->lastdec) + 1;
		int carry = 0;
		for (int i = 0; i <= addNum.lastdec; i++) {
			addNum.dec[i] = this->dec[i] + oper->dec[i] + carry;
			carry = addNum.dec[i] / 10;
			addNum.dec[i] %= 10;
		}
		while (addNum.dec[addNum.lastdec] == '\0') {
			addNum.lastdec--;
		}
		return addNum;
	}
	Bigint sub(Bigint oper);
	Bigint mul(Bigint oper);
	Bigint div(Bigint oper);
	int compare(Bigint *oper) {
		if (this->lastdec > oper->lastdec) return 1;
		else if (this->lastdec < oper->lastdec) return -1;
		else {
			for (int i = this->lastdec; i >= 0; i--) {
				if (this->dec[i] > oper->dec[i]) return 1;
				if (this->dec[i] < oper->dec[i]) return -1;
			}
			return 0;
		}
	}
	void setNum(string num) {
		for (int i = (int)num.length() - 1; i >= 0; i--) {
			dec[lastdec] = num[i] - 48;
			lastdec++;
		}
		lastdec--;
	}
	string getNum() {
		string num = "";
		for (int i = lastdec; i >= 0; i--) {
			num += dec[i] + 48;
		}
		return num;
	}
};

Bigint fibo[500];

void fibonachi() {
	fibo[0].setNum("1"); fibo[1].setNum("1");
	for (int i = 2; i < MAX_SIZE; i++) {
		fibo[i] = fibo[i - 1].add(&fibo[i - 2]);
	}
}

int Solution(Bigint op1, Bigint op2) {
	int cnt = 0, i;
	for (i = 1; fibo[i].compare(&op1) == -1; i++);
	for (; fibo[i].compare(&op2) <= 0; i++, cnt++);
	return cnt;
}

int main() {
	ifstream inp("Fibo.inp");
	ofstream out("Fibo.out");
	fibonachi();
	while (true) {
		Bigint range1, range2;
		string str1, str2;
		inp >> str1 >> str2;
		if (str1.compare("0") == 0 && str2.compare("0") == 0) break;
		range1.setNum(str1); range2.setNum(str2);
		out << Solution(range1, range2) << '\n';
	}
	inp.close();
	out.close();
	return 0;
}