#include <cstdio>
#define MAX 1000
#define QMAX (MAX * MAX)
#define EMP 0
#define DIR 8
typedef struct Node {
	int i;
	int j;
};
int TC, H, W, cycle, qHead, qRear, qCnt, len;
int board[MAX][MAX], waves[MAX][MAX], direct[DIR][2] = {
	{1,0},{-1,0},{0,1}, {0,-1},
	{1,1},{1,-1},{-1,-1},{-1,1}
};
Node myQueue[QMAX], list[QMAX];

void push(Node node) {
	if (qCnt == QMAX) return;
	myQueue[qRear++ % QMAX] = node;
	qCnt++;
}
Node poll() {
	Node node = myQueue[++qHead%QMAX];
	qCnt--;
	return node;
}
void attackWave() {
	for (int i = 0; i < qCnt; i++) {
		Node node = myQueue[i];
		int cnt = 0;
		for (int k = 0; k < DIR; k++) {
			int nextI = node.i + direct[k][0];
			int nextJ = node.j + direct[k][1];
			cnt += (board[nextI][nextJ] == EMP);
		}
		waves[node.i][node.j] = cnt;
	}
}
int attack() {
	int myCnt = qCnt;
	len = 0;
	while (myCnt--) {
		Node node = poll();
		if (waves[node.i][node.j] >= board[node.i][node.j]) {
			board[node.i][node.j] = 0;
			list[len++] = node;
		}else {
			push(node);
		}
	}
	return len;
}
void update() {
	for (int i = 0; i < len; i++) {
		Node node = list[i];
		for (int k = 0; k < DIR; k++) {
			int nextI = node.i + direct[k][0];
			int nextJ = node.j + direct[k][1];
			waves[nextI][nextJ]++;
		}
	}
}
void init() {
	qHead = -1;
	len = qRear = qCnt = H = W = cycle = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			waves[i][j] = 0;
		}
	}
}

void input() {
	char str[MAX + 1];
	scanf("%d %d ", &H, &W);
	for (int i = 0; i < H; i++) {
		scanf("%s", str);
		for (int j = 0; j < W; j++) {
			if (str[j] == '.') board[i][j] = 0;
			else board[i][j] = str[j] - '0';
			if (board[i][j] == 0) continue;
			Node node;
			node.i = i, node.j = j;
			push(node);
		}
	}
}
void result(int num) {
	attackWave();
	while (true) {
		if (attack() == 0) break;
		update();
		cycle++;
	//	printf("%d\n", cycle);
	}
	printf("#%d %d\n", num, cycle);
}

int main() {
	scanf("%d ", &TC);
	for (int num = 1; num <= TC; num++) {
		init();
		input();
		result(num);
	}
	return 0;
}

