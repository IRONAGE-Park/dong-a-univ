#include<stdio.h>
#pragma warning(disable:4996)

typedef struct Rd {
	int right;
	int down;
}Rd;

typedef struct Lu {
	int left;
	int up;
}Lu;

Rd data[100][100];
int M, N, L, G;
Lu dis[100][100][200];

void Scan(FILE *inp) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N - 1; j++) {
			fscanf(inp, "%d", &data[i][j].right);
		}
	}
	for (int i = 0; i < M - 1; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(inp, "%d", &data[i][j].down);
		}
	}
	for (int i = 1; i < N; i++) {
		dis[0][i][0].left = dis[0][i - 1][0].left + data[0][i - 1].right;
	}
	for (int i = 1; i < M; i++) {
		dis[i][0][0].up = dis[i - 1][0][0].up + data[i - 1][0].down;
	}
}

int minimum(int a, int b) {
	if (a == 0 && b == 0) {
		return 10000000;
	}
	else if (a == 0) {
		return b;
	}
	else if (b == 0) {
		return a;
	}
	return a < b ? a : b;
}

int main() {
	FILE *inp = fopen("drive.inp", "r");
	FILE *out = fopen("drive.out", "w");
	int testcase;
	fscanf(inp,"%d", &testcase);
	for (int t = 0; t < testcase; t++) {
		fscanf(inp,"%d %d %d %d", &M, &N, &L, &G);
		Scan(inp);
		int cnt = 2, check = 0;
		for (int i = 1; i < M; i++) {
			for (int j = 1; j < N; j++) {
				for (int k = 1; k <= cnt; k++) {
					dis[i][j][k].left = minimum(dis[i][j - 1][k].left, dis[i][j - 1][k - 1].up) + data[i][j - 1].right;
					dis[i][j][k].up = minimum(dis[i - 1][j][k].up, dis[i - 1][j][k - 1].left) + data[i - 1][j].down;
					if (dis[M - 1][N - 1][k].left <= G && dis[M - 1][N - 1][k].left != 0 && check == 0) {
						fprintf(out, "%d\n", ((M + N - 2)*L) + k);
						check = 1;
					}
					if (dis[M - 1][N - 1][k].up <= G && dis[M - 1][N - 1][k].up != 0 && check == 0) {
						fprintf(out, "%d\n", ((M + N - 2)*L) + k);
						check = 1;
					}
				}
			}
			cnt += 2;
		}
		if (check == 0) fprintf(out,"-1\n");
		cnt = 0;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k <= cnt; k++) {
					dis[i][j][k].left = 0;
					dis[i][j][k].up = 0;
				}
			}
			cnt += 2;
		} // ÃÊ±âÈ­
	}
	fclose(inp);
	fclose(out);
	return 0;
}