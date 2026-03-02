#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define XORSHIFT_IMPL
#include "xorshift.h"

int lower_bound(int* a, size_t n, int k) {
	int l = -1, r = n;

	while (r - l - 1 > 0) {
		int m = (l + r) / 2;

		if (a[m] >= k) {
			r = m;
		} else {
			l = m;
		}
	}

	if (a[r] != k) return -1;

	return r;
}

int upper_bound(int* a, size_t n, int k) {
	int l = -1, r = n;

	while (r - l - 1 > 0) {
		int m = (l + r) / 2;

		if (a[m] <= k) {
			l = m;
		} else {
			r = m;
		}
	}

	if (a[l] != k) return -1;

	return l;
}

int main() {
	init_xorshift();

	size_t n;
	uint l, r;
	int k;
	scanf("%zu%u%u%d", &n, &l, &r, &k);

	int *a = malloc(sizeof(int) * n);

	a[0] = 0;
	for (int i = 1; i < n; i++) a[i] = a[i - 1] + xs_rand(l, r);

	for (int i = 0; i < n; i++) printf("%d ", a[i]);

	printf("\n%d\n", lower_bound(a, n, k));
	printf("%d\n", upper_bound(a, n, k));

	free(a);
	
	return 0;
}
