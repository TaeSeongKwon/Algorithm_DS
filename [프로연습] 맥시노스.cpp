#include <cstdio>

#define MAX 12
#define CORE 1
#define EMPTY 0
#define CABLE 2
#define INF 987654321

typedef struct Core {
	int i;
	int j;
};
typedef struct Result {
	int core;
	int cable;
};

int TC, N, cell[MAX][MAX], len;

Core list[MAX];
Result res;

Result comp(Result A, Result B) {
	if (A.core > B.core) return A;
	else if (A.core == B.core && A.cable < B.cable) return A;
	else return B;
}
bool checkHeight(int start, int end, int staticJ, int add) {
	while (start != end) {
		if (cell[start][staticJ] != EMPTY) return false;
		start += add;
	}
	return true;
}
bool checkWidth(int start, int end, int staticI, int add) {
	while (start != end) {
		if (cell[staticI][start] != EMPTY) return false;
		start += add;
	}
	return true;
}

int markHeight(int start, int end, int staticJ, int add, int type) {
	int cnt = 0;
	while (start != end) {
		cell[start][staticJ] = type;
		cnt++;
		start += add;
	}
	return cnt;
}
int markWidth(int start, int end, int staticI, int add, int type) {
	int cnt = 0;
	while (start != end) {
		cell[staticI][start] = type;
		cnt++;
		start += add;
	}
	return cnt;
}
void init() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			cell[i][j] = EMPTY;
		}
	}
	len = N = 0;
	res = { 0, INF };
}

void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &cell[i][j]);
			if (cell[i][j] == CORE) list[len++] = { i, j };
		}
	}
}
void dfs(int idx, int len, Result tmp) {
	if (idx == len) {
		res = comp(res, tmp);
		return;
	}
	int i = list[idx].i;
	int j = list[idx].j;

	if (i == N - 1 || j == N - 1 || i == 0 || j == 0) {
		tmp.core++;
		dfs(idx + 1, len, tmp);
	}else {
		dfs(idx + 1, len, tmp);
		int start = i + 1, end = N, stNum = j, add = 1;
		int core = 0, cable = 0;
		if (checkHeight(start, end, stNum, add)) {
			cable = tmp.cable + markHeight(start, end, stNum, add, CABLE);
			core = tmp.core + 1;
			dfs(idx + 1, len, { core, cable });
			markHeight(start, end, stNum, add, EMPTY);
		}
		start = i - 1, end = -1, stNum = j, add = -1;
		if (checkHeight(start, end, stNum, add)) {
			cable = tmp.cable + markHeight(start, end, stNum, add, CABLE);
			core = tmp.core + 1;
			dfs(idx + 1, len, { core, cable });
			markHeight(start, end, stNum, add, EMPTY);
		}
		
		start = j + 1, end = N, stNum = i, add = 1;
		if (checkWidth(start, end, stNum, add)) {
			cable = tmp.cable + markWidth(start, end, stNum, add, CABLE);
			core = tmp.core + 1;
			dfs(idx + 1, len, { core, cable });
			markWidth(start, end, stNum, add, EMPTY);
		}

		start = j - 1, end = -1, stNum = i, add = -1;
		if (checkWidth(start, end, stNum, add)) {
			cable = tmp.cable + markWidth(start, end, stNum, add, CABLE);
			core = tmp.core + 1;
			dfs(idx + 1, len, { core, cable });
			markWidth(start, end, stNum, add, EMPTY);
		}
	}
}
void result(int num) {
	dfs(0, len, {0, 0});
	printf("#%d %d\n", num, res.cable);
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

