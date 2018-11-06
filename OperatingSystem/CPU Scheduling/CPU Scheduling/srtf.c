#include<stdio.h>
#pragma warning(disable:4996)

typedef struct process {
	int number;
	int arrive;
	int burst;
}pro;

int pronum;

void Sort(pro list[]) {
	pro temp;
	for (int i = 0; i < pronum; i++) {
		int j = 0;
		for (int j = 0; j < pronum - 1; j++) {
			if (list[j].number > list[j + 1].number) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

void arriveSort(pro list[], int arrive[]) {
	int temp;
	for (int i = 0; i < pronum; i++) {
		for (int j = 0; j < pronum - 1; j++) {
			if (list[arrive[j]].arrive > list[arrive[j + 1]].arrive) {
				temp = arrive[j];
				arrive[j] = arrive[j + 1];
				arrive[j + 1] = temp;
			}
			else if (list[arrive[j]].arrive == list[arrive[j + 1]].arrive) {
				if (arrive[j] > arrive[j + 1]) {
					temp = arrive[j];
					arrive[j] = arrive[j + 1];
					arrive[j + 1] = temp;
				}
			}
		}
	}
}

int main() {
	FILE *inp = fopen("srtf.inp", "r");
	FILE *out = fopen("srtf.out", "w");
	pro list[50];

	int arrive[50], ready[200], wait = 0;
	int ready_front = 0, ready_rear = 0;
	fscanf(inp, "%d", &pronum);
	for (int i = 0; i < pronum; i++) {
		fscanf(inp, "%d %d %d", &list[i].number, &list[i].arrive, &list[i].burst);
		arrive[i] = list[i].number;
	}
	Sort(list);
	arriveSort(list, arrive);
	int time = 0, end = 0, i = 0, cpu = -1;

	while (1) {
		if (i < pronum && list[arrive[i]].arrive == time) {        // �ð��� ������ in ready
			while (i < pronum && list[arrive[i]].arrive == time) {  // ���� ����ť�� �ִ� list�� ���� ������ in ready
				ready[ready_rear] = arrive[i];
				ready_rear++, i++;
				// SJF
				for (int k = ready_front; k < ready_rear; k++) {
					for (int j = ready_front; j < ready_rear - 1; j++) {
						if (list[ready[j]].burst > list[ready[j + 1]].burst) {
							int temp = ready[j];
								ready[j] = ready[j + 1];
								ready[j + 1] = temp;
						}
					}
				}
				// SRTF
				if (cpu != -1 && list[cpu].burst > list[ready[ready_front]].burst) {
					ready[ready_rear] = cpu;
					ready_rear++;
					cpu = ready[ready_front];
					ready[ready_front] = -1;
					ready_front++;
					for (int k = ready_front; k < ready_rear; k++) {
						for (int j = ready_front; j < ready_rear - 1; j++) {
							if (list[ready[j]].burst > list[ready[j + 1]].burst) {
								int temp = ready[j];
								ready[j] = ready[j + 1];
								ready[j + 1] = temp;
							}
						}
					}
				}
				// SRTF
			}
		}

		if (cpu != -1 && list[cpu].burst == 0) {     // cpu�� ������� ���μ����� �� ó������ ��,
			cpu = -1;
		}

		else if (cpu != -1 && list[cpu].burst > 0) {   // cpu�� ������϶�,
			list[cpu].burst--;
		}

		if (cpu == -1 && ready_front != ready_rear) { // cpu�� ������� ��,
			cpu = ready[ready_front];
			list[cpu].burst--;
			ready[ready_front] = -1;
			ready_front++;
			if (i >= pronum && ready_front == ready_rear) break; // ���̻� ó���� ���μ����� ������ ����
		}

		if (ready_front != ready_rear) {     // wait time
			wait += ready_rear - ready_front;
		}
		time++;
	}

	fprintf(out, "%d\n", wait);
	fclose(inp);
	fclose(out);
	return 0;
}
