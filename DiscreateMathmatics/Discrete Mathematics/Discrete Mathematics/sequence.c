#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main() {
	FILE *inp = fopen("sequence.inp", "r");
	FILE *out = fopen("sequence.out", "w");
	long long int repeat = 1, A, limit, count = 1;
	while (1) {
		fscanf(inp, "%lld %lld₩n", &A, &limit);
		if (A < 0 || limit < 0) break;
		long long int A1 = A;
		while (A1 <= limit) {
			if (A1 % 2 == 0) {
				A1 /= 2;
				count++;
			}
			else if (A1 % 2 == 1) {
				A1 = A1 * 3 + 1;
				if (A1 > limit) break;
				count++;
			}
			if (A1 == 1) {
				break;
			}
		}
		fprintf(out, "Case %lld: A = %lld, limit = %lld, number of terms = %lld\n", repeat, A, limit, count);
		repeat++;
		count = 1;
	}
	fclose(inp);
	fclose(out);
	return 0;
}