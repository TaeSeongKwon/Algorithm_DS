#include <stdio.h>
#include <iostream>
using namespace std;

extern void init(void);

extern void insert(int buffer_size, char *buf);

extern int query(int buffer_size, char *buf);

int main(void) {
	//freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	int TestCase; for (scanf("%d", &TestCase); TestCase--;) {
		int Query_N;
		scanf("%d", &Query_N);

		init();

		static int tc = 0;
		printf("#%d", ++tc);

		for (int i = 1; i <= Query_N; i++) {
			int type; scanf("%d", &type);

			if (type == 1) {
				char buf[15] = { 0, };
				scanf("%s", buf);

				int buffer_size = 0;
				while (buf[buffer_size]) buffer_size++;

				insert(buffer_size, buf);
			}
			else {
				char buf[15] = { 0, };
				scanf("%s", buf);

				int buffer_size = 0;
				while (buf[buffer_size]) buffer_size++;

				printf(" %d", query(buffer_size, buf));
			}
		}
		printf("\n");
	}
}

#define ALPHA 128
#define NULL 0

class Node {
public :
	Node* alpha[ALPHA];
	bool isTerminal;
};
Node *root;

Node* createNode() {
	Node* node = new Node;
	for (int i = 0; i < ALPHA; i++)
		node->alpha[i] = NULL;
	node->isTerminal = false;
	return node;
}
void wordInsert(char* head, int i, int size, Node* node) {
	if (i == size) {
		node->isTerminal = true;
		return;
	}else {
		int idx = (int)(*(head+i));
		
		if (node->alpha[idx] == NULL)
			node->alpha[idx] = createNode();
		wordInsert(head, i+1, size, node->alpha[idx]);
	}
}
Node* getHead(char* head,int i, int size, Node* node) {
	if (i == size) return node;
	int idx = (int)(*(head + i));
	return getHead(head, i+1, size, node->alpha[idx]);
}
int getWordCount(Node* node, int cnt) {
	if (node == NULL) return cnt;
	if (node->isTerminal) 
		cnt++;
	for (int i = 0; i < ALPHA; i++) {
		if (node->alpha[i] != NULL)
			cnt = getWordCount(node->alpha[i], cnt);
	}
	return cnt;
}
void init(void) {
	root = new Node;
	for (int i = 0; i < ALPHA; i++)
		root->alpha[i] = NULL;
	root->isTerminal = false;
}

void insert(int buffer_size, char *buf) {
	wordInsert(buf,0, buffer_size, root);
}

int query(int buffer_size, char *buf) {
	Node* head = getHead(buf, 0, buffer_size, root);
	return getWordCount(head, 0);
}