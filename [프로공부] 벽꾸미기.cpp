#include <cstdio>
#define INF 987654321
long long TC, A, B, N, myMin;
long long getAbs(long long a) { return a < 0 ? -a : a; }

long long getMin(long long a, long long b) {
	return a < b ? a : b;
}
long long calc(long long N, long long A, long long B, long long R, long long C) {
	return A * getAbs(R - C) + B * (N - R * C);
}
void init() {
	myMin = INF;
	N = A = B = 0;
}
void input() {
	scanf("%lld %lld %lld", &N, &A, &B);
}
void result(long long num) {
	long long res = 1, R = 0, C = 0;
	while (res >= 0) {
		res = calc(N, A, B, R, R);
		if (res >= 0) myMin = getMin(res, myMin);
		R++;
	} 
	
	printf("#%lld %lld\n", num, myMin);
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