#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main() {
	FILE *inp = fopen("mail.inp", "r");
	FILE *out = fopen("mail.out", "w");
	int i, j;
	int totalrepeat, repeat;
	char code[600];
	fscanf(inp, "%d\n", &totalrepeat);
	for (i = 0; i < totalrepeat; i++) {
		fscanf(inp, "%d\n", &repeat);
		fscanf(inp, "%s", &code);
		for (j = 0; j < repeat; j++) {
			int A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, G = 0, H = 0;
			if (code[0 + j * 6] == '0') A++, B++, C++, D++;
			if (code[1 + j * 6] == '0') A++, B++, E++, F++;
			if (code[2 + j * 6] == '0') A++, C++, E++, G++;
			if (code[3 + j * 6] == '0') A++, C++, F++, H++;
			if (code[4 + j * 6] == '0') A++, D++, F++, G++;
			if (code[5 + j * 6] == '0') A++, D++, E++, H++;
		
			if (code[0 + j * 6] == '1') E++, F++, G++, H++;
			if (code[1 + j * 6] == '1') C++, D++, G++, H++;
			if (code[2 + j * 6] == '1') B++, D++, F++, H++;
			if (code[3 + j * 6] == '1') B++, D++, E++, G++;
			if (code[4 + j * 6] == '1') B++, C++, E++, H++;
			if (code[5 + j * 6] == '1') B++, C++, F++, G++;

			if (A >= 5)fprintf(out, "A");
			else if (B >= 5)fprintf(out, "B");
			else if (C >= 5)fprintf(out, "C");
			else if (D >= 5)fprintf(out, "D");
			else if (E >= 5)fprintf(out, "E");
			else if (F >= 5)fprintf(out, "F");
			else if (G >= 5)fprintf(out, "G");
			else if (H >= 5)fprintf(out, "H");
			else fprintf(out, "X");
		}
		fprintf(out, "\n");
	}
	fclose(inp);
	fclose(out);
	return 0;
}