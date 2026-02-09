#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define uint unsigned int
#define ushort unsigned short
#define uc unsigned char

void transpose(ushort* a, ushort* b, size_t n, size_t m) {
	memset(b, 0, m * sizeof(ushort));

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			if ((a[i] >> j) & 1) {
				b[j] |= (1U << i);
			}
		}
	}
}

size_t popcount(uint n) {
	size_t ret = 0;
	
	while (n) {
		ret++;
		n &= n - 1;
	}

	return ret;
}

int cmp_pcnt(const void* a, const void* b) {
	int u = popcount(*(const ushort*)a),
		v = popcount(*(const ushort*)b);
	
	if (u == v) return 0;
	else if (u > v) return -1;
	else return 1;
}

int main() {
	ushort a[16], b[16];
	size_t n, m;
	scanf("%zu%zu", &n, &m);
	for (size_t i = 0; i < n; i++) {
		scanf("%hb", &a[i]);
	}
	printf("\n\n================\n\n");

	/*
	for (size_t i = 0; i < n; i++) {
		printf("%.*hb\n", m, a[i]);
	}
	printf("\n\n================\n\n");
	*/

	transpose(a, b, n, m);

	qsort(b, m, sizeof(ushort), cmp_pcnt);

	transpose(b, a, m, n);

	for (size_t i = 0; i < n; i++) {
		printf("%.*hb\n", m, a[i]);
	}

	return 0;
}
