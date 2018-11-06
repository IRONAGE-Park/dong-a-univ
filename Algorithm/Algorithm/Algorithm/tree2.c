#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAX 10000

typedef struct node { // 트리의 노드
	int num;
	struct node *left;
	struct node *right;
}node;

typedef struct data { // 리스트 형태
	int num;
	int state; // 1이면 어딘가에서 사용중
}data;

int num, check = 0; // check = list 위치 변수
data in_list[MAX], list[MAX];

int scan(FILE *inp) { // 파일 입력
	int form;
	int k = 2;
	int algo;
	while (k--) {
		fscanf(inp, "%d", &form);
		if (form == -1) for (int i = 0; i < num; i++) {
			fscanf(inp, "%d", &list[i]);
			algo = -1;
		}
		else if (form == 0) for (int i = 0; i < num; i++) fscanf(inp, "%d", &in_list[i]);
		else {
			for (int i = 0; i < num; i++) fscanf(inp, "%d", &list[i]);
			algo = 1;
		}
	}
	return algo;
}

void pre_Order(FILE *out, node *tree) { // 전위 순회
	if (tree != NULL) {
		fprintf(out, "%d\n", tree->num);
		pre_Order(out, tree->left);
		pre_Order(out, tree->right);
	}
}

void post_Order(FILE *out, node *tree) { // 후위 순휘
	if (tree) {
		post_Order(out, tree->left);
		post_Order(out, tree->right);
		fprintf(out, "%d\n", tree->num);
	}
}

node *pre_in(int now) { // now는 in_list의 index number
	node *newNode = (node*)malloc(sizeof(node));
	newNode->num = in_list[now].num;

	int k = now - 1;
	if (k >= 0 && in_list[k].state != 1) {
		while (in_list[k].state != 1) { // 왼쪽 탐색
			if (in_list[k].num == list[check].num) {
				check++;
				in_list[k].state = 1;
				newNode->left = pre_in(k);
				break;
			}
			else {
				k--;
				if (in_list[k].state == 1) {
					newNode->left = NULL;
					break;
				}
			}
		}
	}
	else newNode->left = NULL;
	k = now + 1;
	if (k < num && in_list[k].state != 1) {
		while (in_list[k].state != 1) { // 오른쪽 탐색
			if (in_list[k].num == list[check].num) {
				check++;
				in_list[k].state = 1;
				newNode->right = pre_in(k);
				break;
			}
			else {
				k++;
				if (in_list[k].state == 1) {
					newNode->right = NULL;
					break;
				}
			}
		}
	}
	else newNode->right = NULL;
	return newNode;
}

node *post_in(int now) {
	node *newNode = (node*)malloc(sizeof(node));
	newNode->num = in_list[now].num;

	int k = now + 1;
	if (k < num && in_list[k].state != 1) {
		while (in_list[k].state != 1) { // 오른쪽 탐색
			if (in_list[k].num == list[check].num) {
				check--;
				in_list[k].state = 1;
				newNode->right = post_in(k);
				break;
			}
			else {
				k++;
				if (in_list[k].state == 1) {
					newNode->right = NULL;
					break;
				}
			}
		}
	}
	else newNode->right = NULL;

	k = now - 1;
	if (k >= 0 && in_list[k].state != 1) {
		while (in_list[k].state != 1) { // 왼쪽 탐색
			if (in_list[k].num == list[check].num) {
				check--;
				in_list[k].state = 1;
				newNode->left = post_in(k);
				break;
			}
			else {
				k--;
				if (in_list[k].state == 1) {
					newNode->left = NULL;
					break;
				}
			}
		}
	}
	else newNode->left = NULL;
	return newNode;
}

int main() {
	FILE *inp = fopen("tree.inp", "r");
	FILE *out = fopen("tree.out", "w");

	fscanf(inp, "%d\n", &num);
	node *tree;
	if (scan(inp) == 1) { // 중위-후위 순회 입력
		int now;
		check = num - 1;
		for (int i = 0; i < num; i++) if (in_list[i].num == list[check].num) now = i, in_list[i].state = 1;
		check--;
		tree = post_in(now);
		pre_Order(out, tree);
	}
	else { // 중위-전위 순회 입력
		int now;
		for (int i = 0; i < num; i++) if (in_list[i].num == list[check].num) now = i, in_list[i].state = 1;
		check++;
		tree = pre_in(now);
		post_Order(out, tree);
	}

	fclose(inp);
	fclose(out);
	return 0;
}