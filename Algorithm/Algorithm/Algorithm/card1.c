#include<stdio.h>
#pragma warning(disable:4996)
#define MAX 10000
#define Min(a,b) (a > b ? b : a)
int num, Alice[MAX][MAX], Robot[MAX][MAX];

int cal() {
	for (int j = 1; j < num; j++) {
		for (int i = 0; i + j < num; i++) {
			Robot[i][j + i] = Min(Alice[i][j + i - 1], Alice[i + 1][j + i]);
			Alice[i][j + i] = (Alice[i][j + i - 1] + Robot[i][j + i - 1] + Alice[j + i][j + i]) - Robot[i][j + i];
		}
	}
	return Alice[0][num - 1];
}

int main() {
	FILE *inp = fopen("card.inp", "r");
	FILE *out = fopen("card.out", "w");

	int testcase;
	fscanf(inp, "%d", &testcase);
	while (testcase--) {
		fscanf(inp, "%d", &num);
		for (int i = 0; i < num; i++) fscanf(inp, "%d", &Alice[i][i]);
		int answer = cal();
		fprintf(out, "%d\n", answer);
	}
	fclose(inp);
	fclose(out);
	return 0;
}