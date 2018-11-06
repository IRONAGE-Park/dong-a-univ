#include<stdio.h>
#pragma warning(disable:4996)

int main() {
	FILE *inp = fopen("cross.inp", "r");
	FILE *out = fopen("cross.out", "w");

	int i,j,k,repeat,length;
	int sequence1[10000], sequence2[10000];
	int *location1[10000];
	int *location2[10000];
	fscanf(inp, "%d", &repeat);
	for (i = 0; i < repeat; i++) {
		int point = 0;
		fscanf(inp, "%d", &length);	
		for (j = 1; j <= length; j++) {
			fscanf(inp, "%d", &sequence1[j]);
			location1[sequence1[j]] = &sequence1[j];
		}
		for (j = 1; j <= length; j++) {
			fscanf(inp, "%d", &sequence2[j]);
			location2[sequence2[j]] = &sequence2[j];
		}
		for (j = 1; j <= length; j++) {
			for (k = j + 1; k <= length; k++) {
				if (location1[k] > location1[j] && location2[k] < location2[j]) point++;
				else if (location1[k] < location1[j] && location2[k] > location2[j]) point++;
				else;
			}
		}
		fprintf(out, "Case %d: %d\n", i + 1, point);
	}
	fclose(inp);
	fclose(out);
	return 0;
}