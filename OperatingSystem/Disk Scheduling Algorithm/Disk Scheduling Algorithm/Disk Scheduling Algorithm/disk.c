#include<stdio.h>
#pragma warning(disable:4996)

typedef struct request {
	int request;
	int track;
	int distance;
}request;

request Data[1000], Ready[1000];
int service, time = 0, location = 0, DC = 0;
char command[5];

int abs(int x) {
	if (x < 0) x *= -1;
	return x;
}

void Scan(FILE *inp) {
	fscanf(inp, "%s %d", &command, &service);
	for (int i = 0;; i++) {
		fscanf(inp, "%d %d", &Data[i].request, &Data[i].track);
		if (Data[i].request == -1) break;
	}
}

void Scheduling(char command[]) {
	int seq = 0, front = 0, rear = 0;
	int state = 0; // LOOK에서 0이면 상승
	while (1) {
		while (Data[seq].request <= time && Data[seq].request != -1) {
			Ready[rear] = Data[seq];
			Ready[rear].distance = Ready[rear].track - location;
			rear++, seq++;
		} // 시간이 되면 큐에 넣음
		if (command[0] == 'S') { // SSTF일 경우,
			request temp;
			for (int i = front; i < rear; i++) {
				for (int j = front; j < rear - 1; j++) {
					if (abs(Ready[j].distance) > abs(Ready[j + 1].distance)) temp = Ready[j], Ready[j] = Ready[j + 1], Ready[j + 1] = temp;
				}
			}// 가장 거리가 작은 거 순서대로 정렬
		}
		else if (command[0] == 'L') { // LOOK일 경우,
			request temp;
			if (state == 0) { // 상승하며 이동할 때,
				int check = 0;
				for (int i = front; i < rear; i++) {
					for (int j = front; j < rear - 1; j++) {
						if (Ready[j].distance < 0 || Ready[j].distance > Ready[j + 1].distance && Ready[j + 1].distance > 0) temp = Ready[j], Ready[j] = Ready[j + 1], Ready[j + 1] = temp;
					}
				}  // 자기보다 위쪽 트랙에 있는 것들을 순서대로 정렬
				for (int i = front; i < rear; i++) if (Ready[i].distance > 0) check = 1;
				if (check == 0) {
					state = 1;
					for (int i = front; i < rear; i++) {
						for (int j = front; j < rear - 1; j++) {
							if (Ready[j].distance > 0 || abs(Ready[j].distance) > abs(Ready[j + 1].distance) && Ready[j + 1].distance < 0) temp = Ready[j], Ready[j] = Ready[j + 1], Ready[j + 1] = temp;
						}
					}
				}
			}
			else { // 하강하며 이동할 때,
				int check = 0;
				for (int i = front; i < rear; i++) {
					for (int j = front; j < rear - 1; j++) {
						if (Ready[j].distance > 0 || abs(Ready[j].distance) > abs(Ready[j + 1].distance) && Ready[j + 1].distance<0) temp = Ready[j], Ready[j] = Ready[j + 1], Ready[j + 1] = temp;
					}
				}  // 자기보다 아래쪽 트랙에 있는 것들을 순서대로 정렬
				for (int i = front; i < rear; i++) if (Ready[i].distance < 0) check = 1;
				if (check == 0) {
					state = 0;
					for (int i = front; i < rear; i++) {
						for (int j = front; j < rear - 1; j++) {
							if (Ready[j].distance < 0 || Ready[j].distance > Ready[j + 1].distance && Ready[j + 1].distance > 0) temp = Ready[j], Ready[j] = Ready[j + 1], Ready[j + 1] = temp;
						}
					}
				}
			}
		}
		if (front != rear) {
			location = Ready[front].track, time = time + abs(Ready[front].distance) + service;
			Ready[front].track = 0, Ready[front].request = 0, Ready[front].distance = 0;
			front++;
			for (int i = front; i < rear; i++) Ready[i].distance = Ready[i].track - location;
		} // 큐 안에 있을 경우에 우선적으로 사용
		else {
			if (Data[seq].request != -1) time = Data[seq].request; // 아직 요청 리스트가 끝이 아닌 경우에 시간을 그때로 이동
			else break; // 종료
		}
	}
}

int main() {
	FILE *inp = fopen("disk.inp", "r");
	FILE *out = fopen("disk.out", "w");
	Scan(inp);
	Scheduling(command);
	fprintf(out, "%d %d", time, location);
	fclose(inp);
	fclose(out);
	return 0;
}