#include<stdio.h>
#pragma warning(disable:4996)

char answer[100][5000][4], num[1000][4];

int strikegame(char number[4], char ed[4]) {
	int i, strike = 0;
	for (i = 0; i < 4; i++) {
		if (number[i] == ed[i]) {
			strike++;
		}
	}
	return strike;
}

int ballgame(char number[4], char ed[4]) {
	int i, j, ball = 0;
	for (i = 0; i < 4; i++) {
		if (number[i] != ed[i]) {
			for (j = 0; j < 4; j++) {
				if (i != j&&number[i] == ed[j]) {
					ball++;
				}
			}
		}
	}
	return ball;
}

int main() {
	FILE *inp = fopen("numgame.inp", "r");
	FILE *out = fopen("numgame.out", "w");
	int repeat, question, strike, ball;
	int i = 0, j = 0, k = 0, l = 0,firstcount = 0, count = 0;
	char first, second, third, fourth;

	fscanf(inp, "%d\n", &repeat);         // 테스트케이스 수 입력
	for (first = '1'; first <= '9'; first++) {
		for (second = '1'; second <= '9'; second++) {
			for (third = '1'; third <= '9'; third++) {
				for (fourth = '1'; fourth <= '9'; fourth++) {
					if (first != second&&first != third&&first != fourth&&second != third&&second != fourth&&third != fourth) {
						answer[0][firstcount][0] = first;
						answer[0][firstcount][1] = second;
						answer[0][firstcount][2] = third;
						answer[0][firstcount][3] = fourth;
						firstcount++;
					}
				}
			}
		}
	}          // 모든 경우의 수 입력
	int cnt;
	
	for (i = 0; i < repeat; i++) {
		fscanf(inp, "%d\n", &question);
		count = firstcount;
		for (j = 0; j < question; j++) {
			fscanf(inp, "%s%d%d\n", &num[j], &strike, &ball);
			cnt = 0;
			for (k = 0; k < count; k++) {
				if (strike == strikegame(answer[j][k], num[j]) && ball == ballgame(answer[j][k], num[j])) {
					answer[j + 1][cnt][0] = answer[j][k][0];
					answer[j + 1][cnt][1] = answer[j][k][1];
					answer[j + 1][cnt][2] = answer[j][k][2];
					answer[j + 1][cnt][3] = answer[j][k][3];
					cnt++;
				}
			}
			count = cnt;
		}                                              // DP

		fprintf(out,"%d\n", count);
		if (count <= 6) {
			for (k = 0; k < count; k++) {
				fprintf(out,"%c%c%c%c\n", answer[j][k][0], answer[j][k][1], answer[j][k][2], answer[j][k][3]);
			}
		}
		else {
			for (k = 0; k < 3; k++) {
				fprintf(out, "%c%c%c%c\n", answer[j][k][0], answer[j][k][1], answer[j][k][2], answer[j][k][3]);
			}
			for (k = 3; k > 0; k--) {
				fprintf(out, "%c%c%c%c\n", answer[j][count - k][0], answer[j][count - k][1], answer[j][count - k][2], answer[j][count - k][3]);
			}
		}
	}                              // 출력

	fclose(inp);
	fclose(out);
	return 0;
}