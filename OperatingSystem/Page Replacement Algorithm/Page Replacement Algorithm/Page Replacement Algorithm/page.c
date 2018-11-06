#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

typedef struct input {
	int PID;
	int page;
}input;

typedef struct memory {
	int PID;
	int page;
	int seq;
	int time;
}memory;

input Data[10000];
memory State[10000];
int frame;
int size = 0;
int fault = 0;
int seq_Num = 0;
int DS = 0, now;
int time = 0;

void update(int PID, int page, int point, char command) {
	State[point].PID = PID, State[point].page = page;
	if (command == 'F' || command == 'L') State[point].seq = seq_Num;
	else {
		int victim_Seq = 0;
		for (int i = now + 1; i < DS; i++) {
			State[point].seq = victim_Seq;
			victim_Seq--;
			if (Data[i].PID == PID && Data[i].page == page) {
				break;
			}
			if (i == DS - 1) State[point].seq = -100000;
		}
		State[point].time = time;
		time++;
	}
	seq_Num++, fault++;
}

void victim_Algorithm(int PID, int page, char command) {
	int victim = 0, victim_Seq = 100000;
	for (int i = 0; i < size; i++) {
		if (State[i].PID == PID && victim_Seq > State[i].seq) {
			victim_Seq = State[i].seq, victim = i;
			if (victim_Seq == -100000) break;
		}
	}
	if (victim_Seq == -100000) {
		for (int i = victim; i < size; i++) {
			if (State[i].PID == PID && State[i].seq == -100000 && State[i].time < State[victim].time) {
				victim = i;
			}
		}
	}
	update(PID, page, victim, command);
}

void Allocation(int PID, int page, char command) {
	int over_Check = 0;
	if (command == 'O') {
		for (int i = 0; i < size; i++) {
			if(State[i].seq != -100000) State[i].seq++;
		}
	}
	for (int i = 0; i < size; i++) {
		if (State[i].PID == PID && State[i].page == page) {
			if (command == 'L') { // LRU�� ��� ������ ����
				State[i].seq = seq_Num;
				seq_Num++;
			}
			else if (command == 'O') {
				int victim_Seq = 0;
				for (int j = now + 1; j < DS; j++) {
					State[i].seq = victim_Seq;
					victim_Seq--;
					if (Data[j].PID == PID && Data[j].page == page) {
						break;
					}
					if (j == DS - 1) State[i].seq = -100000;
				}
			}
			return;
		} // �����ӿ� �ִ� �������¿� �䱸�ϴ� �������°� ���� => ��ȭ��ų �ʿ� ����.
		else if (State[i].PID == PID) {
			over_Check++;
			if (over_Check == frame) break;
		} // �����ӿ� �ִ� ���μ��� ��ȣ�� �䱸�ϴ� ���μ����� ��ȣ�� ����
	}
	if (over_Check == frame) {
		victim_Algorithm(PID, page, command);
	} // victim page�� replacement
	else {
		update(PID, page, size, command);
		size++;
	} // ������ ������ �߰� �Ҵ� �޾ƾ� ��
}

void Memory_Print(FILE *out) {
	for (int i = 0; i < size; i++) {
		fprintf(out, "%d %d %d\n", i, State[i].PID, State[i].page);
		State[i].PID = 0, State[i].page = 0, State[i].seq = 0;
	}
	fault = 0, size = 0, seq_Num = 0;
}

void Memory_Scan(FILE *inp) {
	for (int i = 0;; i++) {
		fscanf(inp, "%d %d\n", &Data[i].PID, &Data[i].page);
		if (Data[i].PID == -1) break;
		DS++;
	}
}

int main() {
	FILE *inp = fopen("page.inp", "r");
	FILE *out = fopen("page.out", "w");
	
	int i = 0, PID, page;
	fscanf(inp, "%d\n", &frame);
	Memory_Scan(inp);
	// �Է�

	for (int i = 0; i < DS; i++) Allocation(Data[i].PID, Data[i].page, 'F');
	// FIFO ����
	fprintf(out, "FIFO: %d\n", fault);
	Memory_Print(out);
	// FIFO ��� ���

	for (int i = 0; i < DS; i++) Allocation(Data[i].PID, Data[i].page, 'L');
	// LRU ����
	fprintf(out, "LRU: %d\n", fault);
	Memory_Print(out);
	// LRU ��� ���

	for (int i = 0; i < DS; i++) now = i, Allocation(Data[i].PID, Data[i].page, 'O');
	// OPT ����
	fprintf(out, "OPT: %d\n", fault);
	Memory_Print(out);
	// OPT ��� ���

	fclose(inp);
	fclose(out);
	return 0;
}