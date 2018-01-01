#include <cstdio>
#define MAX_SIZE 1000000

typedef struct node Node;
typedef struct list List;

struct node {
	Node* pre;
	Node* next;
	int data;
};

struct list {
	Node* head;
	Node* tail;
	int size;
};

Node store[MAX_SIZE], *gc[MAX_SIZE];
int stRear, gcTop;
List list = { NULL, NULL, 0 };

void initStore() {
	for (int i = 0; i < MAX_SIZE; i++) {
		store[i].next = store[i].pre = NULL;
		store[i].data = 0;
	}
	stRear = gcTop = 0;
}

void initList(List* list) {
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

void removeNode(Node* node) {
	node->next = node->pre = NULL;
	gc[gcTop++] = node;
}

Node* createNode(int data) {
	Node* node = NULL;
	if (gcTop == 0)
		node = &store[stRear++];
	else
		node = gc[--gcTop];

	node->pre = node->next = NULL;
	node->data = data;

	return node;
}
void push(List* list, Node* node) {
	if (list->head == NULL) list->head = node;
	else {
		node->pre = list->tail;
		list->tail->next = node;
	}
	list->tail = node;
	list->size++;
}

void poll(List* list, Node* node) {
	if (list->head == node) {
		list->head = node->next;
		if (list->head != NULL)
			list->head->pre = NULL;
		if (list->tail == node)
			list->tail = list->head;
	}else if (list->tail == node) {
		list->tail = node->pre;
		list->tail->next = NULL;
	}else {
		Node* pre = node->pre;
		Node* next = node->next;
		pre->next = next;
		next->pre = pre;
	}
	removeNode(node);
	list->size--;
}

void showList(List* list) {
	Node* node = list->head;
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
	node = list->tail;
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->pre;
	}
	printf("\n");
}

int main() {
	initStore();
	initList(&list);
	Node* node1 = createNode(1);
	Node* node2 = createNode(2);
	Node* node3 = createNode(3);
	Node* node4 = createNode(4);
	Node* node5 = createNode(5);

	push(&list, node1);
	push(&list, node2);
	push(&list, node3);
	push(&list, node4);
	push(&list, node5);

	showList(&list);
	poll(&list, node1);
	poll(&list, node5);
	showList(&list);
	poll(&list, node4);
	showList(&list);
	poll(&list, node3);
	poll(&list, node2);
	
	showList(&list);
	
	return 0;
}