#include<stdio.h>
#pragma warning(disable:4996)
int num[10000000];
void Sort(int a[], int size) {
	int i, j, temp;
	for (i = 1; i < size; i++) {
		temp = a[i];
		j = i;
		while ((j > 0) && (a[j - 1] > temp)) {
			a[j] = a[j - 1];
			j = j - 1;
		}
		a[j] = temp;
	}
}

int main() {
	FILE *input = fopen("rods.inp", "r");
	FILE *output = fopen("rods.out", "w");
	int n, cnt = 0, p=0, sum=0, a, b;
	while (1) {
		fscanf(input, "%d", &n);
		if (n == -1) {
			while (num[p] != 0 && num[p + 1] != 0) {
				Sort(num, cnt);
				a = num[p];
				p++;
				b = num[p];
				p++;
				sum += a, sum += b;
				num[cnt] = a + b;
				cnt++;
			}
			fprintf(output, "%d", sum);
			break;
		}
		num[cnt] = n;
		cnt++;
	}
}