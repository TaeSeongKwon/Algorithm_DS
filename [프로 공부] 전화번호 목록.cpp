#include <cstdio>
#define MAX 10
#define YES "YES"
#define NO "NO"

typedef struct Node {
	bool isTerminal;
	Node *check[MAX];
};

Node tree;

int TC, N;
char str[10000][MAX + 1];
int getIdx(char c) {return c - '0';}

void init() {
	for (int i = 0; i < MAX; i++) {
		if (tree.check[i] != NULL) delete tree.check[i];
		tree.check[i] = NULL;
	}
	tree.isTerminal = false;
	N = 0;
}
void insert(char *numbers, Node* node) {
	//if (node->isTerminal) return false;
	int idx = getIdx(*numbers);
	if (node->check[idx] == NULL) {
		node->check[idx] = new Node();
	}
	if (*(numbers + 1) == 0) {
		node->check[idx]->isTerminal = true;
		//return true;
	}else {
		//return 
		insert(numbers + 1, node->check[idx]);
	}
}
bool check(char *key, Node* tree) {
	if (tree->isTerminal) return false;
	if (*(key + 1) == 0) return true;
	int idx = getIdx(*key);
	return check(key + 1, tree->check[idx]);
}
void result() {
	scanf("%d ", &N);
	bool flag = true;
	for (int i = 0; i < N; i++) {
		scanf("%s", str[i]);
		insert(str[i], &tree);
	}
	for (int i = 0; i < N; i++) {
		if (!check(str[i], &tree)) {
			flag = false;
			break;
		}
	}
	printf("%s\n", (flag ? YES : NO));
}

int main() {
	scanf("%d", &TC);
	for (int num = 1; num <= TC; num++) {
		init();
		result();
	}
	return 0;
}