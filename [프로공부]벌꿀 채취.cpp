#include <cstdio>
#define M_MAX 5
#define N_MAX 10
#define MAX 100000
typedef struct Info {
	int set[M_MAX];
	int i;
	int j;
	int powSum;
	int visit;
};

int honeys[N_MAX][N_MAX];
int TC, N, M, C, len;
bool visit[N_MAX][N_MAX];
Info list[MAX], tmp[MAX];

void merge(int st, int mid, int ed, Info list[]) {
	int i = st, j = mid + 1;
	int cnt = 0;
	while (i <= mid && j <= ed) {
		if (list[i].powSum > list[j].powSum) tmp[cnt++] = list[i++];
		else tmp[cnt++] = list[j++];
	}
	while (i <= mid) tmp[cnt++] = list[i++];
	while (j <= ed) tmp[cnt++] = list[j++];
	for (int k = 0, i = st; k < cnt; k++, i++) list[i] = tmp[k];
}
void mergeSort(int st, int ed, Info list[]) {
	if (st < ed) {
		int mid = (st + ed) / 2;
		mergeSort(st, mid, list);
		mergeSort(mid + 1, ed, list);
		merge(st, mid, ed, list);
	}
}
void init() {
	for (int i = 0; i < N_MAX; i++) {
		for (int j = 0; j < N_MAX; j++) {
			honeys[i][j] = 0;
			visit[i][j] = false;
		}
	}
	len = N = M = C = 0;
}
void input() {
	scanf("%d %d %d", &N, &M, &C);
	for (int i = 0; i < MAX; i++) {
		list[i].i = list[i].j = 0;
		list[i].powSum = list[i].visit = 0;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &honeys[i][j]);
		}
	}
}
void result(int num) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - M + 1; j++,len++) {
			list[len].i = i, list[len].j = j;
			for (int k = 0; k < M; k++) {
				list[len].set[k] = honeys[i][j + k];
			}
		}
	}

	for (int i = 0; i < len; i++) {
		for (int j = 1; j < (1 << M); j++) {
			int visit = 0;
			int sum = 0;
			int powSum = 0;

			for (int k = 0; k < M; k++) {
				if (j&(1 << k)) {
					sum += list[i].set[k];
					powSum += (list[i].set[k] * list[i].set[k]);
					visit |= (1 << k);
					//printf("%d ", list[i].set[k]);
				}
				
			}
			//printf("\n");
			if (sum > C) continue;

			if (list[i].powSum < powSum) {
				list[i].powSum = powSum;
				list[i].visit = visit;
			}
		}
	}
	mergeSort(0, len - 1, list);
	int startI = list[0].i;
	int startJ = list[0].j;
	for (int j = startJ; j < startJ + M; j++) visit[startI][j] = true;
	Info b;
	for (int k = 1; k < len; k++) {
		b = list[k];
		startI = b.i;
		startJ = b.j;
		if (!visit[startI][startJ] && !visit[startI][startJ + M - 1]) 
			break;
	}
	printf("#%d %d\n", num, list[0].powSum + b.powSum);
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