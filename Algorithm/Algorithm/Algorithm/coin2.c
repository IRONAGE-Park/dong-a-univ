#include<stdio.h>
#pragma warning(disable:4996)
#define MAX 103

int bucket[3][MAX][MAX][MAX];

void Solution() {
	for (int i = 3; i < MAX; i++) {
		for (int j = 3; j < MAX; j++) {
			for (int k = 3; k < MAX; k++) {
				if (i == 3 && j == 3 && k == 3) continue;
				else {
					if (bucket[1][i - 1][j][k] == -1 && bucket[2][i - 1][j][k] == -1) bucket[0][i][j][k] = 1;
					else if (bucket[1][i][j - 1][k] == -1 && bucket[2][i][j - 1][k] == -1) bucket[0][i][j][k] = 1;
					else if (bucket[1][i][j][k - 1] == -1 && bucket[2][i][j][k - 1] == -1) bucket[0][i][j][k] = 1;
					else bucket[0][i][j][k] = -1;
					// 1개를 뽑았을 때
					
					if (bucket[0][i - 2][j][k] == -1 && bucket[2][i - 2][j][k] == -1) bucket[1][i][j][k] = 1;
					else if (bucket[0][i][j - 2][k] == -1 && bucket[2][i][j - 2][k] == -1) bucket[1][i][j][k] = 1;
					else if (bucket[0][i][j][k - 2] == -1 && bucket[2][i][j][k - 2] == -1) bucket[1][i][j][k] = 1;
					else bucket[1][i][j][k] = -1;
					// 2개를 뽑았을 때

					if (bucket[0][i - 3][j][k] == -1 && bucket[1][i - 3][j][k] == -1) bucket[2][i][j][k] = 1;
					else if (bucket[0][i][j - 3][k] == -1 && bucket[1][i][j - 3][k] == -1) bucket[2][i][j][k] = 1;
					else if (bucket[0][i][j][k - 3] == -1 && bucket[1][i][j][k - 3] == -1) bucket[2][i][j][k] = 1;
					else bucket[2][i][j][k] = -1;
					// 3개를 뽑았을 때
				}
			}
		}
	}
}

int main() {
	FILE *inp = fopen("coin.inp", "r");
	FILE *out = fopen("coin.out", "w");

	int testcase;
	fscanf(inp, "%d", &testcase);
	int b[3];
	Solution();
	while (testcase--) {
		fscanf(inp, "%d %d %d", &b[0], &b[1], &b[2]);
		fprintf(out, "(%d %d %d) : ", b[0], b[1], b[2]);
		b[0] += 3, b[1] += 3, b[2] += 3;
		if (bucket[0][b[0]][b[1]][b[2]] == 1 || bucket[1][b[0]][b[1]][b[2]] == 1 || bucket[2][b[0]][b[1]][b[2]] == 1) fprintf(out, "1\n");
		else fprintf(out, "-1\n");
	}

	fclose(inp);
	fclose(out);
	return 0;
}