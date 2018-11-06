#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main() {
	FILE* inp = fopen("dish.inp", "r");
	FILE* out = fopen("dish.out", "w");
	int s = 0, t = 0;
	int i = 0, j = 0, k = 0;
	char c, beforeC;
	fscanf(inp, "%d\n", &s);
	for (i = 0; i < s; i++) {
		c = 0, beforeC = 0;
		fscanf(inp, "%d\n", &t);
		fscanf(inp, "%c", &beforeC);
		int sum = 10;
		for (j = 0; j < t; j++) {
			fscanf(inp, "%c", &c);
			if (c == '\n') {
				fprintf(out, "%d\n", sum);
				break;
			}
			if (c != beforeC) sum += 10;
			else if (c == beforeC) sum += 5;
			else printf("x");
			beforeC = c;
		}
	}
	fclose(inp);
	fclose(out);
	return 0;
}