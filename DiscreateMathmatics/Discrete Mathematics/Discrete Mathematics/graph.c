#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
int graph[10000][10000], queue[10000], front, rear, graphCount[10000] = { 0 }, distanceGraph[10000][10000];
int load[10000][10000];
int DFS = 0, BFS = 0;

void DepthFirstSearch(int Start, int visit[10000]) {    // 깊이 우선 탐색
	visit[Start] = 1;
	// printf("%d ", Start);
	for (int i = 0; i < graphCount[Start]; i++) {
		if (visit[graph[Start][i]] == 1) {
			continue;
		}
		DFS += distanceGraph[Start][i];
		DepthFirstSearch(graph[Start][i], visit);
	}
}

void BreathFirstSearch(int Start, int visit[10000]) {                           // 너비 우선 탐색
	visit[Start] = 1;
	// printf("%d ", Start);
	for (int i = 0; i < graphCount[Start]; i++) {
		if (visit[graph[Start][i]] == 1) {
			continue;
		}
		BFS += distanceGraph[Start][i];
		queue[rear] = graph[Start][i];
		visit[graph[Start][i]] = 1;
		rear++;
	}
}

int main() {
	FILE *inp = fopen("graph.inp", "r");
	FILE *out = fopen("graph.out", "w");
	int i, j, k, repeat, vertex, edge;
	int pre, post, distance;
	fscanf(inp, "%d\n", &repeat);
	for (i = 0; i < repeat; i++) {
		fscanf(inp, "%d %d\n", &vertex, &edge);
		for (j = 0; j < edge; j++) {
			fscanf(inp, "%d %d %d\n", &pre, &post, &distance);
			load[pre][post] = distance;
			load[post][pre] = distance;
		}                           // 그래프 배열에 거리 가중치 저장
		int x, y;
		for (x = 0; x < vertex; x++) {
			for (y = 0; y < vertex; y++) {
				if (load[x][y] > 0) {
					graph[x][graphCount[x]] = y;
					distanceGraph[x][graphCount[x]] = load[x][y];
					graphCount[x]++;
					load[x][y] = 0;
				}
			}
		}
		// printf("------------------------- Case = %d ----------------------\n", i + 1);
		int startrepeat, start;
		fscanf(inp, "%d", &startrepeat);
		for (j = 0; j < startrepeat; j++) {
			fscanf(inp, "%d", &start);
			// printf("Start : %d\n", start);
			int visit1[10000] = { 0 };
			front = 0, rear = 0;
			queue[rear] = start;
			rear++;
			// printf("BFS : ");
			while (front != rear) {
				BreathFirstSearch(queue[front], visit1);
				queue[front] = -1, front++;
			}
			// printf("\nDFS : ");
			int visit2[10000] = { 0 };
			DepthFirstSearch(start, visit2);
			// printf("\n\n");
			fprintf(out, "n=%d m=%d start=%d DFS:%d BFS:%d\n", vertex, edge, start, DFS, BFS);
			DFS = 0;
			BFS = 0;
		}
		for (x = 0; x < vertex; x++) {
			for (y = 0; y < graphCount[x]; y++) {
				graph[x][y] = 0;
				distanceGraph[x][y] = 0;
			}
			graphCount[x] = 0;
		}
	}

	fclose(inp);
	fclose(out);
	return 0;
}