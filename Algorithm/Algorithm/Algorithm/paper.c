#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)
#define MAX 10000

int idx[MAX] = { 0 };
int Board[MAX][MAX] = { 0 }, length = 0;

typedef struct paper {
	int x;
	int y;
	int w;
	int h;
	int visible;
	int invisible;
}paper;

void Insert(int data) { // idx에 insert
	for (int i = 0; i <= length; i++) {
		if (idx[i] == 0) {
			idx[i] = data;
			length++;
			break;
		}
		else if (idx[i] == data) break;
		else if (idx[i] > data) {
			memmove(idx + i + 1, idx + i, (length - i) * 4);
			idx[i] = data;
			length++;
			break;
		}
		else continue;
	}
}

void Mapping(paper cp[], int num) { // 좌표압축
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < length; j++) {
			if (cp[i].x == idx[j]) cp[i].x = j;
			if (cp[i].y == idx[j]) cp[i].y = j;
			if (cp[i].w == idx[j]) cp[i].w = j;
			if (cp[i].h == idx[j]) cp[i].h = j;
		}
	} // mapping.
}

void Setting(paper cp[], int num) { // 종이들 세팅
	for (int i = 0; i < num; i++) {
		for (int j = cp[i].x; j < cp[i].w; j++) {
			for (int k = cp[i].y; k < cp[i].h; k++) {
				Board[j][k] = i;
			}
		}
	} // setting.
}

void Checking(paper cp[], int num, FILE *out) { // 종이 체크하고 출력
	int all = 0, half = 0, no = 0;
	for (int i = 0; i < num; i++) {
		for (int j = cp[i].x; j < cp[i].w; j++) {
			for (int k = cp[i].y; k < cp[i].h; k++) {
				if (Board[j][k] == i) cp[i].visible = 1;
				else cp[i].invisible = 1;
			}
		}
		if (cp[i].invisible == 1 && cp[i].visible == 1) half++;
		else if (cp[i].invisible == 1) no++;
		else all++;
	}
	fprintf(out, "%d %d %d", no, half, all);
}

int main() {
	FILE *inp = fopen("paper.inp", "r");
	FILE *out = fopen("paper.out", "w");
	paper cp[MAX];
	int num;
	fscanf(inp, "%d", &num);
	for (int i = 0; i < num; i++) {
		fscanf(inp, "%d %d %d %d\n", &cp[i].x, &cp[i].y, &cp[i].w, &cp[i].h);
		cp[i].w += cp[i].x, cp[i].h += cp[i].y;
		Insert(cp[i].x);
		Insert(cp[i].y);
		Insert(cp[i].w);
		Insert(cp[i].h);
		cp[i].invisible = 0, cp[i].visible = 0;
	} // input data.

	Mapping(cp, num);
	Setting(cp, num);
	Checking(cp, num, out);
	
	fclose(inp);
	fclose(out);
	return 0;
}