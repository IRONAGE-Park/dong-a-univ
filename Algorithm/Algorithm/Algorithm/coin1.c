#include<stdio.h>
#pragma warning(disable:4996)
#define MAX 103

int bucket[MAX][MAX][MAX];

void Solution() {
	for (int i = 3; i < MAX; i++) {
		for (int j = 3; j < MAX; j++) {
			for (int k = 3; k < MAX; k++) {
				if (i == 3 && j == 3 && k == 3) bucket[i][j][k] = 0;
				else if (bucket[i - 1][j][k] == -1 || bucket[i][j - 1][k] == -1 || bucket[i][j][k - 1] == -1) {
					bucket[i][j][k] = 1;
				}
				else {
					if (bucket[i - 2][j][k] == -1 || bucket[i][j - 2][k] == -1 || bucket[i][j][k - 2] == -1) {
						bucket[i][j][k] = 1;
					}
					else {
						if (bucket[i - 3][j][k] == -1 || bucket[i][j - 3][k] == -1 || bucket[i][j][k - 3] == -1) {
							bucket[i][j][k] = 1;
						}
						else {
							bucket[i][j][k] = -1;
						}
					}
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
		fprintf(out, "(%d %d %d) : %d\n", b[0], b[1], b[2], bucket[b[0] + 3][b[1] + 3][b[2] + 3]);
	}
	fclose(inp);
	fclose(out);
	return 0;
}