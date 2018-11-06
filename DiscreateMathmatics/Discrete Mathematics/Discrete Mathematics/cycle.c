#include<stdio.h>
#pragma warning(disable:4996)
int graph[22000][22000];
int graphCount[10000], check, queue[10000], front, rear, lab;

void BreathFirstSearch(int Start, int visit[10000], int level) {            // �ʺ� �켱 Ž��
	visit[Start] = level;
	for (int i = 0; i < graphCount[Start]; i++) {
		if (visit[graph[Start][i]] > 0) {
			if (visit[graph[Start][i]] % 2 == visit[Start] % 2) {
				check = 1;
				break;
			}
			continue;
		}
		queue[rear] = graph[Start][i];
		visit[graph[Start][i]] = level + 1;
		rear++;
	}
}

int main() {
	FILE *inp = fopen("cycle.inp", "r");
	FILE *out = fopen("cycle.out", "w");
	int testcase;
	int vertex, edge, pre, post;
	fscanf(inp, "%d\n", &testcase);
	for (int i = 0; i < testcase; i++) {
		fscanf(inp, "%d %d\n", &vertex, &edge);

		for (int j = 0; j < edge; j++) { // �׷���
			fscanf(inp, "%d %d", &pre, &post);
			graph[pre][graphCount[pre]] = post;
			graphCount[pre]++;
			graph[post][graphCount[post]] = pre;
			graphCount[post]++;
		}

		check = 0;
		int visit1[10000] = { 0 };
		front = 0, rear = 0;
		queue[rear] = 0;
		rear++;
		lab = 1;
		while (front != rear) {
			BreathFirstSearch(queue[front], visit1, lab);
			queue[front] = -1, front++;
			if (visit1[queue[front]] == lab + 1) lab++;
		}
		
		if (check == 1) fprintf(out, "O\n"); // Ȧ������Ŭ
		else fprintf(out, "X\n"); // �ƴ� ��
		for (int x = 0; x < vertex; x++) { // �ʱ�ȭ
			for (int y = 0; y < graphCount[x]; y++) {
				graph[x][y] = 0;
			}
			graphCount[x] = 0;
		}
	}
	fclose(inp);
	fclose(out);
	return 0;
}