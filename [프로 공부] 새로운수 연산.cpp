#include <cstdio>
#define MAX 50000
#define LEN 1000
typedef struct Point {
	int x;
	int y;
};

int TC, P, Q, board[LEN + 1][LEN + 1];
Point list[MAX + 1];

void firstInit() {
	int x = 1, y = 1, base = 0;
	board[1][0] = 1;
	while (board[x][y - 1] + (y - 1) <= MAX && (y < LEN)) {
		board[x][y] = board[x][y - 1] + (y - 1);
		//printf("(%d, %d) : %d\n", x, y, board[x][y]);
		list[board[x][y]] = { x, y };
		base = y + 1;
		x++;
		
		while (board[x-1][y] + base <= MAX && (x < LEN)) {
			board[x][y] = board[x - 1][y] + base;
			list[board[x][y]] = { x, y };
			//printf("(%d, %d) : %d\n", x, y, board[x][y]);
			base++, x++;
		}
		//printf("\n");
		y++;
		x = 1;
	}
	/*for (int i = 1; i <= MAX; i++) {
		printf("(%d, %d)  = %d\n", list[i].x, list[i].y, i);
	}*/
}
void init() {
	P = Q = 0;
}

void input() {
	scanf("%d %d", &P, &Q);
}
void result(int num) {
	Point p, q;
	p = list[P], q = list[Q];
	int x = p.x + q.x;
	int y = p.y + q.y;
	printf("#%d %d\n", num, board[x][y]);
}

int main() {
	firstInit();
	scanf("%d", &TC);
	for (int num = 1; num <= TC; num++) {
		init();
		input();
		result(num);
	}
	return 0;
}
