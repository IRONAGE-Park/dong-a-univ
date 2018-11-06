#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int Type1Table1(int N, int M, int K) {                              //type1 ÁÂ»ó
	int i1, Count = 1, TableNumber = 0;

	for (i1 = 1; i1 <= K; i1++) {
		if (Count == 1) {
			if (i1%M == 1 && i1 != 1) {
				TableNumber += M;
				Count = 2;
				continue;
			}
			TableNumber += 1;
		}
		else {
			if (i1%M == 1 && i1 != 1) {
				TableNumber += M;
				Count = 1;
				continue;
			}
			TableNumber -= 1;
		}
	}
	return TableNumber;
}

int Type1Table2(int N, int M, int K) {                              //type1 ¿ì»ó
	int i2, Count = 1, TableNumber = M + 1;

	for (i2 = 1; i2 <= K; i2++) {
		if (Count == 1) {
			if (i2%M == 1 && i2 != 1) {
				TableNumber += M;
				Count = 2;
				continue;
			}
			TableNumber -= 1;
		}
		else {
			if (i2%M == 1 && i2 != 1) {
				TableNumber += M;
				Count = 1;
				continue;
			}
			TableNumber += 1;
		}
	}
	return TableNumber;
}

int Type1Table3(int N, int M, int K) {                              //type1 ¿ìÇÏ
	int i3, Count = 1, TableNumber = N*M + 1;

	for (i3 = 1; i3 <= K; i3++) {
		if (Count == 1) {
			if (i3%M == 1 && i3 != 1) {
				TableNumber -= M;
				Count = 2;
				continue;
			}
			TableNumber -= 1;
		}
		else {
			if (i3%M == 1 && i3 != 1) {
				TableNumber -= M;
				Count = 1;
				continue;
			}
			TableNumber += 1;
		}
	}
	return TableNumber;
}

int Type1Table4(int N, int M, int K) {                              //type1 ÁÂÇÏ
	int i4, Count = 1, TableNumber = N*M - M;

	for (i4 = 1; i4 <= K; i4++) {
		if (Count == 1) {
			if (i4%M == 1 && i4 != 1) {
				TableNumber -= M;
				Count = 2;
				continue;
			}
			TableNumber += 1;
		}
		else {
			if (i4%M == 1 && i4 != 1) {
				TableNumber -= M;
				Count = 1;
				continue;
			}
			TableNumber -= 1;
		}
	}
	return TableNumber;
}


int Type2Table1(int N, int M, int K) {                              //type2 ÁÂ»ó
	int i1, Count = 1, TableNumber = -M + 1;

	for (i1 = 1; i1 <= K; i1++) {
		if (Count == 1) {
			if (i1%N == 1 && i1 != 1) {
				TableNumber += 1;
				Count = 2;
				continue;
			}
			TableNumber += M;
		}
		else {
			if (i1%N == 1 && i1 != 1) {
				TableNumber += 1;
				Count = 1;
				continue;
			}
			TableNumber -= M;
		}
	}
	return TableNumber;
}

int Type2Table2(int N, int M, int K) {                              //type2 ¿ì»ó
	int i2, Count = 1, TableNumber = 0;

	for (i2 = 1; i2 <= K; i2++) {
		if (Count == 1) {
			if (i2%N == 1 && i2 != 1) {
				TableNumber -= 1;
				Count = 2;
				continue;
			}
			TableNumber += M;
		}
		else {
			if (i2%N == 1 && i2 != 1) {
				TableNumber -= 1;
				Count = 1;
				continue;
			}
			TableNumber -= M;
		}
	}
	return TableNumber;
}

int Type2Table3(int N, int M, int K) {                              //type2 ¿ìÇÏ
	int i3, Count = 1, TableNumber = N*M + M;

	for (i3 = 1; i3 <= K; i3++) {
		if (Count == 1) {
			if (i3%N == 1 && i3 != 1) {
				TableNumber -= 1;
				Count = 2;
				continue;
			}
			TableNumber -= M;
		}
		else {
			if (i3%N == 1 && i3 != 1) {
				TableNumber -= 1;
				Count = 1;
				continue;
			}
			TableNumber += M;
		}
	}
	return TableNumber;
}

int Type2Table4(int N, int M, int K) {                              //type2 ÁÂÇÏ
	int i4, Count = 1, TableNumber = N*M + 1;

	for (i4 = 1; i4 <= K; i4++) {
		if (Count == 1) {
			if (i4%N == 1 && i4 != 1) {
				TableNumber += 1;
				Count = 2;
				continue;
			}
			TableNumber -= M;
		}
		else {
			if (i4%N == 1 && i4 != 1) {
				TableNumber += 1;
				Count = 1;
				continue;
			}
			TableNumber += M;
		}
	}
	return TableNumber;
}



int main() {
	FILE *inp = fopen("grid1.inp", "r");
	FILE *out = fopen("grid1.out", "w");
	int a = 0;
	int N, M, t, s, K;
	int i, j;
	fscanf(inp, "%d\n", &a);
	for (i = 0; i < a; i++) {
		fscanf(inp, "%d %d %d %d %d\n", &N,&M,&t,&s,&K);
		if (t == 1) {
			if (s == 1) fprintf(out, "%d\n", Type1Table1(N, M, K));
			else if (s == 2) fprintf(out, "%d\n", Type1Table2(N, M, K));
			else if (s == 3) fprintf(out, "%d\n", Type1Table3(N, M, K));
			else  fprintf(out, "%d\n", Type1Table4(N, M, K));
		}
		else {
			if (s == 1) fprintf(out, "%d\n", Type2Table1(N, M, K));
			else if (s == 2) fprintf(out, "%d\n", Type2Table2(N, M, K));
			else if (s == 3) fprintf(out, "%d\n", Type2Table3(N, M, K));
			else  fprintf(out, "%d\n", Type2Table4(N, M, K));
		}
	}
	fclose(inp);
	fclose(out);
	return 0;
}