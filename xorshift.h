#ifdef XORSHIFT_IMPL

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define uint unsigned int

uint xs;

void init_xorshift(void) {
	xs = 0xDEADBEEF ^ time(NULL);
}

uint xorshift() {
	xs ^= xs << 13;
	xs ^= xs >> 17;
	xs ^= xs << 5;

	return xs;
}

uint xs_rand(int l, int r) {
	int len = r - l;

	return ((xorshift() % len + len) % len) + l;
}

#endif
