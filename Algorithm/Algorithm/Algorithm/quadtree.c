#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

int now;
char str[1010];

typedef struct Node {
	char type;
	struct Node *ul;
	struct Node *ur;
	struct Node *dl;
	struct Node *dr;
}Node;

Node *CreateNode(char type) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->type = type;
	newNode->ul = NULL;
	newNode->ur = NULL;
	newNode->dl = NULL;
	newNode->dr = NULL;
	return newNode;
}

void Insert(Node *root) { // ���� ����
	if (str[now] == 'X') {
		root->ul = CreateNode(str[now]), now++;
		Insert(root->ul);
	}
    else root->ul = CreateNode(str[now]), now++; // ul
	if (str[now] == 'X') {
		root->ur = CreateNode(str[now]), now++;
		Insert(root->ur);
	}
	else root->ur = CreateNode(str[now]), now++; // ur
	if (str[now] == 'X') {
		root->dl = CreateNode(str[now]), now++;
		Insert(root->dl);
	}
	else root->dl = CreateNode(str[now]), now++; // dl
	if (str[now] == 'X') {
		root->dr = CreateNode(str[now]), now++;
		Insert(root->dr);
	}
	else root->dr = CreateNode(str[now]), now++; // dr
}

void up_down(Node *root) { // ���� ����
	if (root != NULL) {
		up_down(root->ul);
		up_down(root->ur);
		up_down(root->dl);
		up_down(root->dr);
		Node *temp;
		temp = root->ul;
		root->ul = root->dl;
		root->dl = temp; // ���� ���Ʒ� ����
		temp = root->ur;
		root->ur = root->dr;
		root->dr = temp; // ������ ���Ʒ� ����
	}
}

void left_right(Node *root) { // �¿� ����
	if (root != NULL) {
		left_right(root->ul);
		left_right(root->ur);
		left_right(root->dl);
		left_right(root->dr);
		Node *temp;
		temp = root->ul;
		root->ul = root->ur;
		root->ur = temp; // ���� ����
		temp = root->dl;
		root->dl = root->dr;
		root->dr = temp; // �Ʒ��� ����
	}
}

void right_90(Node *root) {
	if (root != NULL) {
		right_90(root->ul);
		right_90(root->ur);
		right_90(root->dl);
		right_90(root->dr);
		Node *temp;
		temp = root->ul;
		root->ul = root->ur;
		root->ur = temp; // ���� ����
		temp = root->dl;
		root->dl = root->ul;
		root->ul = temp; // ���� ����
		temp = root->dr;
		root->dr = root->dl;
		root->dl = temp; // �Ʒ��� ����
	}
}

void Format(Node *tree, int form) {
	switch (form) {
	case 1:
		up_down(tree);
		break;
	case 2:
		left_right(tree);
		break;
	case 3:
		right_90(tree);
		break;
	case 4:
		right_90(tree);
		right_90(tree);
		break;
	default:
		right_90(tree);
		right_90(tree);
		right_90(tree);
		break;
	}
}

void PreOrder(FILE *out, Node *root) {
	if (root != NULL) {
		fprintf(out, "%c", root->type);
		PreOrder(out, root->ul);
		PreOrder(out, root->ur);
		PreOrder(out, root->dl);
		PreOrder(out, root->dr);
	}
}

int main() {
	FILE *inp = fopen("quadtree.inp", "r");
	FILE *out = fopen("quadtree.out", "w");
	int testcase;
	fscanf(inp, "%d\n", &testcase);

	while (testcase--) {
		int re = 2;
		now = 1;
		fscanf(inp, "%s", str);
		Node *tree = CreateNode(str[0]);
		int form1, form2;
		fscanf(inp, "%d %d\n", &form1, &form2);
		if (strlen(str) != 1) {
			Insert(tree); // Ʈ�� ����
			Format(tree, form1);
			Format(tree, form2);
		}
		PreOrder(out, tree);
		fprintf(out, "\n"); // ���
	}
	fclose(inp);
	fclose(out);
	return 0;
}