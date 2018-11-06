#include<stdio.h>
#pragma warning(disable:4996)
int distance[10000][10000], route[10000][2];

void print(FILE *out, int start, int final) {
	if (start == 0) {
		fprintf(out, "V%d ", final);
	}
	else {
		print(out, route[start][0], route[start][1]);
		fprintf(out, "V%d ", final);
	}
}

int main() {
	FILE *inp = fopen("dijkstra.inp", "r");
	FILE *out = fopen("dijkstra.out", "w");
	int vertex, edge;
	int i, j;
	int pre, post, D;
	fscanf(inp, "%d %d\n", &vertex, &edge);
	for (i = 0; i < edge; i++) {
		fscanf(inp, "%d %d %d\n", &pre, &post, &D);
		distance[pre][post] = D;                         // �Ÿ��� D ����
		if (pre != 0) {
			if (distance[0][post] >= distance[0][pre] + D || distance[0][post] == 0) { // ���� ���� �Ÿ��� ���� ���� �Ÿ����� ũ�ų�, ���� �Ÿ��� ���� ��
				if (distance[0][pre] > 0) {                  // ���� ���� �Ÿ��� 0�� �ƴ� ���
					distance[0][post] = distance[0][pre] + D;
					route[post][0] = pre, route[post][1] = post;
				}
				else {                                       // ���� ���� �Ÿ��� 0�� ���

				}
			}
		}
		else {                                               // ���� ��尡 0�� ���
			route[post][0] = 0, route[post][1] = post;
		}
	}
	
	for (i = 1; i < vertex; i++) {
		fprintf(out, "V0 ");
		
		if (distance[0][i] != 0) {
			print(out, route[i][0], route[i][1]);
			fprintf(out, "(%d)\n", distance[0][i]);
		}
		else {
			fprintf(out, "V%d ", i);
			fprintf(out, "(-1)\n");
		}
	}                                                   // ���
	
	fclose(inp);
	fclose(out);
	return 0;
}