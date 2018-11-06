#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int dice(int n) {
	FILE *inp = fopen("dice.inp", "r");
	int i, repeat;
	int A, B, C, D, E, F;
	int up = n, bigest, sum = 0;
	fscanf(inp, "%d\n", &repeat);
	// A-F, B-D, C-E
	for (i = 0; i < repeat; i++) {
		fscanf(inp, "%d %d %d %d %d %d\n", &A, &B, &C, &D, &E, &F);
		if (A == up) {
			up = F;
			bigest = B;
			if (bigest < C) bigest = C;
			if (bigest < D) bigest = D;
			if (bigest < E) bigest = E;
			sum += bigest;
		}
		else if (B == up) {
			up = D;
			bigest = A;
			if (bigest < C) bigest = C;
			if (bigest < E) bigest = E;
			if (bigest < F) bigest = F;
			sum += bigest;
		}
		else if (C == up) {
			up = E;
			bigest = A;
			if (bigest < B) bigest = B;
			if (bigest < D) bigest = D;
			if (bigest < F) bigest = F;
			sum += bigest;
		}
		else if (D == up) {
			up = B;
			bigest = A;
			if (bigest < C) bigest = C;
			if (bigest < E) bigest = E;
			if (bigest < F) bigest = F;
			sum += bigest;
		}
		else if (E == up) {
			up = C;
			bigest = A;
			if (bigest < B) bigest = B;
			if (bigest < D) bigest = D;
			if (bigest < F) bigest = F;
			sum += bigest;
		}
		else {
			up = A;
			bigest = B;
			if (bigest < C) bigest = C;
			if (bigest < D) bigest = D;
			if (bigest < E) bigest = E;
			sum += bigest;
		}
	}
	fclose(inp);
	return sum;
}

int main() {
	FILE *out = fopen("dice.out", "w");
	int i, finalsum;
	finalsum = dice(1);
	for (i = 2; i <= 6; i++) {
		if (finalsum < dice(i))finalsum = dice(i);
	}
	fprintf(out, "%d\n", finalsum);
	fclose(out);
	return 0;
}