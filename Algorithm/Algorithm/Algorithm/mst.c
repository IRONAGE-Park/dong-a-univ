#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct Input{ // input data 저장 <- 간선 정보
	int u;
	int v;
	int w;
	int num;
}Input;

typedef struct Node{ // find용
	int vertex;
	int height;
	struct Node *parent;
}Node;

typedef struct Graph { // 그래프 구조체
	struct Graph *next;
	struct Input data;
}Graph;

int vertex, edge;
Input data[100010], temp[100010];
Graph *graph[10010], *Last[10010];
Node *List[10010];

void Scan(FILE *inp) { // input.
	fscanf(inp, "%d %d", &vertex, &edge);
	for (int i = 0; i < vertex; i++) {
		List[i] = (Node*)malloc(sizeof(Node)), List[i]->vertex = i, List[i]->parent = NULL, List[i]->height = 0;
		graph[i] = (Graph*)malloc(sizeof(Graph)), graph[i]->next = NULL;
		Last[i] = (Graph*)malloc(sizeof(Graph)), Last[i]->next = graph[i];
	}
	for (int i = 0; i < edge; i++) {
		fscanf(inp, "%d %d %d", &data[i].u, &data[i].v, &data[i].w);
		data[i].num = i;
		Graph *temp1 = Last[data[i].u]->next, *temp2 = Last[data[i].v]->next;
		temp1->next = (Graph*)malloc(sizeof(Graph));
		temp1->next->next = NULL, temp1->next->data = data[i];
		Last[data[i].u]->next = temp1->next;
		temp2->next = (Graph*)malloc(sizeof(Graph));
		temp2->next->next = NULL, temp2->next->data = data[i];
		Last[data[i].v]->next = temp2->next;
	}
}
void Merge(int left, int mid, int right) { // 합병
	int i, j, k, m;
	i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (data[i].w > data[j].w) temp[k] = data[j], j++;
		else temp[k] = data[i], i++;
		k++;
	}
	if (i > mid) for (m = j; m <= right; m++) temp[k] = data[m], k++;
	else for (m = i; m <= mid; m++) temp[k] = data[m], k++;
	for (m = left; m <= right; m++) data[m] = temp[m];
}
void Merge_Sort(int left, int right) { // kruskal에서 사용할 간선 정렬
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		Merge_Sort(left, mid);
		Merge_Sort(mid + 1, right);
		Merge(left, mid, right);
	}
}
int Find(Node *node) { // find 연산
	Node *temp = node;
	int h = 0;
	while (temp->parent != NULL) {
		temp = temp->parent;
		h++;
	}
	temp->height = h;
	return temp->vertex;
}
void Kruskal(FILE *out) {
	Merge_Sort(0, edge - 1); // 모든 edge를 오름차순으로 정렬
	int edge_num = 0, seq = 0, sum = 0; // num = 포함된 간선 갯수
	int select[10010];
	while (edge_num < vertex - 1 && edge - 1 > seq) {
		if (List[data[seq].u]->parent == NULL && List[data[seq].v]->parent == NULL) { // 둘 다 부모 노드가 없으면
			List[data[seq].v]->parent = List[data[seq].u]; 
			select[edge_num] = data[seq].num;
			sum += data[seq].w;
			edge_num++; 
		} // 두 개의 노드를 연결 -> edge 추가
		else { // 부모 노드가 존재하면
			int find_pointer_v = Find(List[data[seq].v]); // 불 필요한 연산 제거
			int find_pointer_u = Find(List[data[seq].u]);
			if (find_pointer_u != find_pointer_v) { // 두 노드가 같은 부모를 가리키는지 확인
				if (List[find_pointer_u]->height < List[find_pointer_v]->height) List[find_pointer_u]->parent = List[data[seq].v];
				else List[find_pointer_v]->parent = List[data[seq].u];
				select[edge_num] = data[seq].num;
				sum += data[seq].w;
				edge_num++;
			} // 다른 부모를 가리킬 경우 한 쪽 부모 노드를 다른 쪽의 자식으로 연결 -> edge 추가
		}
		seq++;
	}
	fprintf(out, "Tree edges by Kruskal algorithm: %d\n", sum);
	for (int i = 0; i < edge_num; i++) fprintf(out, "%d\n", select[i]);
}

Input heap[200020];
int size = 0;
void Exchange(int index1, int index2) { // 교환
	Input temp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = temp;
}
void Insert(Input edge) { // 삽입
	size++;
	heap[size] = edge;
	int search = size;
	while (search != 1) { // Insertion 알고리즘
		if (heap[search].w < heap[(search / 2)].w) Exchange(search, search / 2);
		else if (heap[search].w == heap[(search / 2)].w) {
			if (heap[search].num < heap[(search / 2)].num) Exchange(search, search / 2);
		}
		else break;
		search /= 2;
	}
}
Input Dequeue() { // 삭제
	Input temp = heap[1];
	heap[1] = heap[size];
	heap[size].num = -1, heap[size].u = -1, heap[size].v = -1, heap[size].w = 99999, size--;
	int search = 1;
	while ((search * 2) <= size) { // adjust 알고리즘
		if (heap[search * 2].w > heap[(search * 2) + 1].w) {
			if (heap[search].w > heap[(search * 2) + 1].w) {
				Exchange(search, (search * 2) + 1);
				search = (search * 2) + 1;
			}
			else break;
		}
		else if (heap[search * 2].w == heap[(search * 2) + 1].w && heap[search * 2].w < heap[search].w) {
			if (heap[search * 2].num < heap[(search * 2) + 1].num) {
				Exchange(search, search * 2);
				search *= 2;
			}
			else {
				Exchange(search, (search * 2) + 1);
				search = (search * 2) + 1;
			}
		}
		else { 
			if (heap[search].w > heap[(search * 2)].w) {
				Exchange(search, (search * 2));
				search *= 2;
			}
			else break;
		}
	}
	return temp;
}
void Prim(FILE *out, int S) {
	int edge_num = 0, sum = 0;
	int select[10010], visit[10010] = { 0 };
	Graph *temp = graph[S]->next;
	visit[S] = 1;
	while (temp != NULL) Insert(temp->data), temp = temp->next;
	while (edge_num < vertex - 1 && size > 0) {
		Input choose = Dequeue();
		if (visit[choose.u] == 1 && visit[choose.v] == 1) continue; // 둘 다 방문한 노드일 경우
		if (visit[choose.v] != 1) { // v를 방문 안 했으면
			temp = graph[choose.v]->next;
			visit[choose.v] = 1;
			while (temp != NULL) Insert(temp->data), temp = temp->next;
		}
		else { // u를 방문 안 했으면
			temp = graph[choose.u]->next;
			visit[choose.u] = 1;
			while (temp != NULL) Insert(temp->data), temp = temp->next;
		}
		select[edge_num] = choose.num;
		sum += choose.w;
		edge_num++;
	}
	fprintf(out, "Tree edges by Prim algorithm with starting vertex %d: %d\n", S, sum);
	for (int i = 0; i < edge_num; i++) fprintf(out, "%d\n", select[i]);
}

int main() {
	FILE *inp = fopen("mst.inp", "r");
	FILE *out = fopen("mst.out", "w");

	Scan(inp); // input.
	Kruskal(out); // Kruskal.
	Input init;
	init.num = 0, init.u = 0, init.v = 0, init.w = 0;
	Prim(out, 0), size = 0;
	for (int i = 0; i <= edge * 2; i++) heap[i] = init;
	Prim(out, vertex / 2), size = 0;
	for (int i = 0; i <= edge * 2; i++) heap[i] = init;
	Prim(out, vertex - 1); // Prim.

	fclose(inp);
	fclose(out);
	return 0;
}