#include<stdio.h>
#pragma warning(disable:4996)

int max[50][50] = { 0 };
int allocation[50][50] = { 0 };
int bank[50] = { 0 };
int use[50] = { 0 };
int ready[1000][51] = { 0 };
int n, m, read, queue = 0;

void request(FILE* f_inp, FILE* f_out) {

	int check = 0, process;

	fscanf(f_inp, "%d", &read);
	process = read;

	for (int i = 0; i < m; i++) {
		fscanf(f_inp, "%d", &read);
		use[i] = read;
		if (use[i] > bank[i]) {
			if (use[i] + allocation[process][i] > max[process][i]) {
				check = 1; //����
			}
			else {
				check = 2; // ���ť
			}
		}
	}

	if (check == 0) {
		for (int i = 0; i < m; i++) {
			allocation[process][i] += use[i];
			bank[i] -= use[i];
		}
		//�������� Ȯ��
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (bank[i] + allocation[i][j] <= max[i][j]) {
					check = 2;
					break;
				}
			}
			if (check == 2) {
				break;
			}
		}
		if (check == 2) {
			for (int i = 0; i < m; i++) {
				allocation[process][i] -= use[i];
				bank[i] += use[i];
			}
		}
	}
	else if (check == 2) {
		ready[queue][0] = process;
		for (int i = 1; i < m + 1; i++) {
			ready[queue][i] = use[i - 1];
		}
		queue++;
	}
}

void release(FILE* f_inp, FILE* f_out) {

	int check = 0, process;

	fscanf(f_inp, "%d", &read);
	process = read;

	for (int i = 0; i < m; i++) {
		fscanf(f_inp, "%d", &read);
		use[i] = read;
		if (use[i] > allocation[process][i]) {
			check = 1;
		}
	}

	if (check == 0) {
		for (int i = 0; i < m; i++) {
			allocation[process][i] -= use[i];
			bank[i] += use[i];
		}
	}
	if (queue != 0) {
		for (int i = 0; i < queue; i++) {
			process = ready[i][0];
			check = 0;
			if (ready[i][0] != -1) {
				for (int j = 1; j < m + 1; j++) {
					if (ready[i][j] > bank[j - 1]) {
						check = 1;
					}
				}
				if (check == 0) {
					for (int j = 1; j < m + 1; j++) {
						allocation[process][j - 1] += ready[i][j];
						bank[j - 1] -= ready[i][j];
					}
					ready[i][0] = -1;
				}
			}
		}
	}
}

int main() {

	FILE* f_inp = fopen("banker.inp", "rt");
	FILE* f_out = fopen("banker.out", "wt");

	//�࿭ũ��
	fscanf(f_inp, "%d %d", &n, &m);

	//�ڿ��� �Է�
	for (int i = 0; i < m; i++) {
		fscanf(f_inp, "%d", &read);
		bank[i] = read;
	}

	//max �Է�
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fscanf(f_inp, "%d", &read);
			max[i][j] = read;
		}
	}

	//allocation �Է�
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fscanf(f_inp, "%d", &read);
			allocation[i][j] = read;
		}
	}

	//������ �ʱⰪ
	for (int j = 0; j < m; j++) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			sum += allocation[i][j];
		}
		bank[j] -= sum;
	}

	char problom[8];

	//��û�� ��ȯ
	while (1) {
		fscanf(f_inp, "%s", &problom);
		if (problom[0] == 'q') {
			break;
		}
		else if (problom[2] == 'q') {
			request(f_inp, f_out);
		}
		else if (problom[2] == 'l') {
			release(f_inp, f_out);
		}
		for (int i = 0; i < m; i++) {
			fprintf(f_out, "%d ", bank[i]);
		}
		fprintf(f_out, "\n");

	}

	return 0;
}