#include <cstdio>
#define MAX 15
int TC, board[MAX][MAX], N, myMax, M;

int getMax(int a, int b) { return a < b ? b : a;  }
int getSum(int i, int j, int M) {
	int sum = 0;
	for (int k = i; k < i + M; k++) {
		for (int l = j; l < j + M; l++) {
			sum += board[k][l];
		}
	}
	return sum;
}
void init() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			board[i][j] = 0;
		}
	}
	N = M = myMax = 0;
}

void input() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);
		}
	}
}

void result(int num) {
	for (int i = 0; i <= N - M; i++) {
		for (int j = 0; j <= N - M; j++) {
			myMax = getMax(myMax, getSum(i, j, M));
		}
	}
	printf("#%d %d\n", num, myMax);
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