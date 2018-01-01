#include <cstdio>
#define MAX 200001

int TC, L, PI[MAX];
char str[MAX];

void init() {
	for (int i = 0; i < MAX; i++) {
		PI[i] = 0;
	}
	L = 0;
}

void input() {
	scanf("%d %s", &L, str);
}

void result(int num) {
	int i = 1, matched = 0;
	while (i + matched < L) {
		if (str[i + matched] == str[matched]) {
			matched++;
			PI[ i+matched - 1] = matched;
		}else {
			if (matched == 0) i++;
			else {
				i += matched - PI[matched - 1];
				matched = PI[matched - 1];
			}
		}
	}
	int myMax = 0;
	for (int i = 0; i < L; i++) {
		myMax = myMax < PI[i] ? PI[i] : myMax;
	}
	printf("#%d %d\n",num, myMax);
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