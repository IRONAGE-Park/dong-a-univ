#include<stdio.h>
#pragma warning(disable:4996)
#define INF 9999999

int distance[510][510];
int dist_p[510][510];
int data[510];

int abs(int x) {
	if (x > 0) return x;
	else return x * -1;
}
void Merge(int left, int mid, int right) { // 합병
	int i, j, k, m;
	int temp[510];
	i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (data[i] > data[j]) temp[k] = data[j], j++;
		else temp[k] = data[i], i++;
		k++;
	}
	if (i > mid) for (m = j; m <= right; m++) temp[k] = data[m], k++;
	else for (m = i; m <= mid; m++) temp[k] = data[m], k++;
	for (m = left; m <= right; m++) data[m] = temp[m];
}
void Merge_Sort(int left, int right) { // 합병 정렬
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		Merge_Sort(left, mid);
		Merge_Sort(mid + 1, right);
		Merge(left, mid, right);
	}
}
void init_distance(int h, int b){
	for (int i = 0; i <= h; i++) {
		for (int j = 0; j <= b; j++) {
			distance[i][j] = INF;
		}
	}
	for (int i = 0; i < b; i++) distance[0][i] = 0;
}
void set_dist(int h) { // 통이 한 개일때 최솟값 계산
	for (int n = 1; n <= h; n++) {
		for (int m = n; m <= h; m++) {
			int mid = (n + m) / 2;
			for (int k = n; k <= m; k++) {
				dist_p[n][m] += abs(data[mid] - data[k]);
			}
		}
	}
}

void Solve(int h, int b) {
	for (int i = 0; i <= b; i++) {
		distance[0][i] = 0;
	}
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= b; j++) {
			int now = INF;
			for (int k = 1; k <= i; k++) {
				if(now > distance[i - k][j - 1] + dist_p[i - k + 1][i]) now = distance[i - k][j - 1] + dist_p[i - k + 1][i];
			}
			distance[i][j] = now;
		}
	}

}

void all_init(int h, int b) { // 초기화
	for (int i = 0; i <= h; i++) {
		for (int j = 0; j <= b; j++) {
			distance[i][j] = 0;
		}
		for (int j = 0; j <= h; j++) {
			dist_p[i][j] = 0;
		}
		data[i] = 0;
	}
}

int main() {
	FILE *inp = fopen("bin.inp", "r");
	FILE *out = fopen("bin.out", "w");
	int testcase;
	fscanf(inp, "%d\n", &testcase);
	while (testcase--) {
		int h_num, b_num; // h_num = 집의 수, b_num = 쓰레기 통의 수
		fscanf(inp, "%d %d", &h_num, &b_num);
		for (int i = 1; i <= h_num; i++) fscanf(inp, "%d ", &data[i]);
		Merge_Sort(1, h_num); // 정렬
		init_distance(h_num, b_num); // 최댓값 세팅
		set_dist(h_num); // 1개의 통으로 결정할 수 있는 최단거리 세팅
		Solve(h_num, b_num);
		fprintf(out, "%d\n", distance[h_num][b_num]);
		all_init(h_num, b_num); // 모두 초기화
	}
	fclose(inp);
	fclose(out);
	return 0;
}	