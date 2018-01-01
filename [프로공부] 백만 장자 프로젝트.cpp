#include <cstdio>
#define MAX 1000000

typedef struct Node {
	int idx;
	long long price;
};

long long TC, N, list[MAX], end, segTree[MAX*4];
Node info[MAX], tmp[MAX];
void merge(int st, int mid, int ed, Node* info) {
	int i = st, j = mid + 1;
	int cnt = 0;
	while (i <= mid && j <= ed) {
		if (info[i].price > info[j].price) tmp[cnt++] = info[i++];
		else tmp[cnt++] = info[j++];
	}
	while (i <= mid) tmp[cnt++] = info[i++];
	while (j <= ed) tmp[cnt++] = info[j++];
	for (int k = 0, l = st; k < cnt; k++, l++)
		info[l] = tmp[k];
}
void mergeSort(int st, int ed, Node* info) {
	if (st < ed) {
		int mid = (st + ed) / 2;
		mergeSort(st, mid, info);
		mergeSort(mid + 1, ed, info);
		merge(st, mid, ed, info);
	}
}

long long initSeg(int left, int right, int node) {
	if (left == right) return segTree[node] = list[left];
	int mid = (left + right) / 2;
	long long leftSum = initSeg(left, mid, node * 2);
	long long rightSum = initSeg(mid + 1, right, node * 2 + 1);
	return segTree[node] = leftSum + rightSum;
}

long long getQuery(int left, int right, int node, int leftNode, int rightNode) {
	if (rightNode < left || right < leftNode) return 0;
	if (left <= leftNode && rightNode <= right) return segTree[node];
	int mid = (leftNode + rightNode) / 2;
	return getQuery(left, right, node * 2, leftNode, mid) + getQuery(left, right, node * 2 + 1, mid + 1, rightNode);
}

void init() {
	for (int i = 0; i < MAX; i++)
		list[i] = 0, info[i] = { 0,0 };
	for (int i = 0; i < MAX * 4; i++) 
		segTree[i] = 0;
	end = N = 0;
}

void input() {
	scanf("%lld", &N);
	for (long long i = 0; i < N; i++)
		scanf("%lld", &list[i]), info[i] = { (int)i, list[i] };
}

void result(long long num) {
	initSeg(0, (int)(N - 1), 1);
	mergeSort(0, (int)(N - 1), info);
	long long st = 0, ed = -1;
	long long res = 0;
	for (long long i = 0; i < N; i++) {
		Node node = info[i];
		if (end > node.idx) continue;
		st = ed + 1, ed = node.idx;
		end = node.idx;
		long long sum = getQuery(st, ed-1, 1, 0, (int)(N - 1));
		if (sum == 0) continue;
		long long gap = (ed-1) - st + 1;
		res += ((gap * node.price) - sum);
	}
	printf("#%lld %lld\n",num, res);
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