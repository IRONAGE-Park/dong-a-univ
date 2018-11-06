#include <stdio.h>
#pragma warning(disable:4996)

int pronum, wait = 0;

typedef struct process {
	int number;
	int arrive;
	int burst;
}pro;

void Sort(pro list[],int start,int last) {
	pro temp;
	for (int i = start; i < last; i++) {
		for (int j = start; j < last - 1; j++) {
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

void lowBurstSort(pro list[], int time, int start) {
	pro temp;
	for (int i = start; i < pronum && list[i].arrive <= time; i++) {
		for (int j = start; j < pronum - 1 && list[j].arrive <= time && list[j + 1].arrive <= time; j++) {
			if (list[j].burst > list[j + 1].burst) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
			else if (list[j].burst == list[j + 1].burst) {
				Sort(list, j, j + 2);
			}
		}
	}
}

int main() {
	FILE* inp = fopen("sjf.inp", "r");
	FILE* out = fopen("sjf.out", "w");

	pro list[50];
	fscanf(inp, "%d\n", &pronum);

	for (int i = 0; i < pronum; i++) {
		fscanf(inp, "%d %d %d\n", &list[i].number, &list[i].arrive, &list[i].burst);
	}
	Sort(list, 0, pronum);
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
		list[i].arrive = -1, list[i].burst = -1, list[i].number = -1;
		lowBurstSort(list, time, i + 1);
	}

	fprintf(out, "%d\n", wait);
	fclose(inp);
	fclose(out);
	return 0;
}
