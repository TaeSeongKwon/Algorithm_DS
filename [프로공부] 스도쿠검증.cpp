#include <cstdio>
#define MAX 9
#define TOTAL 45

int TC, board[MAX][MAX];
bool checkSquare() {
	for (int i = 0; i < MAX; i += 3) {
		for (int j = 0; j < MAX; j += 3) {
			int sum = 0;
			for (int k = i; k < i + 3; k++) {
				for (int l = j; l < j + 3; l++) {
					sum += board[k][l];
				}
			}
			if (sum != TOTAL)
				return false;
		}
	}
	return true;
}

bool checkVertical() {
	for (int j = 0; j < MAX; j++) {
		int sum = 0;
		for (int i = 0; i < MAX; i++) sum += board[i][j];
		if (sum != TOTAL) 
			return false;
	}
	return true;
}
bool checkHorizontal() {
	for (int i = 0; i < MAX; i++) {
		int sum = 0;
		for (int j = 0; j < MAX; j++) sum += board[i][j];
		if (sum != TOTAL)
			return false;
	}
	return true;
}
void input() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			scanf("%d", &board[i][j]);
		}
	}
}
void result(int num) {
	printf("#%d %d\n", num, (checkHorizontal() && checkSquare() && checkVertical()));
}
int main() {
	scanf("%d", &TC);
	for (int num = 1; num <= TC; num++) {
		input();
		result(num);
	}
	return 0;
}
