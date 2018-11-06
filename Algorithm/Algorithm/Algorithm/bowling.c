#include<stdio.h>
#pragma warning(disable:4996)
#define MAX 10

typedef struct frame {
	int point;
	int bonusCnt;
	int first;
	int last;
	char state;
}frame;

int score(FILE *inp) { // 점수 계산
	frame game[10];
	int sum = 0, allCount = 0;
	for (int i = 0; i < MAX; i++) {
		fscanf(inp, "%d", &game[i].first);
		if (game[i].first == MAX) { // 스트라이크일 경우
			game[i].state = 'K';
			game[i].bonusCnt = 2;
			game[i].point = MAX;
			allCount += 2;
			for (int j = 1; j <= 2 && allCount != 0; j++) {
				if (game[i - j].bonusCnt == 2) { // 전 프레임이 스트라이크였을 경우
					game[i - j].point += MAX;
					game[i - j].bonusCnt = 1, allCount -= 1;
				}
				else if (game[i - j].bonusCnt == 1) {
					game[i - j].point += MAX;
					game[i - j].bonusCnt = 0, allCount -= 1;
				}
			}
		}
		else {
			fscanf(inp, "%d", &game[i].last);
			if (game[i].first + game[i].last == MAX) { // 스페어일 경우
				game[i].state = 'P';
				game[i].bonusCnt = 1;
				game[i].point = MAX;
				allCount += 1;
			}
			else game[i].point = game[i].first + game[i].last;

			for (int j = 1; j <= 2 && allCount != 0; j++) {
				if (game[i - j].bonusCnt == 2) { // 전 프레임이 스트라이크였을 경우
					game[i - j].point += game[i].first + game[i].last;
					game[i - j].bonusCnt = 0, allCount -= 2;
				}
				else if (game[i - j].bonusCnt == 1) {
					game[i - j].point += game[i].first;
					game[i - j].bonusCnt = 0, allCount -= 1;
				}
			}
		}
		if (i == MAX - 1 && game[i].point == 10) { // 마지막 보너스 프레임 계산
			int first, last;
			if (game[i].state == 'K') {
				fscanf(inp, "%d %d", &first, &last);
				game[i].point += first + last;
			}
			else {
				fscanf(inp, "%d", &first);
				game[i].point += first;
			}
			if (game[i - 1].bonusCnt == 1) {
				game[i - 1].point += first;
				game[i - 1].bonusCnt = 0, allCount -= 1;
			}
		}
	}
	for (int i = 0; i < MAX; i++) sum += game[i].point; // 합계
	return sum;
}

int main() {
	FILE *inp = fopen("bowling.inp", "r");
	FILE *out = fopen("bowling.out", "w");

	int num_game;
	fscanf(inp, "%d", &num_game);
	for (int i = 0; i < num_game; i++) fprintf(out, "%d\n", score(inp));

	fclose(inp);
	fclose(out);
	return 0;
}