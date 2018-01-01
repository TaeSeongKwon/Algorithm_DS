#include <cstdio>
#define MAX (1<<10) - 1

long long TC, res, N;
long long getSeperate(long long num, long long bitMask) {
	while (num) {
		bitMask |= (1 << (num % 10));
		num /= 10;
	}
	return bitMask;
}
void init() {
	N = res = 0;
}
void input() {
	scanf("%lld", &N);
}
void result(long long num) {
	long long bitMask = 0;
	res = N;
	bitMask = getSeperate(res, bitMask);
	while (bitMask != MAX) {
		res += N;
		bitMask = getSeperate(res, bitMask);
	}
	printf("#%lld %lld\n", num, res);
}

int main() {
	scanf("%lld", &TC);
	for (long long num = 1; num <= TC; num++) {
		init();
		input();
		result(num);
	}
	return 0;
}