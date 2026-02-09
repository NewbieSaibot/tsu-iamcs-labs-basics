#include <stdio.h>

#define ull unsigned long long
#define bool _Bool //why include stdbool.h?
#define true 1
#define false 0

int comp(ull a, ull b) {
	ull a1_b0 = a & ~b;
	ull b1_a0 = b & ~a;

	if (!a1_b0 && !b1_a0) {
		return 0;
	} else if (!a1_b0) {
		return -1;
	} else if (!b1_a0) {
		return 1;
	} else {
		return 2;
	}
}

void test(ull a, ull b) {
	printf("%#llb\n", a);
	printf("%#llb\n", b);

	if (comp(a, b) == 0) {
		printf("a == b\n");
	} else if (comp(a, b) == 1) {
		printf("a >= b\n");
	} else if (comp(a, b) == -1) {
		printf("a <= b\n");
	} else {
		printf("a !! b\n");
	}
}

int main() {
	test(0b1000, 0b1001);
	test(0b1, 0b1);
	test(0b0110, 0b0100);
	test(0b0110, 0b0100);
	test(0b1000, 0b1111);
	test(0b0001, 0b1111);
	test(0b10100, 0b11011);
	
	return 0;
}
