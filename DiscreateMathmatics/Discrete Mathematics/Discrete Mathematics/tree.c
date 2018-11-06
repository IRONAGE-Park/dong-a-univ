#include<stdio.h>
#pragma warning(disable:4996)

typedef struct Node {
	int nodeNumber;
	int parentCount;
	int sonCount;
}Node;

Node node[1000000];

int main() {
	FILE *inp = fopen("tree.inp", "r");
	FILE *out = fopen("tree.out", "w");
	int testcase = 1;
	int parent, son;
	int nodecount = 0;
	int nottree = 0, rootNode = 0, cycle = 1, rootcount = 0;
	while (1) {
		fscanf(inp, "%d %d\n", &parent, &son);
		if (parent == -1 || son == -1) {
			break;
		}                     // 입력파일 끝

		if (parent == 0 || son == 0) {  // 한 테스트케이스 끝
			for (int i = 0; i < nodecount; i++) {
				if (node[i].sonCount == 0) {
					rootNode = node[i].nodeNumber;
					rootcount++;
					cycle = 0;
				}
				node[i].parentCount = 0, node[i].sonCount = 0;
			}
			if (nottree == 1) {
			    fprintf(out, "Test Case %d: -1\n", testcase); // 그냥 트리가 아닐 때,
				testcase++;
				nottree = 0;
			}
			else {
				if(cycle == 1 || rootcount >= 2) fprintf(out, "Test Case %d: -1\n", testcase); // 사이클이 있거나 루트가 두개일 때,
				else fprintf(out, "Test Case %d: %d\n", testcase, rootNode);
				testcase++;
			}
			cycle = 1;
			rootcount = 0;
			nodecount = 0;
			continue;
		}

		if (nodecount == 0) {   // 각 테스트케이스에서 처음 데이터 받을 때,
			node[nodecount].nodeNumber = parent, node[nodecount].parentCount = 1;
			nodecount++;
			node[nodecount].nodeNumber = son, node[nodecount].sonCount = 1;
			nodecount++;
		}
		else { // 그 이후부터
			int pcheck = 0, scheck = 0;
			for (int i = 0; i < nodecount; i++) {
				if (node[i].nodeNumber == parent) node[i].parentCount++, pcheck = 1;
				if (node[i].nodeNumber == son) {
					node[i].sonCount++;
					scheck = 1;
					if (node[i].sonCount >= 2) {
						nottree = 1;
						break;
					}
				}
				if (pcheck == 1 && scheck == 1) break; // parent와 son 둘 다 값이 들어감
			}
			if (pcheck != 1) { // node[i].parentCount에 값을 한 번도 안 넣음
				node[nodecount].nodeNumber = parent, node[nodecount].parentCount = 1;
				nodecount++;
			}
			if (scheck != 1) { // node[i].sonCount에 값을 한 번도 안 넣음
				node[nodecount].nodeNumber = son, node[nodecount].sonCount = 1;
				nodecount++;
			}
		}
	}
	fclose(inp);
	fclose(out);
	return 0;
}