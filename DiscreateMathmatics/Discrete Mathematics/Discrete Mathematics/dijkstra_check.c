#include<stdio.h>
#pragma warning(disable:4996)
int graph[10000][10000], route[10000][10000], queue[10000][10000], count[10000] = { 0 }, distance[10000];

void dijkstra(int start) {
	int i;
	for (i = 0; i < count[start]; i++) {

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
		graph[pre][post] = D;
		queue[pre][count[pre]] = post;
		count[pre]++;

		if (pre == 0) {
			distance[post] = D;
			route[post][1] = post;
		}
	}

	dijkstra(0);

}