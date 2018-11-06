#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int compare(const void *first, const void *second)
{
	if (*(double*)first > *(double*)second)
		return -1;
	else if (*(double*)first < *(double*)second)
		return 1;
	else
		return 0;
}

int main() {
	FILE *inp = fopen("Trip.inp", "r");
	FILE *out = fopen("Trip.out", "w");
	int n;
	double arr[1001];
	double sum, avg, temp;
	double result1, result2;
	while (1) {
		sum = 0, avg = 0, result1 = 0, result2 = 0;
		fscanf(inp, "%d", &n);
		if (n == 0) break;

		for (int i = 0; i < n; i++) {
			fscanf(inp, "%lf\n", &arr[i]);
			sum += arr[i];
		}
		avg = sum / n;
		qsort(arr, n, sizeof(double), compare);
		for (int i = 0; i < n; i++) {
			temp = arr[i] - avg;
			temp = (int)(temp * 100) / 100.0;	// 소수점 둘째자리 이하 버림
			if (temp > 0) result1 += temp;	// 평균보다 값이 큰쪽에서 계산
			else result2 -= temp;	// 값이 작은쪽에서 계산
		}
		if (result1 > result2) fprintf(out, "$%.2lf\n", result1);
		else fprintf(out, "$%.2lf\n", result2);
	}
	fclose(inp);
	fclose(out);
	return 0;
}