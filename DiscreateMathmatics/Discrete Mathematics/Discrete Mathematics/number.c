#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main() {
	FILE *inp = fopen("number.inp", "r");
	FILE *out = fopen("number.out", "w");
	int i, j, k, l = 0, N, n = 0, D = 0;
	int bigest, bigestLocation;
	int control = 0;
	char number[5000];
	
	while (number[0] != '\n') {
		fscanf(inp, "%s", &number);

	}
	
	fclose(inp);
	fclose(out);
	return 0;
}