#include <cstdio>
#define MAX 1000000
#define CHANGE 1
#define SUM 2

long long arr[MAX+1], tree[MAX * 4+4];
int N, K, M, TC;

long long initTree(int node, int left, int right) {
	if (left == right) return tree[node] = arr[left];
	int mid = (left + right) / 2;
	long long leftSum = initTree(node * 2, left, mid);
	long long rightSum = initTree(node * 2 + 1, mid + 1, right);
	return tree[node] = leftSum + rightSum;
}
long long query(int start, int end, int node, int leftNode, int rightNode) {
	if (end < leftNode || rightNode < start) return (long long)0;
	if (start <= leftNode && rightNode <= end) return tree[node];
	int mid = (leftNode + rightNode) / 2;
	return query(start, end, node * 2, leftNode, mid) + query(start, end, node * 2 + 1, mid + 1, rightNode);
}
long long update(int index, long long num, int node, int left, int right) {
	if (left > index || right < index) return tree[node];
	if (left == right) return tree[node] = num;
	int mid = (left + right) / 2;
	return tree[node] = update(index, num, node * 2, left, mid) + update(index, num, node * 2 + 1, mid + 1, right);

}
void init() {
	for (int i = 0; i <= MAX; i++) arr[i] = (long long)0;
	for (int i = 0; i < MAX * 4 + 4; i++) tree[i] = (long long)0;
	N = K = M = 0;
}

void input() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &arr[i]);
}

void result() {
	initTree(1, 1, N);
	int type, b, c;
	for (int i = 0; i < M+K; i++) {
		scanf("%d %d %d", &type, &b, &c);
		if (type == CHANGE) {
			update(b, (long long)c, 1, 1, N);
		}else if (type == SUM) {
			printf("%lld\n", query(b, c, 1, 1, N));
		}
	}
}

int main() {
	TC = 1;
	for (int num = 1; num <= TC; num++) {
		init();
		input();
		result();
	}
	return 0;
}


