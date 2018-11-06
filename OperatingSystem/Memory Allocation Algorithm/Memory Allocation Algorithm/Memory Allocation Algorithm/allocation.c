#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

typedef struct process {
	int request;
	int execute;
	int size;
}process;

typedef struct memory {
	int address;
	int num;
	int size;
	int end;
}memory;

process list[1000];
int ready[200000];
int processNum;

int firstFit() {
	memory state[1000] = { 0 };
	state[0].address = 0, state[0].end = 1000, state[0].num = -1, state[0].size = 1000;
	int stateSize = 1;
	int front = 0, rear = 0;
	int pNum = 0, time = 0, nextEsc = 1000, last = 0;

	while (pNum < processNum || front != rear) {

		if (list[pNum].request < nextEsc && pNum != processNum) { // 요청만 받음
			time = list[pNum].request;
			for (int i = 0; i < stateSize; i++) {
				if (list[pNum].size < state[i].size && state[i].num == -1) {
					memmove(state + i + 1, state + i, (stateSize - i) * 16); // memmove
					state[i].num = pNum, state[i].size = list[pNum].size, state[i].end = list[pNum].execute + time;
					state[i + 1].num = -1, state[i + 1].address = state[i].address + state[i].size, state[i + 1].size -= state[i].size;
					if (nextEsc > state[i].end) nextEsc = state[i].end;
					stateSize++;
					last = state[i].address;
					break;
				}
				else if (list[pNum].size == state[i].size && state[i].num == -1) {
					state[i].num = pNum, state[i].end = list[pNum].execute + time;
					if (nextEsc > state[i].end) nextEsc = state[i].end;
					last = state[i].address;
					break;
				}
				if (i == stateSize - 1) { // 빈 공간이 없을 경우 ready queue
					ready[rear] = pNum;
					rear++;
				}
			}
			pNum++;
		}

		else { // 두 개 다 진행해야 하거나 종료를 더 빨리 할 때,
			time = nextEsc;
			for (int i = 0; i < stateSize; i++) {
				if (state[i].end == nextEsc) {
					if (i != 0 && state[i - 1].num == -1) {
						state[i].address = state[i - 1].address;
						state[i].end = 1000000;
						state[i].num = -1;
						state[i].size += state[i - 1].size;
						memmove(state + i - 1, state + i, (stateSize - i) * 16); // memmove
						stateSize--;
						state[stateSize].address = 0, state[stateSize].end = 0, state[stateSize].num = 0, state[stateSize].size = 0;
						i--;
					}
					else {
						state[i].end = 1000000;
						state[i].num = -1;
					}
					if (state[i + 1].num == -1) {
						state[i + 1].address = state[i].address;
						state[i + 1].end = 1000000;
						state[i + 1].num = -1;
						state[i + 1].size += state[i].size;
						memmove(state + i, state + i + 1, (stateSize - i) * 16); // memmove
						stateSize--;
						state[stateSize].address = 0, state[stateSize].end = 0, state[stateSize].num = 0, state[stateSize].size = 0;
						i--;
					}
				}
			}
			int length = rear - front, repeat = 0;
			while (front != rear && repeat < length) { // 대기 큐에 프로세스가 기다릴 경우,
				for (int i = 0; i < stateSize; i++) {
					if (list[ready[front]].size < state[i].size && state[i].num == -1) {
						memmove(state + i + 1, state + i, (stateSize - i) * 16); // memmove
						state[i].num = ready[front], state[i].size = list[ready[front]].size, state[i].end = list[ready[front]].execute + time;
						state[i + 1].num = -1, state[i + 1].address = state[i].address + state[i].size, state[i + 1].size -= state[i].size;
						stateSize++;
						ready[front] = -1;
						front++;
						if (state[i].num == processNum - 1) last = state[i].address;
						break;
					}
					else if (list[ready[front]].size == state[i].size && state[i].num == -1) {
						state[i].num = ready[front], state[i].end = list[ready[front]].execute + time;
						ready[front] = -1;
						front++;
						if (state[i].num == processNum - 1) last = state[i].address;
						break;
					}
					if (i == stateSize - 1) {
						ready[rear] = ready[front];
						rear++;
						ready[front] = -1;
						front++;
						break;
					}
				}
				repeat++;
			}
			// 먼저 종료 시킨 뒤 요청 받음
			if (list[pNum].request == nextEsc) {
				for (int i = 0; i < stateSize; i++) {
					if (list[pNum].size < state[i].size && state[i].num == -1) {
						memmove(state + i + 1, state + i, (stateSize - i) * 16); // memmove
						state[i].num = pNum, state[i].size = list[pNum].size, state[i].end = list[pNum].execute + time;
						state[i + 1].num = -1, state[i + 1].address = state[i].address + state[i].size, state[i + 1].size -= state[i].size;
						stateSize++;
						last = state[i].address;
						break;
					}
					else if (list[pNum].size == state[i].size && state[i].num == -1) {
						state[i].num = pNum, state[i].end = list[pNum].execute + time;
						last = state[i].address;
						break;
					}
					if (i == stateSize - 1) { // 빈 공간이 없을 경우 ready queue
						ready[rear] = pNum;
						rear++;
					}
				}
				pNum++;
			}

			nextEsc = 1000000;
			for (int i = 0; i < stateSize; i++) if (nextEsc > state[i].end) nextEsc = state[i].end;
		}
	}
	return last;
}

int bestFit() {
	memory state[1000] = { 0 };
	state[0].address = 0, state[0].end = 1000, state[0].num = -1, state[0].size = 1000;
	int stateSize = 1;
	int front = 0, rear = 0;
	int pNum = 0, time = 0, nextEsc = 1000, last = 0;
	while (pNum < processNum || front != rear) {
		if (list[pNum].request < nextEsc && pNum != processNum) { // 요청만 받음
			time = list[pNum].request;
			int best = 1001, bestP;
			for (int i = 0; i < stateSize; i++) {
				if (list[pNum].size < state[i].size && state[i].num == -1) {
					if (state[i].size < best) {
						best = state[i].size;
						bestP = i;
					}
				}
				else if (list[pNum].size == state[i].size && state[i].num == -1) {
					state[i].num = pNum, state[i].end = list[pNum].execute + time;
					if (nextEsc > state[i].end) nextEsc = state[i].end;
					last = state[i].address;
					break;
				}
				if (i == stateSize - 1) {
					if (best != 1001) {
						memmove(state + bestP + 1, state + bestP, (stateSize - bestP) * 16); // memmove
						state[bestP].num = pNum, state[bestP].size = list[pNum].size, state[bestP].end = list[pNum].execute + time;
						state[bestP + 1].num = -1, state[bestP + 1].address = state[bestP].address + state[bestP].size, state[bestP + 1].size -= state[bestP].size;
						if (nextEsc > state[bestP].end) nextEsc = state[bestP].end;
						stateSize++;
						last = state[bestP].address;
						break;
					}
					else {
						ready[rear] = pNum;
						rear++;
					}
				}
			}
			pNum++;
		}

		else { // 두 개 다 진행해야 하거나 종료를 더 빨리 할 때,
			time = nextEsc;
			for (int i = 0; i < stateSize; i++) {
				if (state[i].end == nextEsc) {
					if (i != 0 && state[i - 1].num == -1) {
						state[i].address = state[i - 1].address;
						state[i].end = 1000000;
						state[i].num = -1;
						state[i].size += state[i - 1].size;
						memmove(state + i - 1, state + i, (stateSize - i) * 16); // memmove
						stateSize--;
						state[stateSize].address = 0, state[stateSize].end = 0, state[stateSize].num = 0, state[stateSize].size = 0;
						i--;
					}
					else {
						state[i].end = 1000000;
						state[i].num = -1;
					}
					if (state[i + 1].num == -1) {
						state[i + 1].address = state[i].address;
						state[i + 1].end = 1000000;
						state[i + 1].num = -1;
						state[i + 1].size += state[i].size;
						memmove(state + i, state + i + 1, (stateSize - i) * 16); // memmove
						stateSize--;
						state[stateSize].address = 0, state[stateSize].end = 0, state[stateSize].num = 0, state[stateSize].size = 0;
						i--;
					}
				}
			}
			int length = rear - front, repeat = 0;
			while (front != rear && repeat < length) { // 대기 큐에 프로세스가 기다릴 경우,
				int best = 1001, bestP;
				for (int i = 0; i < stateSize; i++) {
					if (list[ready[front]].size < state[i].size && state[i].num == -1) {
						if (state[i].size < best) {
							best = state[i].size;
							bestP = i;
						}

					}
					else if (list[ready[front]].size == state[i].size && state[i].num == -1) {
						state[i].num = ready[front], state[i].end = list[ready[front]].execute + time;
						ready[front] = -1;
						front++;
						if (state[i].num == processNum - 1) last = state[i].address;
						break;
					}
					if (i == stateSize - 1) {
						if (best != 1001) {
							memmove(state + bestP + 1, state + bestP, (stateSize - bestP) * 16); // memmove
							state[bestP].num = ready[front], state[bestP].size = list[ready[front]].size, state[bestP].end = list[ready[front]].execute + time;
							state[bestP + 1].num = -1, state[bestP + 1].address = state[bestP].address + state[bestP].size, state[bestP + 1].size -= state[bestP].size;
							stateSize++;
							ready[front] = -1;
							front++;
							if (state[bestP].num == processNum - 1) last = state[bestP].address;
							break;
						}
						else {
							ready[rear] = ready[front];
							rear++;
							ready[front] = -1;
							front++;
							break;
						}
					}
				}
				repeat++;
			}
			// 먼저 종료 시킨 뒤 요청 받음
			if (list[pNum].request == nextEsc) {
				int best = 1001, bestP;
				for (int i = 0; i < stateSize; i++) {
					if (list[pNum].size < state[i].size && state[i].num == -1) {
						if (state[i].size < best) {
							best = state[i].size;
							bestP = i;
						}
					}
					else if (list[pNum].size == state[i].size && state[i].num == -1) {
						state[i].num = pNum, state[i].end = list[pNum].execute + time;
						if (nextEsc > state[i].end) nextEsc = state[i].end;
						last = state[i].address;
						break;
					}
					if (i == stateSize - 1) {
						if (best != 1001) {
							memmove(state + bestP + 1, state + bestP, (stateSize - bestP) * 16); // memmove
							state[bestP].num = pNum, state[bestP].size = list[pNum].size, state[bestP].end = list[pNum].execute + time;
							state[bestP + 1].num = -1, state[bestP + 1].address = state[bestP].address + state[bestP].size, state[bestP + 1].size -= state[bestP].size;
							if (nextEsc > state[bestP].end) nextEsc = state[bestP].end;
							stateSize++;
							last = state[bestP].address;
							break;
						}
						else {
							ready[rear] = pNum;
							rear++;
						}
					}
				}
				pNum++;
			}

			nextEsc = 1000000;
			for (int i = 0; i < stateSize; i++) if (nextEsc > state[i].end) nextEsc = state[i].end;
		}
	}
	return last;
}

int worstFit() {
	memory state[1000] = { 0 };
	state[0].address = 0, state[0].end = 1000, state[0].num = -1, state[0].size = 1000;
	int stateSize = 1;
	int front = 0, rear = 0;
	int pNum = 0, time = 0, nextEsc = 1000, last = 0;
	while (pNum < processNum || front != rear) {
		if (list[pNum].request < nextEsc && pNum != processNum) { // 요청만 받음
			time = list[pNum].request;
			int worst = 0, worstP;
			for (int i = 0; i < stateSize; i++) {
				if (list[pNum].size <= state[i].size && state[i].num == -1) {
					if (state[i].size > worst) {
						worst = state[i].size;
						worstP = i;
					}
				}
				if (i == stateSize - 1) {
					if (worst != 0) {
						if (list[pNum].size == state[worstP].size) {
							state[worstP].num = pNum, state[worstP].end = list[pNum].execute + time;
							if (nextEsc > state[worstP].end) nextEsc = state[worstP].end;
							last = state[worstP].address;
							break;
						}
						else {
							memmove(state + worstP + 1, state + worstP, (stateSize - worstP) * 16); // memmove
							state[worstP].num = pNum, state[worstP].size = list[pNum].size, state[worstP].end = list[pNum].execute + time;
							state[worstP + 1].num = -1, state[worstP + 1].address = state[worstP].address + state[worstP].size, state[worstP + 1].size -= state[worstP].size;
							if (nextEsc > state[worstP].end) nextEsc = state[worstP].end;
							stateSize++;
							last = state[worstP].address;
							break;
						}
					}
					else {
						ready[rear] = pNum;
						rear++;
					}
				}
			}
			pNum++;
		}

		else { // 두 개 다 진행해야 하거나 종료를 더 빨리 할 때,
			time = nextEsc;
			for (int i = 0; i < stateSize; i++) {
				if (state[i].end == nextEsc) {
					if (i != 0 && state[i - 1].num == -1) {
						state[i].address = state[i - 1].address;
						state[i].end = 1000000;
						state[i].num = -1;
						state[i].size += state[i - 1].size;
						memmove(state + i - 1, state + i, (stateSize - i) * 16); // memmove
						stateSize--;
						state[stateSize].address = 0, state[stateSize].end = 0, state[stateSize].num = 0, state[stateSize].size = 0;
						i--;
					}
					else {
						state[i].end = 1000000;
						state[i].num = -1;
					}
					if (state[i + 1].num == -1) {
						state[i + 1].address = state[i].address;
						state[i + 1].end = 1000000;
						state[i + 1].num = -1;
						state[i + 1].size += state[i].size;
						memmove(state + i, state + i + 1, (stateSize - i) * 16); // memmove
						stateSize--;
						state[stateSize].address = 0, state[stateSize].end = 0, state[stateSize].num = 0, state[stateSize].size = 0;
						i--;
					}
				}
			}
			int length = rear - front, repeat = 0;
			while (front != rear && repeat < length) { // 대기 큐에 프로세스가 기다릴 경우,
				int worst = 0, worstP;
				for (int i = 0; i < stateSize; i++) {
					if (list[ready[front]].size <= state[i].size && state[i].num == -1) {
						if (state[i].size > worst) {
							worst = state[i].size;
							worstP = i;
						}

					}
					if (i == stateSize - 1) {
						if (worst != 0) {
							if (list[ready[front]].size == state[worstP].size) {
								state[worstP].num = ready[front], state[worstP].end = list[ready[front]].execute + time;
								ready[front] = -1;
								front++;
								if (state[worstP].num == processNum - 1) last = state[worstP].address;
								break;
							}
							else {
								memmove(state + worstP + 1, state + worstP, (stateSize - worstP) * 16); // memmove
								state[worstP].num = ready[front], state[worstP].size = list[ready[front]].size, state[worstP].end = list[ready[front]].execute + time;
								state[worstP + 1].num = -1, state[worstP + 1].address = state[worstP].address + state[worstP].size, state[worstP + 1].size -= state[worstP].size;
								stateSize++;
								ready[front] = -1;
								front++;
								if (state[worstP].num == processNum - 1) last = state[worstP].address;
								break;
							}
						}
						else {
							ready[rear] = ready[front];
							rear++;
							ready[front] = -1;
							front++;
							break;
						}
					}
				}
				repeat++;
			}
			// 먼저 종료 시킨 뒤 요청 받음
			if (list[pNum].request == nextEsc) {
				int worst = 0, worstP;
				for (int i = 0; i < stateSize; i++) {
					if (list[pNum].size <= state[i].size && state[i].num == -1) {
						if (state[i].size > worst) {
							worst = state[i].size;
							worstP = i;
						}
					}
					if (i == stateSize - 1) {
						if (worst != 0) {
							if (list[pNum].size == state[worstP].size) {
								state[worstP].num = pNum, state[worstP].end = list[pNum].execute + time;
								if (nextEsc > state[worstP].end) nextEsc = state[worstP].end;
								last = state[worstP].address;
								break;
							}
							else {
								memmove(state + worstP + 1, state + worstP, (stateSize - worstP) * 16); // memmove
								state[worstP].num = pNum, state[worstP].size = list[pNum].size, state[worstP].end = list[pNum].execute + time;
								state[worstP + 1].num = -1, state[worstP + 1].address = state[worstP].address + state[worstP].size, state[worstP + 1].size -= state[worstP].size;
								if (nextEsc > state[worstP].end) nextEsc = state[worstP].end;
								stateSize++;
								last = state[worstP].address;
								break;
							}
						}
						else {
							ready[rear] = pNum;
							rear++;
						}
					}
				}
				pNum++;
			}

			nextEsc = 1000000;
			for (int i = 0; i < stateSize; i++) if (nextEsc > state[i].end) nextEsc = state[i].end;
		}
	}
	return last;
}

int main() {
	FILE *inp = fopen("allocation.inp", "r");
	FILE *out = fopen("allocation.out", "w");
	fscanf(inp, "%d\n", &processNum);
	for (int i = 0; i < processNum; i++) fscanf(inp, "%d %d %d\n", &list[i].request, &list[i].execute, &list[i].size);
	// input
	fprintf(out, "%d\n%d\n%d", firstFit(), bestFit(), worstFit());
	// output
	fclose(inp);
	fclose(out);
	return 0;
}