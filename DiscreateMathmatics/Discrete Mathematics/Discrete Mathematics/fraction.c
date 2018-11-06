#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int fraction(int check) {
	int i = 2, result = 0, yacc = 1, tmp = 1, cnt = 0;
	while (check >1) {
		for (;; i++) {
			if (check % i == 0) { 
				check /= i;                              
				if (result != i) {
					cnt = 0;                                  
					result = i; 
				}                          
				cnt++;                           
				break; 
			}
		}               
		if (check % i != 0) { 
			yacc = yacc * (2 * cnt + 1);
		}
	}       
	return yacc - yacc / 2;
}

int main() {
	FILE *inp = fopen("fraction.inp", "r");
	FILE *out = fopen("fraction.out", "w");
	int k = 1, count;
	while (k != 0) {
		fscanf(inp, "%d\n", &k);
		if (k == 0)break;
		count = fraction(k);
		fprintf(out, "%d\n", count);
	}
	fclose(inp);
	fclose(out);
	return 0;
}

/*
while (k != 0) {
fscanf(inp, "%d\n", &k);
if (k == 0) break;
x1 = k * 2;
y1 = k * 2;
for (x = x1; x <= k*(k + 1); x++) {
for (y = y1; y >= k + 1; y--) {
if ((x*y) / (x + y) == k) {
x1 = x;
count++;
printf("%d | %d | %.0f %.0f\n", count, k, x, y);
break;
}
}
}
printf("天天天天天天天天天天天天天天天天天天天\n");
fprintf(out, "%d\n", count);
count = 0;
}
*/