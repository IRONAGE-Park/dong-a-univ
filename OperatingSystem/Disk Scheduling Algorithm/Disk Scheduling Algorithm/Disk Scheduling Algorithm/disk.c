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
	int state = 0; // LOOK���� 0�̸� ���
	while (1) {
		while (Data[seq].request <= time && Data[seq].request != -1) {
			Ready[rear] = Data[seq];
			Ready[rear].distance = Ready[rear].track - location;
			rear++, seq++;
		} // �ð��� �Ǹ� ť�� ����
		if (command[0] == 'S') { // SSTF�� ���,
			request temp;
			for (int i = front; i < rear; i++) {
				for (int j = front; j < rear - 1; j++) {
					if (abs(Ready[j].distance) > abs(Ready[j + 1].distance)) temp = Ready[j], Ready[j] = Ready[j + 1], Ready[j + 1] = temp;
				}
			}// ���� �Ÿ��� ���� �� ������� ����
		}
		else if (command[0] == 'L') { // LOOK�� ���,
			request temp;
			if (state == 0) { // ����ϸ� �̵��� ��,
				int check = 0;
				for (int i = front; i < rear; i++) {
					for (int j = front; j < rear - 1; j++) {
						if (Ready[j].distance < 0 || Ready[j].distance > Ready[j + 1].distance && Ready[j + 1].distance > 0) temp = Ready[j], Ready[j] = Ready[j + 1], Ready[j + 1] = temp;
					}
				}  // �ڱ⺸�� ���� Ʈ���� �ִ� �͵��� ������� ����
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
			else { // �ϰ��ϸ� �̵��� ��,
				int check = 0;
				for (int i = front; i < rear; i++) {
					for (int j = front; j < rear - 1; j++) {
						if (Ready[j].distance > 0 || abs(Ready[j].distance) > abs(Ready[j + 1].distance) && Ready[j + 1].distance<0) temp = Ready[j], Ready[j] = Ready[j + 1], Ready[j + 1] = temp;
					}
				}  // �ڱ⺸�� �Ʒ��� Ʈ���� �ִ� �͵��� ������� ����
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
		} // ť �ȿ� ���� ��쿡 �켱������ ���
		else {
			if (Data[seq].request != -1) time = Data[seq].request; // ���� ��û ����Ʈ�� ���� �ƴ� ��쿡 �ð��� �׶��� �̵�
			else break; // ����
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