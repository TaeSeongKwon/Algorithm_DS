#include <cstdio>
#define MAX_NAME 20 
#define MAX 200000
#define MAX_TABLE 200003
#define LEFT 0
#define RIGHT 1
#define MAX_ALPHA 52
#define EMP -1

typedef struct node Node;

struct node {
	Node* alpha[MAX_ALPHA];
	int idx;
};

Node trie, store[MAX];
int TC, F, cnt, sizes[MAX], disjoint[MAX];
char list[MAX][2][MAX_NAME + 1];

Node* createNode() {
	return &store[cnt++];
}

int setData(char* name, Node* trie, int *idx) {
	if (*name == NULL) {
		trie->idx = (trie->idx == EMP) ? (*idx)++ : trie->idx;
		return trie->idx;
	}else {
		int index;
		if ('a' <= *name && *name <= 'z') index = *name - 'a';
		else index = *name - 'A' + 26;
		if (trie->alpha[index] == NULL)
			trie->alpha[index] = createNode();
		return setData(name + 1, trie->alpha[index], idx);
	}
}
void initStore() {
	for (int i = 0; i < MAX; i++) {
		store[i].idx = EMP;
		for (int j = 0; j < MAX_ALPHA; j++)
			store[i].alpha[j] = NULL;
	}
}

int getRoot(int node) {
	if (disjoint[node] == node) return node;
	else return getRoot(disjoint[node]);
}
void init() {
	initStore();
	F = 0;
	for (int i = 0; i < MAX_ALPHA; i++)
		trie.alpha[i] = NULL;

	for (int i = 0; i < MAX; i++)
		disjoint[i] = i, sizes[i] = 1;
}
void input() {
	scanf("%d ", &F);
	for (int i = 0; i < F; i++) 
		scanf("%s %s ", list[i][LEFT], list[i][RIGHT]);
}
void result() {
	int idx = 0;
	for (int i = 0; i < F; i++) {
		int left = setData(list[i][LEFT], &trie, &idx);
		int right = setData(list[i][RIGHT], &trie, &idx);
		int leftRoot = getRoot(left);
		int rightRoot = getRoot(right);
		if (leftRoot != rightRoot) {
			disjoint[rightRoot] = leftRoot;
			sizes[leftRoot] += sizes[rightRoot];
		}
		printf("%d\n", sizes[leftRoot]);
	}
}

int main() {
	scanf("%d", &TC);
	for (int num = 1; num <= TC; num++) {
		init();
		input();
		result();
	}
	return 0;
}