#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int heap[1000010], size = 0;

void Exchange(int index1, int index2) { // ��ȯ
	int temp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = temp;
}

void Insert(int num) { // ����
	size++;
	heap[size] = num;
	int search = size;
	while (search != 1) { // Insertion �˰���
		if (heap[search] > heap[(search / 2)]) Exchange(search, search / 2);
		else break;
		search /= 2;
	}
}

void Delete() { // ����
	heap[1] = heap[size];
	heap[size] = -1, size--;
	int search = 1;
	while ((search * 2) <= size) { // adjust �˰���
		if (heap[search * 2] < heap[(search * 2) + 1]) { // ������ �ڽ��� �� ũ��
			if (heap[search] < heap[(search * 2) + 1]) {
				Exchange(search, (search * 2) + 1);
				search = (search * 2) + 1;
			}
			else break;
		}
		else { // ������ �� ũ��
			if (heap[search] < heap[(search * 2)]) {
				Exchange(search, (search * 2));
				search *= 2;
			}
			else break;
		}
	}
}

void Report(FILE *out) { // ���
	int search = 1;
	while (search <= size) { // ���� ���θ� �̵�
		fprintf(out, "%d ", heap[search]);
		search *= 2;
	}
	fprintf(out, "\n");
}

int main() {
	FILE *inp = fopen("queue.inp", "r");
	FILE *out = fopen("queue.out", "w");

	char str[1000000] = { 0 };
	while (1) {
		fscanf(inp, "%s", &str);
		if (str[0] == 'q') break;
		else if (str[0] == 'r') Report(out);
		else if (str[0] == 'd') Delete();
		else {
			int num = atoi(str);
			Insert(num);
		}
	}
	fclose(inp);
	fclose(out);
	return 0;
}