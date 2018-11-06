#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define num 100

int main() {
	FILE *inp = fopen("frog.inp", "r");
	FILE *out = fopen("frog.out", "w");
	int repeat, i, j, N, D, west[num];
	int between, button = 0, now = 0, empty[num];
	int answer = 0;
	char size[num], trash;

	fscanf(inp, "%d\n", &repeat);
	for (i = 0; i < repeat; i++) {
		fscanf(inp, "%d %d\n", &N, &D);
		for (j = 0; j < N; j++) {
			fscanf(inp, "%c%c%d ", &size[j], &trash, &west[j]);
		}
		// 인풋파일 입력

		for (j = 0; j < N; j++) {
			if (size[j] == 'S' && button == 0) {
				button = 1;
			}
			else if (size[j] == 'S' && button == 1) {
				button = 0;
				between = west[j] - now;
				now = west[j];
				empty[j] = 1;
				if (answer <= between) answer = between;
			}
			else {
				button = 0;
				between = west[j] - now;
				now = west[j];
				if (answer <= between) answer = between;
			}

			if (j == N - 1) {                       // 마지막 돌을 밟았을 때
				between = D - now;
				if (answer <= between) answer = between;
			}
		}                           // 편도

		button = 0;
		now = 0;
		for (j = 0; j < N; j++) {
			if (empty[j] == 1) {
				if (j == N - 1) {                   // 마지막 돌을 밟았을 때
					between = D - now;
					if (answer <= between) answer = between;
				}
				continue;
			}
			between = west[j] - now;
			now = west[j];
			if (answer <= between) answer = between;

			if (j == N - 1) {                       // 마지막 돌을 밟았을 때
				between = D - now;
				if (answer <= between) answer = between;
			}
		}                           // 왕복

		for (j = 0; j < N; j++)empty[j] = 0, west[j] = 0, size[j] = 0;
		fprintf(out, "Case %d: %d\n", i+1, answer);
		between = 0, now = 0, button = 0, answer = 0;
	}
	fclose(inp);
	fclose(out);
	return 0;
}