#include <cstdio>
#define MAX 8
typedef struct Pos {
	int i;
	int j;
};
Pos list[MAX*MAX];
int N, K, TC, resDist, len;
int board[MAX][MAX], direct[4][2] = { {1,0}, {0,1},{-1,0},{0,-1} };	
bool visit[MAX][MAX];

int getMax(int a, int b) { return a < b ? b : a; }

void init() {
	N = K = resDist = len = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			board[i][j] = 0;
			visit[i][j] = false;
		}
	}
}
void input() {
	int myMax = 0;
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);
			myMax = getMax(myMax, board[i][j]);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == myMax) list[len++] = { i, j };
		}
	}
}
void dfs(Pos crrPos, int height, int dist, bool flag) {
	resDist = getMax(resDist, dist);
	int i = crrPos.i, j = crrPos.j;

	visit[i][j] = true;
	for (int k = 0; k < 4; k++) {
		int nextI = i + direct[k][0];
		int nextJ = j + direct[k][1];
		if (nextI < 0 || nextJ < 0 || nextI == N || nextJ == N) continue;
		if (height > board[nextI][nextJ] && !visit[nextI][nextJ]) {
			dfs({ nextI, nextJ }, board[nextI][nextJ], dist + 1, flag);
		}
	}
	if (!flag) {
		for (int k = 0; k < 4; k++) {
			int nextI = i + direct[k][0];
			int nextJ = j + direct[k][1];
			if (nextI < 0 || nextJ < 0 || nextI == N || nextJ == N) continue;
			for (int l = 1; l <= K; l++) {
				if ( height > (board[nextI][nextJ]-l) && !visit[nextI][nextJ]) {
					dfs({ nextI, nextJ }, board[nextI][nextJ]-l, dist + 1, true);
				}
			}
		}
	}
	visit[i][j] = false;
}
void result(int num) {
	for (int i = 0; i < len; i++) {
		dfs(list[i], board[list[i].i][list[i].j], 1, false);
	}
	printf("#%d %d\n", num, resDist);
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
