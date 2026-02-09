#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ushort unsigned short

int cmp_pcnt(ushort *a, int n, int i, int j) {
	size_t u = 0, v = 0;

	for (size_t k = 0; k < n; k++) {
		u += (a[k] >> i) & 1;
		v += (a[k] >> j) & 1;
	}

	if (u == v) return 0;
	else if (u > v) return 1;
	else return -1;
}

void swap_col(ushort* a, int n, int i, int j) {
	for (size_t k = 0; k < n; k++) {
		bool u = ((a[k] >> i) & 1) ^ ((a[k] >> j) & 1);
		a[k] ^= (u << i);
		a[k] ^= (u << j);
	}
}

void bubble_sort(ushort* a, size_t n, size_t m) {
	for (size_t i = 0; i < m; i++) {
		bool swapped = false;
		for (size_t j = 0; j < m - i - 1; j++) {
			if (cmp_pcnt(a, n, j, j + 1) == -1) {
				swap_col(a, n, j, j + 1);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}

int main() {
	ushort a[16];
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

	bubble_sort(a, n, m);

	for (size_t i = 0; i < n; i++) {
		printf("%.*hb\n", m, a[i]);
	}

	return 0;
}
