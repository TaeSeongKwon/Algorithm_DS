#include <cstdio>
#define MAX 5000
int TC, piLen, strLen, res, pi[MAX];
char str[MAX + 1], piStr[MAX + 1];
void getPi() {
	int i = 1, j = 0;
	for (; i < piLen; i++) {
		while (j > 0 && piStr[i] != piStr[j]) j = piStr[j - 1];
		if (piStr[i] == piStr[j]) pi[i] = ++j;
	}
}

int kmp(char* S, char* P) {
	int i = 0, j = 0;
	int myCnt = 0;
	for (; i < strLen; i++) {
		while (j > 0 && S[i] != P[j]) j = pi[j - 1];
		if (S[i] == P[j]) {
			if (j + 1 == piLen) {
				myCnt++;
				if (myCnt >= 2) return myCnt;
				j = pi[j];
			}else j++;
		}
	}
	return myCnt;
}
void showPiStr() {
	for (int i = 0; i < piLen; i++) {
		printf("%c", piStr[i]);
	}
	printf("\n");
}
void init() {
	for (int i = 0; i < MAX; i++) pi[i] = str[i] = piStr[i] = 0;
	res = piLen = strLen = 0;
}
void input() {
	scanf("%s", str);
}
void result() {
	for (strLen = 0; str[strLen] != 0; strLen++);
	for (int i = 0; i < strLen; i++) {
		int j;
		for (j = i, piLen = 1; j < strLen; j++, piLen++) {
			piStr[piLen - 1] = str[j];
		}
		getPi();
		int cnt = kmp(str, piStr);
		if (cnt >= 2) {
			res = piLen;
				//showPiStr();
		}
	}
	printf("%d\n", res);
}

int main() {
	TC = 1;
	/*scanf("%d", &TC);*/
	//for (int num = 1; num <= TC; num++) {
		//init();
		input();
		result();
	//}
	return 0;
}