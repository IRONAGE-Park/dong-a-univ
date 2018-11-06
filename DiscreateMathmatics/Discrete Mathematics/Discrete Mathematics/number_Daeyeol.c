#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

int Danswer(char *number, int size) {
	int i = 0;
	int D = 0;
	while (size > 1) {
		for (i = 0; (number[i] <= number[i + 1]) || (i == 0 && number[1] == '0'); i++);
		for (; i < size; i++) number[i] = number[i + 1];
		size--;
		if (size < 6) D += atoi(number);
		else D += atoi(number + size - 5);
	}
	return D;
}

int main() {
	FILE *inp = fopen("number.inp", "r");
	FILE *out = fopen("number.out", "w");
	char number[5000];
	int answer;
	while (1) {
			fscanf(inp, "%s", &number);
		if (number[0] == '0') break;
		int A = atoi(number + strlen(number) - 6);
		answer = (A - Danswer(number, strlen(number))) % 10000;
		if (answer < 0) answer = 10000 + answer;
		fprintf(out,"%d\n", answer);
	}
	return 0;
}