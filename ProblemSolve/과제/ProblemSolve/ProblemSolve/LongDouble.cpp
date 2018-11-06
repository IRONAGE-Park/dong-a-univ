#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#define MAXDIGITS 400
#define PLUS 1
#define MINUS -1

using namespace std;

typedef struct Bignum {
	char digit[MAXDIGITS];
	int signbit;
	int lastdigit;
	int point;
}Bignum;

int max(int a, int b) {
	return (a > b ? a : b);
}
int Abs(int a) {
	if (a > 0) return a;
	else return a * -1;
}
void add_Bignum(Bignum *a, Bignum *b, Bignum *c);
void sub_Bignum(Bignum *a, Bignum *b, Bignum *c);
void mul_Bignum(Bignum *a, Bignum *b, Bignum *c);
Bignum div_Bignum(Bignum *a, Bignum *b, Bignum *c);
void initialize_Bignum(Bignum *n);
void digit_shift(Bignum *n, int d);
int compare_Bignum(Bignum *a, Bignum *b);
void zero_justify(Bignum *n);
int position_Point(string num) {
	int i = num.length() - 1, cnt = 0;
	for (; i >= 0; i--, cnt++) {
		if (num[i] == '.')
			return cnt;
	}
	return MINUS;
}
void setNum(Bignum *n, string num) {
	initialize_Bignum(n);
	if (num[0] == '-') {
		n->signbit = MINUS;
		num = num.substr(1, num.length() - 1);
	}
	else n->signbit = PLUS; // 부호 처리.

	n->point = position_Point(num);
	if (n->point == 0) {
		num = '0' + num;
	}

	if (n->point != -1) {
		num = num.substr(0, num.length() - n->point - 1) + num.substr(num.length() - n->point, num.length());
	}  // 소수점 처리.

	n->lastdigit = num.length() - 1;
	for (int i = n->lastdigit, j = 0; i >= 0; i--, j++) {
		n->digit[i] = num[j] - 48;
	} // Bignum형식으로 변환.
	
	while (true) {
		if (n->digit[n->lastdigit] != 0) break;
		n->lastdigit--;
	}
	if (n->point == -1)
		n->point = 0;
}
string setString(Bignum *n) {
	string str = "";
	for (int i = n->lastdigit, j = 0; i >= 0; i--, j++) {
		str += n->digit[i] + 48;
		if (j == n->lastdigit - n->point)
			str += ".";
	}
	if (0 > n->lastdigit - n->point) {
		string cstr = "0.";
		for (int i = -1; i > n->lastdigit - n->point; i--) {
			cstr += "0";
		}
		str = cstr + str;
	}
	if (n->signbit == MINUS)
		str = "-" + str;
	return str;
}
string stringClean(string str) {
	for (int i = str.length() - 1; i >= 0; i--) {
		if (str[i] == '.') {
			str = str.substr(0, i);
			break;
		}
		else if (str[i] != '0') {
			str = str.substr(0, i + 1);
			break;
		}
	}
	int len = str.length();
	if (len == 2 && str[0] == '-' && str[1] == '0')
		str = "0";
	return str;
}
string Operation(Bignum op1, Bignum op2, string oper) {
	Bignum result;
	if (op1.point > op2.point) { // op2가 더 올림을 많이 했으면.
		digit_shift(&op2, op1.point - op2.point);
		op2.point = op1.point;
	}
	else {
		digit_shift(&op1, op2.point - op1.point);
		op1.point = op2.point;
	} // 소수점 맞추기
	
	if (oper.compare("+") == 0) {
		add_Bignum(&op1, &op2, &result);
		result.point = op1.point;
	} else if (oper.compare("-") == 0) {
		sub_Bignum(&op1, &op2, &result);
		result.point = op1.point;
	} else if (oper.compare("*") == 0) {
		mul_Bignum(&op1, &op2, &result);
		result.point = op1.point + op2.point;
	} else {
		div_Bignum(&op1, &op2, &result);
		result.point = Abs(op1.point - op2.point);
	}
	string str = setString(&result);
	str = stringClean(str);
	return str;
}
int main() {
	ifstream inp("LongDouble.inp");
	ofstream out("LongDouble.out");

	int testcase;
	inp >> testcase;
	while (testcase--) {
		string op1, op2, operater;
		inp >> op1 >> operater >> op2;
		Bignum oper1, oper2;
		setNum(&oper1, op1), setNum(&oper2, op2);
		out << Operation(oper1, oper2, operater) << "\n";
	}
	inp.close();
	out.close();
	return 0;
}

void initialize_Bignum(Bignum *n) {
	memset(n->digit, 0, MAXDIGITS);
	n->signbit = PLUS;
	n->lastdigit = 0;
}
void zero_justify(Bignum *n) {
	while ((n->lastdigit > 0) && (n->digit[n->lastdigit] == 0))
		n->lastdigit--;
	if ((n->lastdigit == 0) && (n->digit[0] == 0))
		n->signbit = PLUS;
}
int compare_Bignum(Bignum *a, Bignum *b) {
	if ((a->signbit == MINUS) && (b->signbit == PLUS)) return PLUS;
	if ((a->signbit == PLUS) && (b->signbit == MINUS)) return MINUS;

	if (b->lastdigit > a->lastdigit) return PLUS * a->signbit;
	if (a->lastdigit > b->lastdigit) return MINUS * a->signbit;

	for (int i = a->lastdigit; i >= 0; i--) {
		if (a->digit[i] > b->digit[i]) return MINUS * a->signbit;
		if (b->digit[i] > a->digit[i]) return PLUS * a->signbit;
	}
	return 0;
}
void digit_shift(Bignum *n, int d) {
	if ((n->lastdigit == 0) && (n->digit[0] == 0)) return;
	for (int i = n->lastdigit; i >= 0; i--)
		n->digit[i + d] = n->digit[i];
	for (int i = 0; i < d; i++) n->digit[i] = 0;
	n->lastdigit = n->lastdigit + d;
}
void add_Bignum(Bignum *a, Bignum *b, Bignum *c) {
	int carry;

	initialize_Bignum(c);

	if (a->signbit == b->signbit) c->signbit = a->signbit;
	else {
		if (a->signbit == MINUS) {
			a->signbit = PLUS;
			sub_Bignum(b, a, c);
			a->signbit = MINUS;
		}
		else {
			b->signbit = PLUS;
			sub_Bignum(a, b, c);
			b->signbit = MINUS;
		}
		return;
	}
	c->lastdigit = max(a->lastdigit, b->lastdigit) + 1;
	carry = 0;
	for (int i = 0; i <= (c->lastdigit); i++) {
		c->digit[i] = (char)(carry + a->digit[i] + b->digit[i]) % 10;
		carry = (carry + a->digit[i] + b->digit[i]) / 10;
	}
	zero_justify(c);
}
void sub_Bignum(Bignum *a, Bignum *b, Bignum *c) {
	int borrow;
	int v;

	initialize_Bignum(c);

	if ((a->signbit == MINUS) || (b->signbit == MINUS)) {
		b->signbit = b->signbit * MINUS;
		add_Bignum(a, b, c);
		b->signbit = b->signbit * MINUS;
		return;
	}

	if (compare_Bignum(a, b) == PLUS) {
		sub_Bignum(b, a, c);
		c->signbit = MINUS;
		return;
	}
	c->lastdigit = max(a->lastdigit, b->lastdigit);
	borrow = 0;

	for (int i = 0; i <= (c->lastdigit); i++) {
		v = (a->digit[i] - borrow - b->digit[i]);
		if (a->digit[i] > 0)
			borrow = 0;
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}
		c->digit[i] = (char)v % 10;
	}
	zero_justify(c);
}
void mul_Bignum(Bignum *a, Bignum *b, Bignum *c) {
	Bignum row;
	Bignum tmp;

	initialize_Bignum(c);

	row = *a;
	for (int i = 0; i <= b->lastdigit; i++) {
		for (int j = 1; j <= b->digit[i]; j++) {
			add_Bignum(c, &row, &tmp);
			*c = tmp;
		}
		digit_shift(&row, 1);
	}
	c->signbit = a->signbit * b->signbit;
	zero_justify(c);
}
Bignum div_Bignum(Bignum *a, Bignum *b, Bignum *c) {
	Bignum row;
	Bignum tmp;
	int asign, bsign;

	initialize_Bignum(c);
	c->signbit = a->signbit * b->signbit;

	asign = a->signbit;
	bsign = b->signbit;

	a->signbit = PLUS;
	b->signbit = PLUS;

	initialize_Bignum(&row);
	initialize_Bignum(&tmp);

	c->lastdigit = a->lastdigit;

	for (int i = a->lastdigit; i >= 0; i--) {
		digit_shift(&row, 1);
		row.digit[0] = a->digit[i];
		c->digit[i] = 0;
		while (compare_Bignum(&row, b) != PLUS) {
			c->digit[i]++;
			sub_Bignum(&row, b, &tmp);
			row = tmp;
		}
	}
	zero_justify(c);
	a->signbit = asign;
	b->signbit = bsign;
	return row;
}