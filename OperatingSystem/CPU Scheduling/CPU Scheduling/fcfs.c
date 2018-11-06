#include <stdio.h>
#pragma warning(disable:4996)

int pronum, wait = 0;

typedef struct process {
	int number;
	int arrive;
	int burst;
}pro;

void Sort(pro list[]) {
	pro temp;
	for (int i = 0; i < pronum; i++) {
		for (int j = 0; j < pronum - 1; j++) {
			if (list[j].arrive > list[j + 1].arrive) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
			else if (list[j].arrive == list[j + 1].arrive) {
				if (list[j].number > list[j + 1].number) {
					temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
				}
			}
		}
	}
}

int main() {
	FILE* inp = fopen("fcfs.inp", "rt");
	FILE* out = fopen("fcfs.out", "wt");

	pro list[50];
	fscanf(inp, "%d\n", &pronum);

	for (int i = 0; i < pronum; i++) fscanf(inp, "%d %d %d\n", &list[i].number, &list[i].arrive, &list[i].burst);
	Sort(list);
	// 여기까지 입력 & 정렬

	int time = 0;
	for (int i = 0; i < pronum; i++) {
		if (list[i].arrive < time) {
			wait += time - list[i].arrive;
		}
		else {
			time = list[i].arrive;
		}
		time += list[i].burst;
	}

	fprintf(out, "%d\n", wait);
	fclose(inp);
	fclose(out);
	return 0;
}
