#include <cstdio>
#define MAX 300
#define DIR 8
#define EMP '.'
#define MINE '*'

typedef struct Node {
	int i;
	int j;
};
int TC, N, table[MAX][MAX], len, res;
int direct[DIR][2] = { 
	{0,1},{0,-1},{1,0},{-1,0} ,
	{1,1},{1,-1},{-1,1},{-1,-1}
};
char board[MAX][MAX + 1];
Node list[MAX*MAX];

int getAroundMineCnt(int i, int j) {
	int cnt = 0;
	for (int k = 0; k < DIR; k++) {
		int nextI = i + direct[k][0];
		int nextJ = j + direct[k][1];
		if (nextI < 0 || nextJ < 0 || nextI >= N || nextJ >= N) continue;
		if (board[nextI][nextJ] == MINE) cnt++;
	}
	return cnt;
}
void checkMine(int i, int j) {
	
	if (board[i][j] != EMP) return;		// visited or this location is mine

	board[i][j] = table[i][j] + '0';
	if (table[i][j] == 0) {			// if this location is value 0 count then recusion
		for (int k = 0; k < DIR; k++) {
			int nextI = i + direct[k][0];
			int nextJ = j + direct[k][1];
			if (nextI < 0 || nextJ < 0 || nextI >= N || nextJ >= N) continue;
			checkMine(nextI, nextJ);
		}
	}
}
void init() {
	N = len = res = 0;
}

void input() {
	scanf("%d ", &N);
	for (int i = 0; i < N; i++)
		scanf("%s", board[i]);

}

void result(int num) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == EMP) {
				table[i][j] = getAroundMineCnt(i, j);
				if (table[i][j] == 0) list[len++] = { i , j };
			}
		}
	}
	for (int k = 0; k < len; k++) {
		int i = list[k].i;
		int j = list[k].j;
		if (board[i][j] != EMP) continue;
		res++;
		checkMine(i, j);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != EMP) continue;
			res++;
			checkMine(i, j);
		}
	}
	printf("#%d %d\n", num, res);
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