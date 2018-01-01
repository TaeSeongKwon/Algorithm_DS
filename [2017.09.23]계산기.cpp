#include <cstdio>
#define MAX 33
#define NUM 'N'

int TC, N, score;
char op, display[MAX];
void calc(char op, char display[]); // 우리가 구현해야 하는 함수
bool myStrcmp(char strA[], char strB[]) {
	int i = 0, j = 0;
	while (strA[i] != 0 && strB[j] != 0) {
		if (strA[i] != strB[j]) return false;
		i++, j++;
	}
	if (strA[i] == 0 && strB[j] == 0) return true;
	else return false;
}

void calc(char op, char display[]);

int main() {
	scanf("%d", &TC);
	for (int num = 1; num <= TC; num++) {
		scanf("%d ", &N);
		score = 0;
		for (int k = 0; k < N; k++) {
			scanf("%c %s ", &op, display);
			if (op == NUM) {
				char number[MAX], tmp[MAX];
				int i = 0;
				for (; display[i] != 0; i++) {
					tmp[i] = number[i] = display[i];
					tmp[i+1] = number[i + 1] = '\0';
					calc(op, number);
					if (myStrcmp(tmp, number)) 
						score++;
				}
				printf("%s\n", number);
			}
			else {
				char number[MAX];
				calc(op, number);
				if (myStrcmp(number, display)) 
					score++;
				printf("%s\n", number);
			}
		}
		printf("#%d %d\n", num, score);
	}
	return 0;
}

#define ADD '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'
#define CLR 'C'
#define EQU '='

#define A 0
#define B 1

char opCode;
int numStk[2][MAX];
int len[2];

int getNum(char c) { return c - '0'; }
char getChar(int num) { return num + '0';  }

void reverse(int num[], int len) {
	for (int i = 0; i < (len / 2); i++) {
		int tmp = num[i];
		num[i] = num[len - 1 - i];
		num[len - 1 - i] = tmp;
	}
}
void clr(char display[]) {
	display[0] = '0';
	display[1] = '\0';
	opCode = 0;
	len[A] = len[B] = 0;
	for (int i = 0; i < MAX; i++) 
		numStk[A][i] = numStk[B][i] = 0;
}
void copyStr(int num[], int len, char display[]) {
	for (int i = 0; i < len; i++) display[i] = getChar(num[i]);
	display[len] = '\0';
}
void copyArray(int src[], int dest[], int len) {
	for (int i = 0; i < len; i++) dest[i] = src[i];
}
void add(int numA[], int* lenA, int numB[], int* lenB) {
	int i = 0, j = 0;

	while (i < *lenA && j < *lenB) {
		numA[i] += numB[j];
		if (numA[i] >= 10) {
			numA[i + 1] += (numA[i] / 10);
			numA[i] %= 10;
		}
		i++, j++;
	}
	while (j < *lenB) {
		numA[j] += numB[j];
		if (numA[j] >= 10) {
			numA[j + 1] += (numA[j] / 10);
			numA[j] %= 10;
		}
		j++;
	}
	while (i < *lenA) {
		if (numA[i] >= 10) {
			numA[i + 1] += (numA[i] / 10);
			numA[i] %= 10;
		}
		i++;
	}
	for (i = MAX - 1; numA[i] == 0; i--);
	*lenA = i + 1;
}
bool sub(int numA[], int* lenA, int numB[], int* lenB) {
	int i = 0, j = 0;

	if (*lenA < *lenB) return false;

	while (i < *lenA) {
		numA[i] = numA[i] - numB[i];
		if (numA[i] < 0 && i + 1 < *lenA) {
			numA[i] += 10;
			numA[i + 1]--;
		}
		j = numA[i] > 0 ? i : j;
		i++;
	}
	if (numA[(*lenA) - 1] < 0) return false;
	
	*lenA = j + 1;
	
	return true;
}
void div(int numA[], int* lenA, int numB[], int* lenB) {
	
	int cnt = 0;
	while (sub(numA, lenA, numB, lenB)) {
		cnt++;
		//printf("div : %d\n", cnt);
	}

	*lenA = 0;
	for (int i = 0; i < MAX; i++) numA[i] = 0;

	if (cnt == 0) {
		*lenA = 1;
		return;
	}
	while (cnt != 0) {
		numA[(*lenA)++] = (cnt % 10);
		cnt /= 10;
	}
	
}
void mul(int numA[], int* lenA, int numB[], int* lenB) {
	int tmp[MAX] = { 0, };
	int k = 0;
	for (int i = 0; i < *lenB; i++) {
		k = i;
		for (int j = 0; j < *lenA; j++) {
			tmp[k + j] += (numA[j] * numB[i]);
		}
	}
	for (int i = 0; i < MAX; i++) {
		if (tmp[i] >= 10) {
			tmp[i + 1] = (tmp[i] / 10);
			tmp[i] %= 10;
		}
	}
	for (int i = 0; i < MAX; i++) 
		numA[i] = tmp[i];

	int i = 0;
	for (i = MAX - 1; numA[i] == 0; i--);
	*lenA = i + 1;
}
void calc(char op, char display[]) {
	if (op == CLR) clr(display);
	if (op != ADD && op != SUB && op != MUL && op != DIV && op != EQU) {
		// 숫자일 때 
		int idx;
		if (opCode == 0 || opCode == EQU)			
			// 현재 저장된 연산자가 없거나 =일때 숫자는 A에 저장 아니면 B
			idx = A;
		else 
			idx = B;

		len[idx] = 0;
		for (int i = 0; display[i] != 0; i++, len[idx]++)
			numStk[idx][len[idx]] = getNum(display[i]);
		copyStr(numStk[idx], len[idx], display);
	}else {
		// 연산자일 때
		if (opCode == 0 || opCode == EQU) 
			opCode = op;
		else {
			reverse(numStk[A], len[A]), reverse(numStk[B], len[B]);
			if (opCode == ADD) {
				add(numStk[A], &len[A], numStk[B], &len[B]);
			}else if (opCode == SUB) {
				sub(numStk[A], &len[A], numStk[B], &len[B]);
			}else if (opCode == DIV) {
				div(numStk[A], &len[A], numStk[B], &len[B]);
			}else if (opCode == MUL) {
				mul(numStk[A], &len[A], numStk[B], &len[B]);
			}
			opCode = op;
			reverse(numStk[A], len[A]);
		}
		copyStr(numStk[A], len[A], display);
	}
}

//3
//13
//C 0
//N 1000
/// 1000
//N 1000
//= 1
//* 1
//N 9999
//= 9999
//+ 9999
//N 1
//* 10000
//N 54
//= 540000
//5
//C 0
//N 5
/// 5
//N 3
//= 1
//5
//C 0
//N 100000000
/// 100000000
//N 1
//= 100000000