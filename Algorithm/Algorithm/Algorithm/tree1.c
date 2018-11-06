#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
#define MAX 50010

int cnt, i;

typedef struct Node {
	char name[8];
	char rcheck;
	struct Node *left;
	struct Node *right;
}Node;

Node *itos(Node *root, int n) { // integer -> string
	int check = 0, s = 1;
	if (n / 100000 > 0) {
		root->name[s] = n / 100000 + 48;
		check = 1, s++;
	} if (n / 10000 > 0 || check == 1) {
		root->name[s] = (n / 10000) % 10 + 48;
		check = 1, s++;
	} if (n / 1000 > 0 || check == 1) {
		root->name[s] = (n / 1000) % 10 + 48;
		check = 1, s++;
	} if (n / 100 > 0 || check == 1) {
		root->name[s] = (n / 100) % 10 + 48;
		check = 1, s++;
	} if (n / 10 > 0 || check == 1) {
		root->name[s] = (n / 10) % 10 + 48;
		check = 1, s++;
	}
	root->name[s] = n % 10 + 48;
	root->name[0] = 'r';
	root->name[s + 1] = '\0';
	return root;
}

void preorder(Node *root, FILE *out) { // 전위순회
	if (root) {
		if (root->rcheck == 'r') { // 이름 부여
			root = itos(root, cnt);
			cnt++;
		}
		for (int i = 0; i < 8; i++) {
			if (root->name[i] == '\0') break; // 의심
			fprintf(out, "%c", root->name[i]);
		}
		fprintf(out, "\n");
		preorder(root->left, out);
		preorder(root->right, out);
	}
}

void inorder(Node *root, FILE *out) { // 중위순회
	if (root) {
		inorder(root->left, out);
		for (int i = 0; i < 8; i++) {
			if (root->name[i] == '\0') break; // 의심
			fprintf(out, "%c", root->name[i]);
		}
		fprintf(out, "\n");
		inorder(root->right, out);
	}
}

Node *insert(Node *root, FILE *inp, char str[]) {
	Node *newLeft = (Node*)malloc(sizeof(Node));
	newLeft->left = NULL, newLeft->right = NULL;
	root->rcheck = 'r'; // 부모 노드라면 r 표시

	if (i == 0 && str[i] == '(') i++; // 추가
	while (str[i] == ')'||str[i] == ' ') i++;
	if (root->left == NULL) { // 루트 노드의 왼쪽이 비었을 경우
		if (str[i] == '(') { // 괄호(자식노드 추가)
			i++;
			newLeft = insert(newLeft, inp, str);
			root->left = newLeft;
		} else if (str[i] >= 48) {
			for (int j = 0; str[i] != ' ' && j < 8; i++, j++) { // 추가
				newLeft->name[j] = str[i];
			}
			root->left = newLeft;
		}
	}

	while (str[i] == ')' || str[i] == ' ') i++;
	Node *newRight = (Node*)malloc(sizeof(Node));
	newRight->left = NULL, newRight->right = NULL;
	if (root->right == NULL) { // 루트노드의 오른쪽이 비었을 경우
		if (str[i] == '(') { // 괄호(자식노드 추가)
			i++;
			newRight = insert(newRight, inp, str);
			root->right = newRight;
		} else if (str[i] >= 48) {
			for (int j = 0; str[i] != ' ' && j < 8; i++, j++) { // 추가
				newRight->name[j] = str[i];
			}
			root->right = newRight;
		}
	}
	return root;
}

void base(FILE *inp, FILE *out) {
	char str[MAX];
	fgets(str, MAX, inp);
	fprintf(out, "%s", str);
	Node *root = (Node*)malloc(sizeof(Node));
	root->left = NULL, root->right = NULL;  // 루트 초기화
	root = insert(root, inp, str);

	fprintf(out, "Preorder\n");
	preorder(root, out);
	fprintf(out, "Inorder\n");
	inorder(root, out);
}

int main() {
	FILE *inp = fopen("tree.inp", "r");
	FILE *out = fopen("tree.out", "w");

	int testcase;
	fscanf(inp, "%d\n", &testcase);

	for (int j = 0; j < testcase; j++) {
		cnt = 0, i = 0;
		base(inp, out);
	}
	fclose(inp);
	fclose(out);
	return 0;
}