#include<stdio.h>
#pragma warning(disable:4996)

long long int Solve(int n, int l, int r) {
	if (n == 1) { // 막대의 수가 1개이면
		if (l == 1 && r == 1) return 1;
		else return 0;
	}
	else { // 여러개이면
		if (l == 1 && r == 1) return 0; // impossible
		if (l + r >= n + 2) return 0; // impossible

		long long int Case[21][21][21] = { 0 };

		for (int i = 1; i <= n; i++) {
			Case[i][i][1] = 1;
			Case[i][1][i] = 1;
		}
		if (Case[n][l][r] == 1) return 1; // 위에 계산한 식으로 답이 도출될 경우 return.

		for (int i = 2; i <= n; i++)
			for (int j = 1; j <= l; j++)
				for (int k = 1; k <= r; k++)
					Case[i][j][k] = (Case[i - 1][j][k] * (i - 2)) + Case[i - 1][j - 1][k] + Case[i - 1][j][k - 1];
		return Case[n][l][r];
	}
}

int main() {
	FILE *inp = fopen("pole.inp", "r");
	FILE *out = fopen("pole.out", "w");
	int testcase;
	fscanf(inp, "%d\n", &testcase);
	int num, left, right;
	for (;testcase > 0; testcase--) {
		fscanf(inp, "%d %d %d", &num, &left, &right);
		fprintf(out, "%lli\n", Solve(num, left, right));
	}
	fclose(inp);
	fclose(out);
	return 0;
}
