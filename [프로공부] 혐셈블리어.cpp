#include <cstdio>
#define MAX 20
#define YES "YES"
#define NO "NO"
#define QMAX 10000
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

typedef struct Process {
	int i;
	int j;
	int direct;
	int memory;
};

int TC, R, C, qHead, qRear, qCnt;
int direct[4][2] = { {-1, 0}, {1,0}, {0,-1},{0,1} };
bool visit[MAX][MAX][4][16];
char app[MAX][MAX + 1];
Process myQueue[QMAX];

void push(Process proc) {
	if (qCnt == QMAX) return;
	myQueue[qRear++%QMAX] = proc;
	qCnt++;
}
Process poll() {
	if (!qCnt) return { -1,-1,-1,-1 };
	Process tmp = myQueue[(++qHead) % QMAX];
	qCnt--;
	return tmp;

}

bool move(Process& proc) {
	int unitI = direct[proc.direct][0];
	int unitJ = direct[proc.direct][1];
	int nextI = proc.i + unitI;
	int nextJ = proc.j + unitJ;

	if (nextI == R) nextI = 0;
	else if (nextI < 0) nextI = R - 1;

	if (nextJ == C) nextJ = 0;
	else if (nextJ < 0) nextJ = C - 1;

	if (visit[nextI][nextJ][proc.direct][proc.memory]) return false;
	visit[nextI][nextJ][proc.direct][proc.memory] = true;
	proc.i = nextI;
	proc.j = nextJ;
	return true;
}

void operate(char cmd, Process& proc) {
	if (cmd == '_') {
		//메모리에 0이 저장되어 있으면 이동 방향을 오른쪽으로 바꾸고, 아니면 왼쪽으로 바꾼다.
		proc.direct = proc.memory == 0 ? RIGHT : LEFT;
	}else if (cmd == '|'){
		//메모리에 0이 저장되어 있으면 이동 방향을 아래쪽으로 바꾸고, 아니면 위쪽으로 바꾼다.
		proc.direct = proc.memory == 0 ? DOWN : UP;
	}else if (cmd == '+') {
		proc.memory = proc.memory + 1 > 15 ? 0 : proc.memory + 1;
	}else if (cmd == '-') {
		proc.memory = proc.memory - 1 < 0 ? 15 : proc.memory - 1;
	}else if (cmd == '^') {
		proc.direct = UP;
	}else if (cmd == 'v') {
		proc.direct = DOWN;
	}else if (cmd == '<') {
		proc.direct = LEFT;
	}else if (cmd == '>') {
		proc.direct = RIGHT;
	}else {
		proc.memory = cmd - '0';
	}
}


void init() {
	qHead = -1;
	qCnt = qRear = 0;
	R = C = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			app[i][j] = 0;
			for (int k = 0; k < 4; k++) 
				for(int p = 0; p<16; p++)
				visit[i][j][k][p] = false;
		}
	}
}
void input() {
	scanf("%d %d ", &R, &C);
	for (int i = 0; i < R; i++)
		scanf("%s", app[i]);
}
void result(int num) {
	push({ 0,0,RIGHT,0 });
	visit[0][0][RIGHT][0] = true;
	bool flag = false;
	while (qCnt) {
		Process proc = poll();
		Process tmp;
		int i = proc.i;
		int j = proc.j;
		if (app[i][j] == '@') {
			flag = true;
			break;
		}else if (app[i][j] == '.') {
			tmp = proc;
			if (move(tmp)) 
				push(tmp);
		}else if (app[i][j] == '?') {
			for (int k = 0; k < 4; k++) {
				tmp = proc;
				tmp.direct = k;
				if (move(tmp)) 
					push(tmp);
			}
		}else {	// 그외의 명령어 처리
			tmp = proc;
			operate(app[i][j], tmp);
			if (move(tmp)) 
				push(tmp);
		}
	}
	printf("#%d ", num);
	if (flag) printf("%s\n", YES);
	else printf("%s\n", NO);
}

int main() {
	scanf("%d", &TC);
	for (int num = 1; num <= TC; num++) {
		init();
		input();
		result(num);
	}
	return 0;
}