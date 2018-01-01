#include <cstdio>
#define MAX 49

int TC, N, board[MAX][MAX], sum = 0;

int getAbs(int a) { return a < 0 ? -a : a; }

void init() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			board[i][j] = 0;
		}
	}
	N = sum = 0;
}

void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1d ", &board[i][j]);
		}
	}
}

void result(int num) {
	int i;
	for (i = 0; i < (N / 2) + 1; i++) {
		int stJ = getAbs((N / 2) - i);
		for (int j = 0; j < (2 * i) + 1; j++) {
			sum += board[i][stJ + j];
		}
	}
	for (; i < N; i++) {
		int stJ = getAbs((N / 2) - i);
		for (int j = 0; j < 2 * (N - i - 1) + 1; j++) {
			sum += board[i][stJ + j];
		}
	}
	printf("#%d %d\n", num, sum);
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