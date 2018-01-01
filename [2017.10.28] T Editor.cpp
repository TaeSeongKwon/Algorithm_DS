#include <cstdio>
#include <cstring>

#define CMD_INPUT 2
#define CMD_SUB 9
#define CMD_REVERT 1
#define CMD_MOVE 0
#define MAX 26
int TC, N, type;
void init();
void cmd_input(char *str);
void cmd_movecursor(int pos);
void cmd_revert();
void get_substring(int st, int len, char* str);

int main() {
	scanf("%d", &TC);
	int sum = 0;
	for (int num = 1; num <= TC; num++) {
		init();
		int score = 100;
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d ", &type);
			
			if (type == CMD_INPUT) {
				char str[MAX];
				scanf("%s", str);
				cmd_input(str);
			}else if (type == CMD_MOVE) {
				int pos;
				scanf("%d", &pos);
				cmd_movecursor(pos);
			}else if (type == CMD_REVERT) {
				cmd_revert();
			}else if (type == CMD_SUB) {
				int st, len;
				char ori[MAX], res[MAX];
				scanf("%d %d %s", &st, &len, &ori);
				get_substring(st, len, res);
				if (strcmp(ori, res) != 0) {
					score = 0;
				}
			}
		}
		sum += score;
		printf("#%d %d\n", num, score);
	}
	printf("total : %d\n", (sum / TC));
	return 0;
}

class Node {
public :
	char c;
	Node* next;
	Node* pre;
};
class Text {
public :
	Node* head;
};
#define NULL 0

Text text;
bool isRevert;
Node *cursor, *newCursor, *st, *ed;

Node* createNode(char c) {
	Node* node = new Node();
	node->c = c;
	node->next = NULL;
	node->pre = NULL;
	return node;
}
void initText() {
	text.head = new Node();
	text.head->next = NULL;
	text.head->pre = NULL;
	
}
Node* insertText(char *str) {
	Node* element;
	for (int i = 0; str[i] != 0; i++) {
		element = createNode(str[i]);
		element->next = cursor->next;
		element->pre = cursor;
		if (cursor->next != NULL) {
			cursor->next->pre = element;
		}
		cursor->next = element;
		cursor = element;
	}
	return element;
}

void moveCursor(int pos) {
	Node *node = text.head;
	Node *pre = text.head;
	for (int i = 0; i < pos; i++) {
		if (node == NULL) break;
		pre = node;
		node = node->next;
	}
	if (node == NULL) {
		newCursor = pre;
	}else {
		newCursor = node;
	}
}

void init() {
	initText();
	cursor = text.head;
	newCursor = NULL;
	isRevert = false;
}

void cmd_input(char *str) {
	bool isNew = false;
	if (newCursor != cursor) {
		isNew = true;
		if (newCursor == NULL) {
			st = cursor;
		}else {
			st = newCursor;
			cursor = newCursor;
		}
		isRevert = false;
	}
	ed = insertText(str);
	if (isNew) {
		st = st->next;
	}
	newCursor = cursor;
}
void cmd_movecursor(int pos) {
	moveCursor(pos);
}
void cmd_revert() {
	Node *pre = st->pre;
	Node *next = ed->next;
	if (!isRevert) {
		pre->next = next;
		if (next != NULL) 
			next->pre = pre;
		isRevert = true;

		newCursor = st->pre;

	}else {
		pre->next = st;
		if (next != NULL)
			next->pre = ed;
		isRevert = false;
		newCursor = ed;
	}
	printf("REVERT : ");
	Node *node = text.head->next;
	while (node != NULL) {
		printf("%c", node->c);
		node = node->next;
	}
	printf("\n");
}
void get_substring(int st, int len, char* str) {
	Node *node = text.head;
	int idx = 0;
	for (int i = 0; i < st; i++) {
		if (node == NULL) break;
		node = node->next;
	}
	for (int i = 0; i < len; i++) {
		if (node == NULL) break;
		str[idx++] = node->c;
		node = node->next;
	}
	str[idx] = '\0';
}