#define BITSET_IMPL
#include <string.h>
#include "bitset.h"

void test(char* _s, char* _t) {
	Bitset a, b;

	size_t u = strlen(_s), v = strlen(_t);
	size_t n = ((u > v) ? u : v);
	BitsetInit(&a, n);
	BitsetInit(&b, n);

	char* s = _s;
	char* t = _t;

	BitsetSetString(a, strlen(s), s);
	BitsetSetString(b, strlen(t), t);

	int c = BitsetComp(a, b);

	if (c == 0) {
		printf("a == b\n");
	} else if (c == 1) {
		printf("a >= b\n");
	} else if (c == -1) {
		printf("a <= b\n");
	} else {
		printf("a !! b\n");
	}

	printf("%s\n", BitsetGetString(a));
	printf("%s\n", BitsetGetString(b));

	//BitsetXor(a, b);
	//printf("%s\n", BitsetGetString(a));

	BitsetFree(&a);
	BitsetFree(&b);

	for (int i = 0, j = 0; j < 100; i = printf("="), j++) {}
	printf("\n\n\n");
}

int main() {
	test("1000", "1001");
	test("1", "1");
	test("0110", "0100");
	test("1111111111111", "1");
	test("0111111111111", "1");
	
	return 0;
}
