#include <cstdio>
#define MAX 21
#define LEN 101
#define FLT '.'
#define SWL '*'
#define IWL '#'
#define WAT '-'
#define UP '^'
#define DOWN 'v'
#define LEFT '<'
#define RIGHT '>'
#define S 'S'
#define U 'U'
#define L 'L'
#define R 'R'
#define D 'D'

char map[MAX][MAX], command[LEN];
int TC, W, H, N, tankX, tankY;

bool isMoveable(int x, int y, char (*map)[MAX]) {
	if (y >= H || y < 0 || x < 0 || x >= W) return false;
	if (map[y][x] == FLT) return true;
	return false;
}
void shot(int x, int y, char(*map)[MAX]) {
	int unitX, unitY;
	if (map[y][x] == UP) unitY = -1, unitX = 0;
	else if (map[y][x] == DOWN) unitY = 1, unitX = 0;
	else if (map[y][x] == LEFT) unitY = 0, unitX = -1;
	else if (map[y][x] == RIGHT) unitY = 0, unitX = 1;

	x += unitX;
	y += unitY;
	while (isMoveable(x, y, map) || map[y][x] == WAT) {
		x += unitX;
		y += unitY;
	}
	if (y >= H || y < 0 || x < 0 || x >= W) return;
	if (map[y][x] == SWL) map[y][x] = FLT;
}
void printMap() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}
void init() {
	for (int i = 0; i < LEN; i++) {
		command[i] = 0;
	}
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			map[i][j] = 0;
		}
	}
	N = W = H = 0;
}
void input() {
	scanf("%d %d ", &H, &W);
	for (int i = 0; i < H; i++) {
		scanf("%s", map[i]);
		for (int j = 0; j < W; j++) {
			if (map[i][j] == UP || map[i][j] == DOWN || map[i][j] == LEFT || map[i][j] == RIGHT) {
				tankX = j, tankY = i;
				break;
			}
		}
	}
	scanf("%d ", &N);
	scanf("%s", command);
}
void result(int num) {
	for (int i = 0; i < N; i++) {
		char c = command[i];
		if (c == S) {
			shot(tankX, tankY, map);
		}else if (c == U) {
			if (isMoveable(tankX, tankY - 1, map)) {
				map[tankY][tankX] = FLT;
				tankY--;
			}
			map[tankY][tankX] = UP;
		}else if (c == D) {
			if (isMoveable(tankX, tankY + 1, map)) {
				map[tankY][tankX] = FLT;
				tankY++;
			}
			map[tankY][tankX] = DOWN;
		}else if (c == L) {
			if (isMoveable(tankX-1, tankY, map)) {
				map[tankY][tankX] = FLT;
				tankX--;
			}
			map[tankY][tankX] = LEFT;
		}else if (c == R) {
			if (isMoveable(tankX+1, tankY, map)) {
				map[tankY][tankX] = FLT;
				tankX++;
			}
			map[tankY][tankX] = RIGHT;
		}
	}
	printf("#%d ", num);
	printMap();
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