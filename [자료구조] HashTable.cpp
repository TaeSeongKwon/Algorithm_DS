#include <cstdio>
#define MAX 520957
#define MAX_LEN 10

typedef struct Element {
	char key[MAX_LEN+1];
	char data[MAX_LEN+1];
};

typedef struct HashMap {
	Element* table[MAX];
	int cnt;
};
bool strEquals(char *src, char* dest) {
	int len = 0;
	for (; src[len] != 0; len++) {
		if (src[len] != dest[len]) return false;
	} 
	if (src[len] != dest[len]) return false;
	return true;
}
void strCpy(char *src, char* dest) {
	int len = 0;
	for (; src[len] != 0; len++) dest[len] = src[len];
	dest[len] = 0;
} 

Element* createElement(char* key, char* data) {
	Element* element = new Element;
	strCpy(key, element->key);
	strCpy(data, element->data);
	return element;
}
int firstHash(char *key) {
	int sum = 0;
	for (int i = 0; key[i] != 0; i++) sum = (sum << 3) + key[i];
	return sum%MAX;
}
int secondHash(char *key) {
	int sum = 0;
	for (int i = 0; key[i] != 0; i++) sum = (sum << 2) + key[i];
	return sum % (MAX - 2);
}

void initHash(HashMap* map) {
	for (int i = 0; i < MAX; i++) {
		if (map->table[i] != NULL) {
			Element* tmp = map->table[i];
			map->table[i] = NULL;
			delete tmp;
		}
	}
	map->cnt = 0;
}

void set(HashMap* map, char* key, char* data) {
	Element* element = createElement(key, data);
	int address = firstHash(key);
	int unit = secondHash(key);

	while (true) {
		if (map->table[address] == NULL) break;
		address = (address + unit) % MAX;
		printf("set collision\n");
	}

	map->table[address] = element;
	map->cnt++;
}

Element* get(HashMap *map, char* key) {
	int address = firstHash(key);
	int unit = secondHash(key);
	Element* element = NULL;
	while (map->table[address] != NULL) {
		if (strEquals(key, map->table[address]->key)) {
			element = map->table[address];
			break;
		}
		address = (address + unit) % MAX;
		printf("get collision\n");
	}
	return element;
}

void printElement(Element* d) {
	if (d == NULL) printf("is null\n");
	else printf("(%s) : %s\n", d->key, d->data);
}

int main() {
	HashMap* map = new HashMap;
	initHash(map);
	set(map, "Heeee", "hi");
	set(map, "Pukyong", "hi");
	set(map, "National", "hi");
	set(map, "University", "hi");
	set(map, "Samsung", "hi");
	set(map, "Maple", "hi");
	set(map, "STORY", "hi");
	set(map, "Story", "hi");
	printElement(get(map, "Heeee"));
	printElement(get(map, "Samsung"));
	printElement(get(map, "MAPLE"));
	printElement(get(map, "STORY"));
	printElement(get(map, "maple"));
	printElement(get(map, "National"));
	printElement(get(map, "Story"));
	printElement(get(map, "Pukyong"));
	printElement(get(map, "University"));
	printElement(get(map, "xxxxxx"));
	initHash(map);
	set(map, "Heeee", "hi");
	printElement(get(map, "Heeee"));
	return 0;
}