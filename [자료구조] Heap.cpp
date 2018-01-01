#include <cstdio>
#define MAX 500000
#define ROOT 0

typedef struct Node {
	int key;
	int data;
};

typedef struct Heap {
	Node tree[MAX];
	int cnt;
};

void initHeap(Heap* q) {
	q->cnt = 0;
}

void push(Heap* q, int key, int data) {
	Node node = { key, data };
	int idx = q->cnt;
	q->tree[idx] = node;

	while (idx != ROOT) {
		int parent = (idx - 1) / 2;
		if (q->tree[idx].key < q->tree[parent].key) {
			Node tmp = q->tree[idx];
			q->tree[idx] = q->tree[parent];
			q->tree[parent] = tmp;
			idx = parent;
		}else break;
	}
	q->cnt++;
}
void downPos(Heap* q, int idx) {
	int leftIdx = idx * 2 + 1;
	int rightIdx = idx * 2 + 2;

	Node node = { 987654321, 0 };
	int compIdx = -1;

	if (leftIdx >= q->cnt) return;
	node = q->tree[leftIdx];
	compIdx = leftIdx;

	if (rightIdx < q->cnt && q->tree[rightIdx].key < node.key) {
		compIdx = rightIdx;
		node = q->tree[rightIdx];
	}

	if (node.key < q->tree[idx].key) {
		Node tmp = q->tree[idx];
		q->tree[idx] = q->tree[compIdx];
		q->tree[compIdx] = tmp;
		downPos(q, compIdx);
	}else return;

}
Node pop(Heap* q) {
	if (q->cnt <= 0) return{ -1, -1 };
	Node node = q->tree[ROOT];
	q->cnt--;
	if (q->cnt > 0) {
		q->tree[ROOT] = q->tree[q->cnt];
		downPos(q, ROOT);
	}
	return node;
}
void printNode(Node node) {
	if (node.key == -1) printf("is null\n");
	else printf("(%d) : %d\n", node.key, node.data);
}
int main() {
	Heap* heap = new Heap;
	initHeap(heap);
	push(heap, 50, 1);
	push(heap, 20, 1);
	push(heap, 80, 1);
	push(heap, 90, 1);
	push(heap, 15, 1);
	push(heap, 10, 1);
	push(heap, 100, 1);
	push(heap, 70, 1);
	push(heap, 60, 1);

	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	printNode(pop(heap));
	return 0;
}