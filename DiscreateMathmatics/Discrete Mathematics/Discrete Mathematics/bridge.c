#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

void card(char player[13][2]){
	int i, j = 0, count = 0;
	int queue1[13][13], queue2[4][13], num1[13] = { 0 }, num2[4] = { 0 };
	char temp[13][2];

	for (i = 0; i < 13; i++) {
		if (player[i][1] == '2')queue1[0][num1[0]] = i, num1[0]++;
		else if (player[i][1] == '3')queue1[1][num1[1]] = i, num1[1]++;
		else if (player[i][1] == '4')queue1[2][num1[2]] = i, num1[2]++;
		else if (player[i][1] == '5')queue1[3][num1[3]] = i, num1[3]++;
		else if (player[i][1] == '6')queue1[4][num1[4]] = i, num1[4]++;
		else if (player[i][1] == '7')queue1[5][num1[5]] = i, num1[5]++;
		else if (player[i][1] == '8')queue1[6][num1[6]] = i, num1[6]++;
		else if (player[i][1] == '9')queue1[7][num1[7]] = i, num1[7]++;
		else if (player[i][1] == 'T')queue1[8][num1[8]] = i, num1[8]++;
		else if (player[i][1] == 'J')queue1[9][num1[9]] = i, num1[9]++;
		else if (player[i][1] == 'Q')queue1[10][num1[10]] = i, num1[10]++;
		else if (player[i][1] == 'K')queue1[11][num1[11]] = i, num1[11]++;
		else if (player[i][1] == 'A')queue1[12][num1[12]] = i, num1[12]++;
	}
	for (i = 0; i < 13; i++) {
		for (j = 0; j < num1[i]; j++) {
			temp[count][1] = player[queue1[i][j]][1];
			temp[count][0] = player[queue1[i][j]][0];
			count++;
		}
	}                              // 옮기기
	count = 0;
	for (i = 0; i < 13; i++) {
		if (temp[i][0] == 'C')queue2[0][num2[0]] = i, num2[0]++;
		else if (temp[i][0] == 'D')queue2[1][num2[1]] = i, num2[1]++;
		else if (temp[i][0] == 'S')queue2[2][num2[2]] = i, num2[2]++;
		else if (temp[i][0] == 'H')queue2[3][num2[3]] = i, num2[3]++;
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < num2[i]; j++) {
			player[count][1] = temp[queue2[i][j]][1];
			player[count][0] = temp[queue2[i][j]][0];
			count++;
		}
	}                              // 옮기기
                                  // 출력 하기
}

int main() {
	FILE *inp = fopen("bridge.inp", "r");
	FILE *out = fopen("bridge.out", "w");
	int i, j;
	int num[13] = { 13 };
	char player;
	char N[13][2], E[13][2], S[13][2], W[13][2];
	while (1) {
		fscanf(inp, "%c\n", &player);
		if (player == '#') break;
		for (i = 0; i < 13; i++) {
			if (player == 'N') {
				if (i == 6) {
					fscanf(inp, "%c%c%c%c\n", &E[i][0], &E[i][1], &S[i][0], &S[i][1]);
					fscanf(inp, "%c%c%c%c", &W[i][0], &W[i][1], &N[i][0], &N[i][1]);
					continue;
				}
				fscanf(inp, "%c%c%c%c%c%c%c%c", &E[i][0], &E[i][1], &S[i][0], &S[i][1], &W[i][0], &W[i][1], &N[i][0], &N[i][1]);
			}
			else if (player == 'E') {
				if (i == 6) {
					fscanf(inp, "%c%c%c%c\n", &S[i][0], &S[i][1], &W[i][0], &W[i][1]);
					fscanf(inp, "%c%c%c%c", &N[i][0], &N[i][1], &E[i][0], &E[i][1]);
					continue;
				}
				fscanf(inp, "%c%c%c%c%c%c%c%c", &S[i][0], &S[i][1], &W[i][0], &W[i][1], &N[i][0], &N[i][1], &E[i][0], &E[i][1]);
			}
			else if (player == 'S') {
				if (i == 6) {
					fscanf(inp, "%c%c%c%c\n", &W[i][0], &W[i][1], &N[i][0], &N[i][1]);
					fscanf(inp, "%c%c%c%c", &E[i][0], &E[i][1], &S[i][0], &S[i][1]);
					continue;
				}
				fscanf(inp, "%c%c%c%c%c%c%c%c", &W[i][0], &W[i][1], &N[i][0], &N[i][1], &E[i][0], &E[i][1], &S[i][0], &S[i][1]);
			}
			else if (player == 'W') {
				if (i == 6) {
					fscanf(inp, "%c%c%c%c\n", &N[i][0], &N[i][1], &E[i][0], &E[i][1]);
					fscanf(inp, "%c%c%c%c", &S[i][0], &S[i][1], &W[i][0], &W[i][1]);
					continue;
				}
				fscanf(inp, "%c%c%c%c%c%c%c%c", &N[i][0], &N[i][1], &E[i][0], &E[i][1], &S[i][0], &S[i][1], &W[i][0], &W[i][1]);
			}
		}                             // 입력 받기
		fscanf(inp, "%c", &player);
		card(S);
		card(W);
		card(N);
		card(E);
		for (i = 0; i < 4; i++) {
			if (i == 0) fprintf(out, "S: ");
			else if (i == 1) fprintf(out, "W: ");
			else if (i == 2) fprintf(out, "N: ");
			else fprintf(out, "E: ");
			for (j = 0; j < 13; j++) {
				if (i == 0) fprintf(out, "%c%c", S[j][0], S[j][1]);
				else if (i == 1) fprintf(out, "%c%c", W[j][0], W[j][1]);
				else if (i == 2) fprintf(out, "%c%c", N[j][0], N[j][1]);
				else fprintf(out, "%c%c", E[j][0], E[j][1]);
				if (j != 12) fprintf(out, " ");
			}
			fprintf(out,"\n");
		}                              // 출력 하기
	}
	fclose(inp);
	fclose(out);
	return 0;
}