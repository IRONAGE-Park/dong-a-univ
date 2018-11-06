#include<stdio.h>
#pragma warning(disable:4996)
#define MAX(a,b) a > b ? a : b

int main() {
	FILE *inp = fopen("stickers.inp", "r");
	FILE *out = fopen("stickers.out", "w");

	int testcase;
	fscanf(inp, "%d", &testcase);

	while (testcase--) {
		int sticker[2][100000] = { 0 }, num;
		fscanf(inp, "%d\n", &num);
		for (int i = 0; i < 2; i++) for (int j = 0; j < num; j++) fscanf(inp, "%d", &sticker[i][j]);
		sticker[0][1] = sticker[1][0] + sticker[0][1], sticker[1][1] = sticker[0][0] + sticker[1][1]; 
		// 초기 값 설정
		for (int i = 2; i < num; i++) {
			sticker[0][i] += MAX(sticker[1][i - 2], sticker[1][i - 1]); // 위쪽 라인
			sticker[1][i] += MAX(sticker[0][i - 2], sticker[0][i - 1]); // 아래 라인
		}
		fprintf(out, "%d\n", MAX(sticker[0][num - 1], sticker[1][num - 1]));
	}
	fclose(inp);
	fclose(out);
	return 0;
}