#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

int route[10000000];
int length;
int map[11000][11000], check[11000][11000];
int width, height;

int Discover(FILE *out, int x, int y, int pre) { // pre가 0 -> 북, 1 -> 동, 2 -> 남, 3 -> 서
	route[length] = ((x - 1) * width) + (y - 1);
	length++;
	if (route[length - 1] == (width * height) - 1) {
		for (int i = 0; i < length; i++) fprintf(out, "%d\n", route[i]);
		exit(-1);
	} else if (check[x][y] == 1) { // 이미 한 번 지나온 경로인지 확인
		route[length - 1] = 0;
		length--;
		return 0;
	} else {
		check[x][y] = 1;
		if (pre != 0 && (map[x - 1][y] == 3 || map[x - 1][y] == 2)) if (Discover(out, x - 1, y, 2)) return 1; // 북쪽으로 간다
		if (pre != 1 && (map[x][y] == 3 || map[x][y] == 1)) if (Discover(out, x, y + 1, 3)) return 1; // 동쪽으로 간다
		if (pre != 2 && (map[x][y] == 3 || map[x][y] == 2)) if (Discover(out, x + 1, y, 0)) return 1; // 남쪽으로 간다
		if (pre != 3 && (map[x][y - 1] == 3 || map[x][y - 1] == 1)) if (Discover(out, x, y - 1, 1)) return 1; // 서쪽으로 간다
	}
	route[length -1] = 0;
	length--;
	return 0;
}

int main() {
	FILE *inp = fopen("maze.inp", "r");
	FILE *out = fopen("maze.out", "w");

	fscanf(inp, "%d %d\n", &height, &width);
	while (1) {
		int point, type;
		fscanf(inp, "%d %d", &point, &type);
		if (point == -1) break;
		else map[(point / width) + 1][(point % width) + 1] = type;
	}
	if (!Discover(out, 1, 1, 0)) fprintf(out, "No Solution!\n");
	fclose(inp);
	fclose(out);
	return 0;
}