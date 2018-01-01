#include <cstdio>

typedef struct Node {
	Node* pre;
	Node* next;
	int data;
};

typedef struct List {
	Node* head;
	Node* tail;
	int cnt;
};


Node* createNode(int data) {
	Node* node = new Node;
	node->pre = NULL;
	node->next = NULL;
	node->data = data;
	return node;
}

void initList(List* list) {
	list->tail = NULL;
	list->head = NULL;
	list->cnt = 0;
}

void push(List* list, int data) {
	Node* node = createNode(data);
	if (list->head == NULL)
		list->head = node;
	else {
		list->tail->next = node;
		node->pre = list->tail;
	}
	list->tail = node;
	list->cnt++;
}

void removeNode(Node *node) {
	node->next = NULL;
	node->pre = NULL;
	delete node;
}

void remove(List* list, int data) {
	Node* node = list->head;
	while (node != NULL) {
		if (node->data == data) break;
		node = node->next;
	}
	if (node != NULL) {
		if (node == list->head) {
			list->head = node->next;
			if (list->head != NULL) list->head->pre = NULL;
			if (list->tail == node) list->tail = list->head;
		}else if (node == list->tail) {
			list->tail = node->pre;
			list->tail->next = NULL;
		}else {
			Node* next = node->next;
			Node* pre = node->pre;
			next->pre = pre;
			pre->next = next;
		}
		removeNode(node);
		list->cnt--;
	}
}
Node* getNode(List* list, int idx) {
	Node* node = list->head;
	while (node != NULL && idx-- > 0) {
		node = node->next;
	}
	return node;
}

void printList(List* list) {
	printf("List(%d)\n>> ", list->cnt);
	Node* node = list->head;
	while (node != NULL) printf("%d ", node->data), node = node->next;
	printf("\n>> ");
	node = list->tail;
	while (node != NULL) printf("%d ", node->data), node = node->pre;
	printf("\n");
}

int main() {
	List* list = new List;
	initList(list);
	push(list, 1);
	push(list, 2);
	printList(list);
	remove(list, 1);
	remove(list, 2);
	printList(list);
	push(list, 1);
	push(list, 2);
	push(list, 3);
	push(list, 4);
	push(list, 5);
	printList(list);
	remove(list, 3);
	printList(list);
	remove(list, 1);
	remove(list, 5);
	printList(list);
	return 0;
}
