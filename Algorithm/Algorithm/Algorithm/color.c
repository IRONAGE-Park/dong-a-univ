#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

typedef struct data {
	int use;
	int total;
}Data;

struct table {
	int first;
	int last;
};
int car_num[30], s1len, s2len;
struct table table[3][30]; // A = 65
Data data[5010][5010];

Data Min(Data temp1, Data temp2) {
	if (temp1.total < temp2.total)
		return temp1;
	else return temp2;
}

void init(char str1[], char str2[]) {
	s1len = strlen(str1), s2len = strlen(str2);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 26; j++) {
			table[i][j].first = -1, table[i][j].last = -1;
		}
	}
	for (int i = 0; i < s2len; i++) {
		for (int j = 0; j < s1len; j++) {
			data[i][j].total = 0, data[i][j].use = 0;
		}
	}
} // 초기화
void input_table(char str1[], char str2[]) {
	for (int i = 0; i < s1len; i++) {
		if (table[0][str1[i] - 65].first == -1) table[0][str1[i] - 65].first = i + 1, table[0][str1[i] - 65].last = i + 1;
		else table[0][str1[i] - 65].last = i + 1;
		car_num[str1[i] - 65]++;
	}
	for (int i = 0; i < s2len; i++) {
		if (table[1][str2[i] - 65].first == -1) table[1][str2[i] - 65].first = i + 1, table[1][str2[i] - 65].last = i + 1;
		else table[1][str2[i] - 65].last = i + 1;
		car_num[str2[i] - 65]++;
	}
}

Data comp(Data data, char c, int width, int height) { // 다음 테이블 계산
	data.total += data.use;
	if (width == table[0][c - 65].first && (height < table[1][c - 65].first || table[1][c - 65].first == -1)) data.total++, data.use++;
	else if (height == table[1][c - 65].first && (width < table[0][c - 65].first || table[0][c - 65].first == -1)) data.total++, data.use++;
	
	// 처음 들어오는가

	if (width >= table[0][c - 65].last && height >= table[1][c - 65].last) data.total--, data.use--; // 그 차가 마지막으로 들어왔을 경우
	return data;
}

int solution(char str1[], char str2[]) { // Sol.
	for (int i = 0; i < s1len; i++) data[0][i + 1] = comp(data[0][i], str1[i], i + 1, 0); // str1 -> 가로
	for (int i = 0; i < s2len; i++) data[i + 1][0] = comp(data[i][0], str2[i], 0, i + 1); // str2 -> 세로
	
	for (int i = 1; i <= s2len; i++) {
		for (int j = 1; j <= s1len; j++) {
			data[i][j] = Min(comp(data[i - 1][j], str2[i - 1], j, i), comp(data[i][j - 1], str1[j - 1], j, i));
		}
	}
	return data[s2len][s1len].total;
}

int main() {
	FILE *inp = fopen("color.inp", "r");
	FILE *out = fopen("color.out", "w");
	int testcase;
	fscanf(inp, "%d\n", &testcase);
	while (testcase--) {
		char str[2][5010];
		fscanf(inp, "%s%s", &str[0], &str[1]);
		init(str[0], str[1]);
		input_table(str[0], str[1]);
		fprintf(out, "%d\n", solution(str[0], str[1]));
	}
	fclose(inp);
	fclose(out);
	return 0;
}