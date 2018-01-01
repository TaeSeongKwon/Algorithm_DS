#include <cstdio>
#define MAX 100000

typedef struct Node {
	int *list;
	int size;
};

int TC, N, M, list[MAX];
Node *segTree[MAX * 4];
Node* createNode(int size) {
	Node* node = new Node();
	if (size == 0) {
		node->size = 0;
		node->list = NULL;
	}else {
		node->size = size;
		node->list = new int[size];
	}
	return node;
}
void merge(Node* A, Node* B, Node* dest) {
	int i = 0, j = 0;
	int cnt = 0;
	while ((A != NULL && B!=NULL) && (i < A->size && j < B->size)) {
		if (A->list[i] < B->list[j]) dest->list[cnt++] = A->list[i++];
		else dest->list[cnt++] = B->list[j++];
	}

	while(A!=NULL && i<A->size) dest->list[cnt++] = A->list[i++];
	while(B!=NULL && j < B->size) dest->list[cnt++] = B->list[j++];

}

Node* initSeg(int left, int right, int node) {
	if (left == right) {
		segTree[node] = createNode(1);
		segTree[node]->list[0] = list[left];
		return segTree[node];
	}
	int mid = (left + right) / 2;
	Node *leftNode = initSeg(left, mid, node * 2 + 1);
	Node *rightNode = initSeg(mid + 1, right, node * 2 + 2);
	segTree[node] = createNode(leftNode->size + rightNode->size);
	merge(leftNode, rightNode, segTree[node]);
	return segTree[node];
}

Node* query(int left, int right, int node, int leftIdx, int rightIdx) {
	if (left > rightIdx || right < leftIdx) {
		return NULL;
	}
	if (left <= leftIdx && rightIdx <= right) {
		return segTree[node];
	}
	int mid = (leftIdx + rightIdx) / 2;
	Node *leftNode = query(left, right, node * 2 + 1, leftIdx, mid);
	Node *rightNode = query(left, right, node * 2 + 2, mid + 1, rightIdx);
	if (leftNode != NULL && rightNode != NULL) {
		Node *mergeNode = createNode(leftNode->size + rightNode->size);
		merge(leftNode, rightNode, mergeNode);
		return mergeNode;
	}else if (leftNode != NULL) return leftNode;
	else if (rightNode != NULL) return rightNode;
	
}
void init() {
	for (int i = 0; i < MAX * 4; i++) {
		segTree[i] = NULL;
	}
	for (int i = 0; i < MAX; i++) list[i] = 0;
	N = M = 0;
}

void input() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) 
		scanf("%d", &list[i]);
}

void result() {
	initSeg(0, N - 1, 0);
	int start, end, k;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &start, &end, &k);
		start--, end--, k--;
		Node* node = query(start, end, 0, 0, N - 1);
		printf("%d\n", node->list[k]);
	}
}

int main() {
	TC = 1;
	for (int num = 1; num <= TC; num++) {
		init();
		input();
		result();
	}
	return 0;
}