#include <cstdio>

class Node {
public :
	Node* next;
	int data;
};

class List {
public :
	Node* head;
	Node* tail;
	int size;
};

List list;

void initList() {
	list.head = NULL;
	list.tail = NULL;
	list.size = 0;
}
Node* createNode(int data) {
	Node* node = new Node();
	node->data = data;
	node->next = NULL;
	return node;
}

void append(int data) {
	Node* node = createNode(data);
	if (list.head == NULL) {
		list.head = node;
	}else {
		list.tail->next = node;
	}
	list.tail = node;
	list.size++;
}
void deleteNode(Node* node) {
	delete node;
}
void removeNode(int data) {
	Node* node = list.head;
	Node* pre = NULL;
	while (node != NULL) {
		if (node->data == data) break;
		pre = node;
		node = node->next;
	}
	if (node != NULL) {
		if (node == list.head) {
			list.head = node->next;
		}else if (node == list.tail) {
			list.tail = pre;
			list.tail->next = NULL;
		}else {
			pre->next = node->next;	
		}
		node->next = NULL;
		deleteNode(node);
		list.size--;
	}
}

void printList() {
	Node *node = list.head;
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}

int main() {
	initList();
	append(1);
	append(2);
	append(3);
	append(4);
	append(5);
	append(6);
	append(7);
	printList();
	removeNode(7);
	printList();
	removeNode(1);
	printList();
	removeNode(3);
	printList();
	removeNode(4);
	removeNode(5);
	printList();
	removeNode(6);
	printList();
	append(7);
	printList();
	removeNode(2);
	append(4);
	printList();
	removeNode(7);
	removeNode(4);
	printList();
	return 0;
}