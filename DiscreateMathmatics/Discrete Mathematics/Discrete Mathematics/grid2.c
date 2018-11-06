#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int Type1Table(int N, int M, int s, int K) {                              //type1
	int i3, Count = s, TableNumber = 0, Check = 0;
	int Minus = 0, MinusCount = -1;

	if (Count == 1)TableNumber = 0;
	else if (Count == 2)TableNumber = 0;
	else if (Count == 3)TableNumber = N*M + 1;
	else TableNumber = N*M + 1;

	for (i3 = 0; i3 < K; i3++) {
		if (Count == 1) {
			TableNumber += 1;
			Check++;
			if ((Check + Minus) %M == 0 && Check != 0) {
				Count = 2;
				Check = 1;
				MinusCount++;
				if (MinusCount % 2 == 0 && MinusCount != 0)Minus++;
				continue;
			}
		}
		else if (Count == 2) {
			TableNumber += M;
			Check++;
			if ((Check + Minus) %N == 0 && Check != 0) {
				Count = 3;
				Check = 1;
				MinusCount++;
				if (MinusCount % 2 == 0 && MinusCount != 0)Minus++;
				continue;
			}
		}
		else if (Count == 3) {
			TableNumber -= 1;
			Check++;
			if ((Check + Minus) %M == 0 && Check != 0) {
				Count = 4;
				Check = 1;
				MinusCount++;
				if (MinusCount % 2 == 0 && MinusCount != 0)Minus++;
				continue;
			}
		}
		else {
			TableNumber -= M;
			Check++;
			if ((Check + Minus) %N == 0 && Check != 0) {
				Count = 1;
				Check = 1;
				MinusCount++;
				if (MinusCount % 2 == 0 && MinusCount != 0)Minus++;
				continue;
			}
		}
	}
	return TableNumber;
}

int Type2Table(int N, int M, int s, int K) {                              //type2
	int i4, Count = s, TableNumber = 0, Check = 0;
	int Minus = 0, MinusCount = -1;

	if (Count == 1)TableNumber = 1-M;
	else if (Count == 2)TableNumber = M+1;
	else if (Count == 3)TableNumber = N*M + M;
	else TableNumber = N*M - M;

	for (i4 = 0; i4 < K; i4++) {
		if (Count == 1) {
			TableNumber += M;
			Check++;
			if ((Check + Minus) % N == 0 && Check != 0) {
				Count = 4;
				Check = 1;
				MinusCount++;
				if (MinusCount % 2 == 0 && MinusCount != 0)Minus++;
				continue;
			}
		}
		else if (Count == 2) {
			TableNumber -= 1;
			Check++;
			if ((Check + Minus) % M == 0 && Check != 0) {
				Count = 1;
				Check = 1;
				MinusCount++;
				if (MinusCount % 2 == 0 && MinusCount != 0)Minus++;
				continue;
			}
		}
		else if (Count == 3) {
			TableNumber -= M;
			Check++;
			if ((Check + Minus) % N == 0 && Check != 0) {
				Count = 2;
				Check = 1;
				MinusCount++;
				if (MinusCount % 2 == 0 && MinusCount != 0)Minus++;
				continue;
			}
		}
		else {
			TableNumber += 1;
			Check++;
			if ((Check + Minus) % M == 0 && Check != 0) {
				Count = 3;
				Check = 1;
				MinusCount++;
				if (MinusCount % 2 == 0 && MinusCount != 0)Minus++;
				continue;
			}
		}
	}
	return TableNumber;
}


int main() {
	FILE *inp = fopen("grid2.inp", "r");
	FILE *out = fopen("grid2.out", "w");
	int a = 0;
	int N, M, t, s, K;
	int i, j;
	fscanf(inp, "%d\n", &a);
	for (i = 0; i < a; i++) {
		fscanf(inp, "%d %d %d %d %d\n", &N, &M, &t, &s, &K);
		if (t == 3) fprintf(out, "%d\n", Type1Table(N, M, s, K));
		else fprintf(out, "%d\n", Type2Table(N, M, s, K));
	}
	fclose(inp);
	fclose(out);
	return 0;
}