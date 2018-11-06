#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#define MAXDIGITS 400
#define PLUS 1
#define MINUS -1

using namespace std;

typedef struct Bignum {
	char digit[MAXDIGITS];
	int signbit;
	int lastdigit;
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
void setNum(Bignum *n, string num) {
	initialize_Bignum(n);
	if (num[0] == '-') {
		n->signbit = MINUS;
		num = num.substr(1, num.length() - 1);
	}
	else n->signbit = PLUS; // 부호 처리.

	n->lastdigit = num.length() - 1;
	for (int i = n->lastdigit, j = 0; i >= 0; i--, j++) {
		n->digit[i] = num[j] - 48;
	} // Bignum형식으로 변환.

	
}
string setString(Bignum *n) {
	string str = "";
	for (int i = n->lastdigit; i >= 0; i--) {
		str += n->digit[i] + 48;
	}
	return str;
}
Bignum gcd(Bignum *a, Bignum *b) {
	Bignum div, r = div_Bignum(b, a, &div), zero;
	setNum(&zero, "0");
	if (compare_Bignum(&r, &zero) == 0)
		return *a;
	else
		return gcd(&r, a);
}

int main() {
	ifstream inp("Mid-term4.inp");
	ofstream out("Mid-term4.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		char op;
		string A, B, C, D;
		inp >> op >> A >> B >> C >> D;
		Bignum a, b, c, d;
		Bignum x, y, opA, opB, opC, opD, zero;
		setNum(&a, A), setNum(&b, B), setNum(&c, C), setNum(&d, D), setNum(&zero, "0");;
		switch (op) {
		case '+':
			mul_Bignum(&b, &d, &y), mul_Bignum(&a, &d, &opA), mul_Bignum(&c, &b, &opC);
			add_Bignum(&opA, &opC, &x); // 통분 후 계산.
			break;
		case '-':
			mul_Bignum(&b, &d, &y), mul_Bignum(&a, &d, &opA), mul_Bignum(&c, &b, &opC);
			sub_Bignum(&opA, &opC, &x); // 통분 후 계산.
			break;
		case '*':
			mul_Bignum(&a, &c, &x), mul_Bignum(&b, &d, &y);
			break;
		case '/':
			mul_Bignum(&a, &d, &x), mul_Bignum(&b, &c, &y);
			break;
		}
		Bignum div, mod = div_Bignum(&x, &y, &div);
		if (!compare_Bignum(&mod, &zero)) { // 약분이 되면
			if (div.signbit == MINUS) out << "- ";
			string str = setString(&div);
			out << str + ' ' << 1;
		}
		else {
			if (x.signbit == MINUS) out << "- ";
			div = gcd(&x, &y);
			Bignum newX, newY;
			div_Bignum(&x, &div, &newX), div_Bignum(&y, &div, &newY);
			string strX = setString(&newX), strY = setString(&newY);
			out << strX + ' ' << strY;
		}
		out << '\n';
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
	if ((a->signbit == MINUS) && (b->signbit == PLUS)) return PLUS; // a가 더 작으면 1
	if ((a->signbit == PLUS) && (b->signbit == MINUS)) return MINUS;// a가 더 크면 -1

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