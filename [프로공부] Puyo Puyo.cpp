#include <cstdio>
#define R 12
#define C 6
#define DIR 4
#define EMP '.'

int TC, res, direct[DIR][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
char map[R][C+1];
bool visit[R][C];

void initVisit() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			visit[i][j] = false;
		}
	}
}
int dfs(int i, int j, char color, int cnt) {
	if (i >= R || j >= C || i < 0 || j < 0) return cnt;
	if (map[i][j] != color) return cnt;
	if (visit[i][j]) return cnt;
	cnt++;
	visit[i][j] = true;
	for (int k = 0; k < DIR; k++) {
		int nextI = i + direct[k][0];
		int nextJ = j + direct[k][1];
		cnt = dfs(nextI, nextJ, color, cnt);
	}
	return cnt;
}
void boom() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (visit[i][j]) map[i][j] = EMP;
		}
	}
}
int check() {
	int cnt = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == EMP) continue;
			initVisit();
			if(dfs(i, j, map[i][j], 0) >= 4) {
				cnt++;
				boom();
			}
		}
	}
	return cnt > 0 ? 1 : 0;
}
bool drop() {
	int flag = false;
	for (int j = 0; j < C; j++) {
		int cnt = 0;
		for (int i = R - 1; i >= 0; i--) {
			if (map[i][j] == EMP) cnt++;
			else if(map[i][j] !=EMP && cnt > 0) {
				map[i + cnt][j] = map[i][j];
				map[i][j] = EMP;
				flag = true;
			}
		}
	}
	return flag;
}

void init() {
	res = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = 0;
		}
	}
}

void input() {
	for (int i = 0; i < R; i++) {
		scanf("%s", &map[i]);
	}
}

void result() {
	do {
		res += check();
	} while (drop());
	printf("%d\n", res);
}

int main() {
	TC = 1;
	for (int num = 1; num <= TC; num++) {
		init();
		input();
		result();
	}
	return 0;
}