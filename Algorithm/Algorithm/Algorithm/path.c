#include<stdio.h>
#pragma warning(disable:4996)
#define MAX 500
#define INF 99999999

int n, m;
int graph[MAX][MAX], distance = 0, sequence[MAX], s_length = 0;
int D[MAX][MAX], P[MAX][MAX];

void Scan(FILE *inp) {
	while (m--) {
		int i, j, w;
		fscanf(inp, "%d %d %d\n", &i, &j, &w);
		graph[i][j] = w;
	}
}

void path(int S, int T) { // ���Ž�� �˰���
	if (P[S][T] != -1) {
		path(S, P[S][T]);
		sequence[s_length] = P[S][T];
		s_length++;
		path(P[S][T], T);
	}
}

int path_Search(int S, int T, int Not) { // Not�� ������ �ʰ� S���� T������ �ִ� ���
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (graph[i][j] != 0 || i == j) {
				D[i][j] = graph[i][j];
			}
			else {
				D[i][j] = INF;
			}
			P[i][j] = -1;
		}
	}
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (k != Not && D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
	if (D[S][T] > 0 && D[S][T] < INF) { // S���� T������ ���� ������,
		distance += D[S][T];
		sequence[s_length] = S;
		s_length++;
		path(S, T);
		return 1;
	}
	else return 0;
}

int main() {
	FILE *inp = fopen("path.inp", "r");
	FILE *out = fopen("path.out", "w");

	fscanf(inp, "%d %d\n", &n, &m);
	Scan(inp);
	while (1) {
		int S, V, T;
		s_length = 0, distance = 0;
		fscanf(inp, "%d %d %d", &S, &V, &T);
		if (S == -1 || V == -1 || T == -1) break;
		if (path_Search(S, V, T) && path_Search(V, T, S)) { // �ΰ��� ��� ��� ���� ������ 
			for (int i = 0; i < s_length; i++) fprintf(out, "%d ", sequence[i]);
			fprintf(out, "%d (%d)\n", T, distance);
		}
		else fprintf(out, "%d %d %d (-1)\n", S, V, T);
	}
	fclose(inp);
	fclose(out);
	return 0;
}