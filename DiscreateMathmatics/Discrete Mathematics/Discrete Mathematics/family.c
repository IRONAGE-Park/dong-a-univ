#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int son[500000];        // 부모의 숫자가 적혀있는 배열
int button[500000], buttoncount[500000];

int main() {
	FILE *inp = fopen("family.inp", "r");
	FILE *out = fopen("family.out", "w");
	int repeat, hint, i, j;
	int parent, first, sonnumber;             // 부모 번호와 자식 번호
	int count = 0, lastcount = 0;
	fscanf(inp, "%d\n", &repeat);
	for (i = 0; i < repeat; i++) {
		fscanf(inp, "%d\n", &hint);
		int allpeople = hint, diffentpeople = 0;
		lastcount = 0;
		for (j = 1; j < hint; j++) {
			fscanf(inp, "%d %d\n", &parent, &sonnumber);
			son[sonnumber] = parent;           // 부모 번호를 자식의 번호에 해당하는 배열에 삽입
			allpeople += j;
			diffentpeople += sonnumber;
		}
		first = allpeople - diffentpeople;      // 조상 번호
		for (j = 1; j <= hint; j++) {
			sonnumber = j;
			count = 1;
			button[j] = 1;
			while (sonnumber != first) {
				sonnumber = son[sonnumber];
				if (button[sonnumber] == 1) {
					count += buttoncount[sonnumber];
					break;
				}
				count++;
			}
			buttoncount[j] = count;
			if (count > lastcount) lastcount = count;
		}
		fprintf(out, "%d\n", lastcount);
		for (j = 1; j <= hint; j++) {
			button[j] = 0;
			buttoncount[j] = 0;
		}
	}
	fclose(inp);
	fclose(out);
	return 0;
}
