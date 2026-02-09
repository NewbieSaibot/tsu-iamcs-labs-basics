#include <stdio.h>

#define ull unsigned long long
#define bool _Bool
#define true 1
#define false 0

int comp(ull a, ull b) {
	bool a_le_b = true, b_le_a = true;

	for (int i = 0; i <= 63; i++) {
		if (!(((a >> i) & 1) <= ((b >> i) & 1))) {
			a_le_b = false;
		}
		if (!(((b >> i) & 1) <= ((a >> i) & 1))) {
			b_le_a = false;
		}
	}

	if (a_le_b && b_le_a) {
		return 0;
	} else if (a_le_b) {
		return -1;
	} else if (b_le_a) {
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
	test(0b0100, 0b1011);
	
	return 0;
}
