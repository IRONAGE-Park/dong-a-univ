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

void main() {
	int question, strike, ball;
	int i = 0, j = 0, k = 0, l = 0, firstcount = 0, count = 0;
	char first, second, third, fourth;

	for (first = '0'; first <= '9'; first++) {
		for (second = '0'; second <= '9'; second++) {
			for (third = '0'; third <= '9'; third++) {
				for (fourth = '0'; fourth <= '9'; fourth++) {
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
	}          // 모든 경우의 수
	int cnt;
	count = firstcount;
	while (1) {
		printf("%d번째 질문\n숫자 : ", j + 1);
		scanf("%s", &num[j]);
		printf("St 수 : ");
		scanf("%d", &strike);
		printf("Ba 수 : ");
		scanf("%d", &ball);
		printf("------------------------------------\n");
		if (strike == 4) {
			printf("정답\n\n*********************************************\n\n");
			printf("계속 하시겠습니까?(Yes = 1/No = 0)");
			scanf("%d\n", &question);
			if (question == 1) {
				j = 0, count = firstcount;
				continue;
			}
			else break;
		}
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
		j++;
		count = cnt;
		printf("\n모든 경우의 갯수 : %d\n", count);
		printf("\n다음 예상 답안 \n");
		for (k = 0; k < count; k++) {
			if (k == 1)break;
			printf("%c%c%c%c\n", answer[j][k][0], answer[j][k][1], answer[j][k][2], answer[j][k][3]);
		}
		printf("\n--------------------------------------------\n\n");
	}
}
