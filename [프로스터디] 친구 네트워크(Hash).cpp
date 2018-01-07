#include <cstdio>
#define MAX 100007
#define MAX_TABLE 100007
#define MAX_NAME 20
#define L 0
#define R 1

typedef struct node Node;
typedef struct list List;
typedef struct element Element;

struct node {
	char* name;
	int idx;
	Node* next;
};

struct list {
	Node* head;
	Node* tail;
	int size;
};

struct element {
	int parent;
	int size;
};

int TC, F, cnt;
char names[MAX][2][MAX_NAME + 1];
Node store[MAX];
List table[MAX_TABLE];
Element set[MAX];

Node* createNode(char* name, int* idx) {
	Node* node = &store[cnt++];
	node->name = name;
	node->idx = (*idx)++;
	node->next = NULL;
	return node;
}
bool myStrCmp(char* a, char* b) {
	int i = 0;
	while (a[i] != NULL && b[i] != NULL) {
		if (a[i] != b[i]) return false;
		i++;
	}
	return a[i] == b[i];
}
int getRoot(int node) {
	if (set[node].parent == node) return node;
	return getRoot(set[node].parent);
}

int getHash(char* name) {
	int address = 0;
	for (int i = 0; name[i]; i++) {
		address = ((address * 107) + (int)name[i]) % MAX_TABLE;
	}
	return address;
}

void initStore() {
	for (int i = 0; i < MAX; i++)
		store[i] = { NULL, 0, NULL };
	cnt = 0;
}
void initTable() {
	for (int i = 0; i < MAX_TABLE; i++)
		table[i] = { NULL, NULL, 0 };
}
void initSet() {
	for (int i = 0; i < MAX; i++) {
		set[i] = { i, 1 };
	}
}
void push(List *list, Node* node) {
	if (list->head == NULL)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->size++;
}

int setData(List *table, char* name, int* idx) {
	int address = getHash(name);
	Node* node;
	node = table[address].head;
	while (node != NULL) {
		if (myStrCmp(name, node->name)) {
			break;
		}
		node = node->next;
	}
	if (node == NULL) {
		node = createNode(name, idx);
		push(&table[address], node);
	}
	return node->idx;
}

void init() {
	initStore();
	initTable();
	initSet();
}

void result() {
	int idx = 0;
	scanf("%d ", &F);
	for (int i = 0; i < F; i++) {
		scanf("%s %s ", &names[i][L], &names[i][R]);
		int left = setData(table, names[i][L], &idx);
		int right = setData(table, names[i][R], &idx);
		int leftRoot = getRoot(set[left].parent);
		int rightRoot = getRoot(set[right].parent);
		if (leftRoot != rightRoot) {
			set[rightRoot].parent = leftRoot;
			set[leftRoot].size += set[rightRoot].size;
		}
		printf("%d\n", set[leftRoot].size);
	}
}

int main() {
	scanf("%d ", &TC);
	for (int num = 1; num <= TC; num++) {
		init();
		result();
	}
	return 0;
}

