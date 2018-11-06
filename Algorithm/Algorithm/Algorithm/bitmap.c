#include<stdio.h>
#pragma warning(disable:4996)

char map[200][200];
int cnt;

char sameCheck(int sx, int sy, int n, int m) { // -1 이면 내용이 다름
	for (int i = sy; i < m; i++) {
		for (int j = sx; j < n; j++) {
			if (map[sy][sx] != map[i][j]) return -1;
		}
	}
	return map[sy][sx];
}

int divide(int x) {
	if (x % 2 == 0) {
		return x / 2;
	}
	else return (x / 2) + 1;
}

void cond(FILE *out, int sx, int sy, int n, int m) { // 압축
	if (sameCheck(sx, sy, n, m) != -1) { // 내부가 모두 같으면
		fprintf(out, "%c", sameCheck(sx, sy, n, m));
		cnt++;
		if (cnt % 50 == 0) fprintf(out, "\n");
	}
	else { // 내부가 다르면
		fprintf(out, "D");
		cnt++;
		if (cnt % 50 == 0) fprintf(out, "\n"); // 50줄이 넘으면 개행

		if (n - sx == 1) { // 열이 한 줄
			cond(out, sx, sy, divide(n + sx), divide(m + sy)); // 왼쪽 상단
			cond(out, sx, divide(m + sy), divide(n + sx), m); // 왼쪽 하단
		}
		else if (m - sy == 1) { // 행이 한 줄
			cond(out, sx, sy, divide(n + sx), divide(m + sy)); // 왼쪽 상단
			cond(out, divide(n + sx), sy, n, divide(m + sy)); // 오른쪽 상단
		}
		else {
			cond(out, sx, sy, divide(n + sx), divide(m + sy)); // 왼쪽 상단
			cond(out, divide(n + sx), sy, n, divide(m + sy)); // 오른쪽 상단
			cond(out, sx, divide(m + sy), divide(n + sx), m); // 왼쪽 하단
			cond(out, divide(n + sx), divide(m + sy), n, m); // 오른쪽 하단
		}
	}
}

void div(FILE *inp, int sx, int sy, int n, int m) {
	char f;
	fscanf(inp, "%c", &f);
	if (f == '\n') fscanf(inp, "%c", &f); // 개행문자가 오면 넘김

	if (f == 'D') {
		if (n - sx == 1) { // 열이 한 줄
			div(inp, sx, sy, divide(n + sx), divide(m + sy)); // 왼쪽 상단
			div(inp, sx, divide(m + sy), divide(n + sx), m); // 왼쪽 하단
		}
		else if (m - sy == 1) { // 행이 한 줄
			div(inp, sx, sy, divide(n + sx), divide(m + sy)); // 왼쪽 상단
			div(inp, divide(n + sx), sy, n, divide(m + sy)); // 오른쪽 상단
		}
		else {
			div(inp, sx, sy, divide(n + sx), divide(m + sy)); // 왼쪽 상단
			div(inp, divide(n + sx), sy, n, divide(m + sy)); // 오른쪽 상단
			div(inp, sx, divide(m + sy), divide(n + sx), m); // 왼쪽 하단
			div(inp, divide(n + sx), divide(m + sy), n, m); // 오른쪽 하단
		}
	}
	else {
		for (int i = sy; i < m; i++) {
			for (int j = sx; j < n; j++) {
				map[i][j] = f;
			}
		}
	}
}

int main() {
	FILE *inp = fopen("bitmap.inp", "r");
	FILE *out = fopen("bitmap.out", "w");
	while (1) {
		char form, c;
		int m, n;
		cnt = 0;
		fscanf(inp, "%c %d %d\n", &form, &m, &n);
		if (form == '#') break;
		else if (form == 'B') { // B => D
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					fscanf(inp, "%c", &c);
					if (c == '\n') { // 만약 50번째 문자열에서 check가 개행문자이면 열외
						j--;
						continue;
					}
					else map[i][j] = c;
				}
			} // bitmap에 입력
			fprintf(out, "D%4d%4d\n", m, n);
			cond(out, 0, 0, n, m);
			fprintf(out, "\n");
			fscanf(inp, "%c", &c); // 마지막 개행문자 처리
		}
		else { // D => B
			fprintf(out, "B%4d%4d\n", m, n);
			div(inp, 0, 0, n, m);
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					fprintf(out, "%c", map[i][j]);
					cnt++;
					if (cnt % 50 == 0) fprintf(out, "\n");
				}
			}
			if (cnt % 50 != 0) fprintf(out, "\n");
			fscanf(inp, "%c", &c); // 마지막 개행문자 처리
		}
	}
	fclose(inp);
	fclose(out);
	return 0;
}