#include <cstdio>
#define CAT 101
#define MAX 20

int TC, N, res;
int desert[MAX][MAX];

int getMax(int a, int b) { return a < b ? b : a; }

void copyVisit(bool* src, bool* dest) {
	for (int i = 0; i < CAT; i++) dest[i] = src[i];
}
void move1(int i, int j, int W, int H);
void move2(int i, int j, int W, int H, bool *visit);
void move3(int i, int j, int W, int H, bool *visit);
void move4(int i, int j, int W, int H, bool *visit);

void move1(int i, int j, int W, int H) {
	bool visit[CAT] = { false, };
	int cat = desert[i][j];
	visit[cat] = true;
	int nextI = i + 1;
	int nextJ = j + 1;
	W++;
	while (nextI < N && nextJ < N) {
		int idx = desert[nextI][nextJ];
		if (visit[idx]) break;
		visit[idx] = true;
		move2(nextI, nextJ, W, H, visit);
		nextI++, nextJ++, W++;
	}
}

void move2(int i, int j, int W, int H, bool *visit) {
	bool visit2[CAT] = { false, };
	copyVisit(visit, visit2);
	int nextI = i;
	int nextJ = j;

	while (true) {
		nextI++, nextJ--; H++;
		if (nextI >= N || nextJ < 0)  break;

		int idx = desert[nextI][nextJ];
		if (visit2[idx]) break;
		visit2[idx] = true;
		move3(nextI, nextJ, W, H,visit2);
	}
}

void move3(int i, int j, int W, int H, bool *visit) {
	bool visit2[CAT] = { false, };
	copyVisit(visit, visit2);
	int nextI = i - 1, nextJ = j - 1;
	int cnt = 2;
	for (; cnt <= W && (nextI >=0 && nextJ>=0); cnt++) {
		int cat = desert[nextI][nextJ];
		if (visit2[cat]) break;
		visit2[cat] = true;
		nextI--, nextJ--;
	}

	if (cnt-1 == W) move4(i- W + 1, j - W + 1, W, H, visit2);
}
void move4(int i, int j, int W, int H, bool *visit) {
	bool visit2[CAT] = { false, };
	copyVisit(visit, visit2);

	int nextI = i - 1, nextJ = j + 1;
	int cnt = 3;

	for (; cnt <= H && (nextI >= 0 && nextJ < N); cnt++) {
		int cat = desert[nextI][nextJ];
		if (visit2[cat]) break;
		visit2[cat] = true;
		nextI--, nextJ++;
	}
	if (cnt - 1 == H) res = getMax(res, (H+W-1) *2 - 2);
}

void init() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			desert[i][j] = 0;
		}
	}
	N = 0;
	res = -1;
}
void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &desert[i][j]);
		}
	}
}
void result(int num) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			move1(i, j, 1, 1);
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