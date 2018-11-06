#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main() {
	FILE *inp = fopen("string.inp", "r");
	FILE *out = fopen("string.out", "w");
	int repeat = 0, i, j;
	int ABA = 0, ABK = 0, BAB = 0, KBA = 0;
	char first, second, third;
	fscanf(inp, "%d\n", &repeat);
	for (i = 0; i < repeat; i++) {
		fscanf(inp, "%c", &first);
		fscanf(inp, "%c", &second);
		fscanf(inp, "%c", &third);
		for (j = 0; j < 10000; j++) {
			if (third == '\n') break;
			if (first == 'A'&&second == 'B'&&third == 'A') ABA++;
			else if (first == 'A'&&second == 'B'&&third == 'K') ABK++;
			else if (first == 'B'&&second == 'A'&&third == 'B') BAB++;
			else if (first == 'K'&&second == 'B'&&third == 'A')	KBA++;
			first = second;
			second = third;
			fscanf(inp, "%c", &third);
		}
		fprintf(out, "%d %d %d %d\n", ABA, ABK, BAB, KBA);
		ABA = 0, ABK = 0, BAB = 0, KBA = 0;
	}
	fclose(inp);
	fclose(out);
	return 0;
}