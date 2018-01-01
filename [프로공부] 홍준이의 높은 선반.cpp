#include <cstdio>
#define MAX 10000

int TC, N, B;
int list[MAX], tmp[MAX];

void mergeSort(int st, int ed, int* arr) {
	if (st < ed) {
		int mid = (st + ed) / 2;
		mergeSort(st, mid, arr);
		mergeSort(mid + 1, ed, arr);

		int i = st, j = mid + 1, cnt = 0;
		while (i <= mid && j <= ed) {
			if (arr[i] > arr[j]) tmp[cnt++] = arr[i++];
			else tmp[cnt++] = arr[j++];
		}
		while (i <= mid) tmp[cnt++] = arr[i++];
		while (j <= ed) tmp[cnt++] = arr[j++];
		for (int k = 0, l = st; k < cnt; k++, l++) {
			arr[l] = tmp[k];
		}
	}
}

void init() {
	N = B =  0;
}

void input() {
	scanf("%d %d ", &N, &B);
	for (int i = 0; i < N; i++) scanf("%d", &list[i]);
}

void result(int num) {
	mergeSort(0, N - 1, list);
	int head = 0, rear = 0;
	int sum = 0, mySum = 987654321;
	while (true) {
		if (sum < B) {
			if (rear < N)  sum += list[rear++];
			else break;
		}else {
			mySum = mySum > sum ? sum : mySum;
			sum -= list[head++];
		}
	}
	printf("#%d %d\n", num, mySum - B);
}

int main() {
	scanf("%d ", &TC);
	for (int num = 1; num <= TC; num++) {
		init();
		input();
		result(num);
	}
	return 0;
}