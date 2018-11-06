#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#pragma warning(disable:4996)
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
	n->signbit;
	n->lastdigit = num.length() - 1;
	for (int i = n->lastdigit, j = 0; i >= 0; i--, j++) {
		n->digit[i] = num[j] - 48;
	}
}
string toString(int val) {
	string str = "";
	bool check = false;
	if (val >= 100) {
		str += (val / 100) + 48;
		val %= 100;
		check = true;
	}
	if (val >= 10 || check) {
		str += (val / 10) + 48;
		val %= 10;
		check = true;
	}
	if (val >= 0 || check) {
		str += val + 48;
	}

	return str;
}
string setString(Bignum *n) {
	string str = "";
	for (int i = n->lastdigit; i >= 0; i--) {
		if (n->lastdigit >= 1) {
			str += ((n->digit[i] * 10) + n->digit[i - 1]) + 55;
			i--;
		}
		else str += n->digit[i] + 48;
	}
	return str;
}
Bignum changeDec(string num, int from) {
	Bignum sum, com, result, x;
	setNum(&sum, "0");
	setNum(&com, "1");
	setNum(&x, toString(from));

	for (int i = num.length() - 1; i >= 0; i--) {
		Bignum sumNum;
		int val;
		if (num[i] >= 'A') val = num[i] - 55;
		else val = num[i] - 48;
		setNum(&sumNum, toString(val));
		mul_Bignum(&sumNum, &com, &result);
		sumNum = result;
		add_Bignum(&sum, &sumNum, &result);
		sum = result;
		mul_Bignum(&com, &x, &result);
		com = result;
	}
	return sum;
}
string changeN(Bignum *num, int to) {
	string str = "";
	Bignum x = *num, div, result, mod;
	setNum(&div, toString(to));
	while (compare_Bignum(&x, &div) != PLUS) {
		mod = div_Bignum(&x, &div, &result);
		str += setString(&mod);
		x = result;
	}
	Bignum cp;
	setNum(&cp, "0");
	if (compare_Bignum(&x, &cp) == MINUS) {
		str += setString(&x);
	}
	return str;
}
string baseconvert(string num, int from, int to) {
	Bignum decimal = changeDec(num, from);
	string str = changeN(&decimal, to);
	return str;
}
string reverse(string str) {
	string r_str = "";
	for (int i = str.length() - 1; i >= 0; i--) {
		r_str += str[i];
	}
	return r_str;
}

int main() {
	ifstream inp("BaseConversion.inp");
	ofstream out("BaseConversion.out");
	Bignum num1, num2, r;
	while (true) {
		string num;
		int pre, post;
		inp >> num >> pre >> post;
		if (!num.compare("0") && !pre && !post)
			break;
		num = baseconvert(num, pre, post);

		out << reverse(num) << '\n';
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