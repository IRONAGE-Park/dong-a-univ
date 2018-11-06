#include<stdio.h>
#pragma warning(disable:4996)
#define INF -9999999
#define FULL 1000
#define MAX(a,b) a > b ? a : b

typedef struct Data {
	int num;
	int check;
}Data;

int num;

int Compare(int a, int b, int c) { // 3개 비교
	return a > b ? MAX(a, c) : MAX(b, c);
}

int sol(int card[]) { // 오답
	Data data[FULL] = { 0 };
	if (num == 4) return MAX(card[0] + card[3], card[1] + card[3]);
	else {
		data[0].num = card[0];
		data[1].num = card[1];
		data[2].num = card[2];
		data[3].num = MAX(data[0].num + card[3], data[1].num + card[3]);
		data[4].num = Compare(data[0].num + card[4], data[1].num + card[4], data[2].num + card[4]);
		if (data[3].num == data[1].num + card[3]) data[3].check = 1;
		if (data[4].num == data[2].num + card[4]) data[4].check = 1; // 기본 값 셋팅
		for (int i = 5; i < num; i++) {
			if (data[i - 2].check == 1) data[i].num = MAX(data[i - 3].num + card[i], data[i - 4].num + card[i]);
			else {
				data[i].num = Compare(data[i - 2].num + card[i], data[i - 3].num + card[i], data[i - 4].num + card[i]);
				if (data[i].num == data[i - 2].num + card[i]) {
					if (data[i].num == data[i - 3].num + card[i] || data[i].num == data[i - 4].num + card[i]) continue;
					else data[i].check = 1;
				}
			}
		}
		return data[num - 1].num;
	}
}

int sol_reverse(int card[]) { // 오답
	Data data[FULL] = { 0 };
	data[num - 2].num = INF;
	if (num == 4) return MAX(card[0] + card[3], card[1] + card[3]);
	else { // 5 이상일 경우
		data[num - 1].num = card[num - 1];
		data[num - 3].num = data[num - 1].num + card[num - 3], data[num-3].check = 1;
		data[num - 4].num = data[num - 1].num + card[num - 4];
		data[num - 5].num = data[num - 1].num + card[num - 5]; // 기본값 셋팅
		for (int i = num - 6; i >= 0; i--) {
			if (data[i + 2].check == 1 || i == 0) data[i].num = MAX(data[i + 3].num + card[i], data[i + 4].num + card[i]); // i + 2 번째 카드가 i+2번째 카드를 선택하여 왔을 경우
			else {
				data[i].num = Compare(data[i + 2].num + card[i], data[i + 3].num + card[i], data[i + 4].num + card[i]);
				if (data[i].num == data[i + 2].num + card[i]) {
					if (data[i].num == data[i + 3].num + card[i] || data[i].num == data[i + 4].num + card[i]) continue;
					else data[i].check = 1;
				}
			}
		}
		return Compare(data[0].num, data[1].num, data[2].num);
	}
}

int solution(int card[]) {
	int data[FULL][3] = { 0 };
	if (num == 4) return MAX(card[0] + card[3], card[1] + card[3]);
	else {
		for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) data[i][j] = card[i]; // Index[0] to Index[2]
		data[3][0] = card[1] + card[3], data[3][1] = card[0] + card[3], data[3][2] = INF;
		data[4][0] = card[2] + card[4], data[4][1] = card[1] + card[4], data[4][2] = card[0] + card[4];
		for (int i = 5; i < num; i++) {
			data[i][0] = MAX(data[i - 2][1] + card[i], data[i - 2][2] + card[i]);
			data[i][1] = Compare(data[i - 3][0] + card[i], data[i - 3][1] + card[i], data[i - 3][2] + card[i]);
			data[i][2] = Compare(data[i - 4][0] + card[i], data[i - 4][1] + card[i], data[i - 4][2] + card[i]);
		}
		return Compare(data[num - 1][0], data[num - 1][1], data[num - 1][2]);
	}
}

int selection(FILE *inp) {
	int card[FULL];
	for (int i = 0; i < num; i++) fscanf(inp, "%d", &card[i]);
	return solution(card);
}

int main() {
	FILE *inp = fopen("card.inp", "r");
	FILE *out = fopen("card.out", "w");

	int testcase;
	fscanf(inp, "%d", &testcase);
	while (testcase--) {
		fscanf(inp, "%d\n", &num);
		fprintf(out, "%d\n", selection(inp));
	}
	fclose(inp);
	fclose(out);
	return 0;
}