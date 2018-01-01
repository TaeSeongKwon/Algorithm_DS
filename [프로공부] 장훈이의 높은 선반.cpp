#include <cstdio>
#define MAX 20

int TC, N, list[MAX], B;

void input() {
	scanf("%d %d", &N, &B);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
}

void result(int num) {
	int sum = 0;
	int myMin = 987654321;
	for (int i = 1; i < (1 << N); i++) {
		sum = 0;
		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) {
				sum += list[j];
				if (sum >= B && myMin >= sum) break;
				//printf("%d ", list[j]);
			}
		}
		//printf("\n");
		myMin = myMin > sum && sum >= B ? sum : myMin;
	}
	printf("#%d %d\n", num, myMin-B);
}

int main() {
	scanf("%d", &TC);
	for (int num = 1; num <= TC; num++) {
		input();
		result(num);
	}
	return 0;
}