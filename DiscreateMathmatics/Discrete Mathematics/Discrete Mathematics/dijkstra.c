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
		distance[pre][post] = D;                         // 거리에 D 저장
		if (pre != 0) {
			if (distance[0][post] >= distance[0][pre] + D || distance[0][post] == 0) { // 원래 계산된 거리가 새로 계산된 거리보다 크거나, 계산된 거리가 없을 때
				if (distance[0][pre] > 0) {                  // 앞의 계산된 거리가 0이 아닐 경우
					distance[0][post] = distance[0][pre] + D;
					route[post][0] = pre, route[post][1] = post;
				}
				else {                                       // 앞의 계산된 거리가 0일 경우

				}
			}
		}
		else {                                               // 앞의 노드가 0일 경우
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
	}                                                   // 출력
	
	fclose(inp);
	fclose(out);
	return 0;
}