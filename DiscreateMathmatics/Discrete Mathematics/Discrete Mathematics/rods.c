#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)
int data[100000000], front, rear;

int dequeue() {
	int num;
	num = data[front];
	data[front] = 0;
	front++;
	return num;
}

void SelectionSort(int a[], int size) { 
	int i, j, t, min, temp;
	for (i = 0; i < size - 1; i++) {
		min = i;
		for (j = i + 1; j < size; j++) {
			if (a[j] < a[min]) min = j;
		}     temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}

int main() {
	FILE *inp = fopen("rods.inp", "r");
	FILE *out = fopen("rods.out", "w");
	int sum = 0, num1, num2, cnt;
	int length;
	int datacount = 0;
	while (1) {
		fscanf(inp, "%d\n", &length);
		if (length == -1) {  // 출력할 때,
			front = 0, rear = datacount;
			SelectionSort(data, datacount);
			while (front != rear) { // 계산
				num1 = dequeue();
				num2 = dequeue();
				if (num1 == 0 || num2 == 0) break;
				sum += (num1 + num2);
				if (front == rear) break;
				else {
					int i = front, cnt = 0;
					while ((num1 + num2) > data[i]) {
						i++;
						if (data[i] == 0) {
							data[i] = num1 + num2;
							rear++;
							cnt = 1;
							break;
						}
					}
					if (cnt != 1) {
						memmove(&data[i + 1], &data[i], (rear - i) * 4);
						data[i] = (num1 + num2);
						rear++;
					}
				}
			}
			fprintf(out, "%d", sum);
			break;
		}
		data[datacount] = length;
		datacount++;
	}
	fclose(inp);
	fclose(out);
	return 0;
}