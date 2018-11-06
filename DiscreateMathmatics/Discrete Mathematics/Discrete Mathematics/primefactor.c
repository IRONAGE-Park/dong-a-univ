#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main() {
	FILE *inp = fopen("primefactor.inp", "r");
	FILE *out = fopen("primefactor.out", "w");
	int i, j, repeat, PrimeNumber,FirstPrimeNumber;
	fscanf(inp, "%d\n", &repeat);
	for (i = 0; i < repeat; i++) {
		int sum = 0, count = 0;
		fscanf(inp, "%d\n", &PrimeNumber);
		FirstPrimeNumber = PrimeNumber;
		for (j = 2; j <= PrimeNumber; j++) {
			if (PrimeNumber%j == 0 && j != FirstPrimeNumber) {
				sum += j;
				PrimeNumber = PrimeNumber / j;
				j = 1;
				count++;
			}
		}
		if (sum == 0 && count == 0) fprintf(out, "Prime Number\n");
		else fprintf(out, "%d\n", sum);
	}
	fclose(inp);
	fclose(out);
	return 0;
}