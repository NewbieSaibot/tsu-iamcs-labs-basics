#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define XORSHIFT_IMPL
#include "xorshift.h"

size_t n = -1;

bool is_integer(char* s) {
	if (s == NULL) return false;

	for (int i = 0; s[i]; i++) {
		if (!('0' <= s[i] && s[i] <= '9')) {
			return false;
		}
	}

	return true;
}

int stoi(char* s) {
	if (s == NULL) return 0;

	int ret = 0;

	for (int i = 0; s[i]; i++) {
		ret *= 10;
		ret += s[i] - '0';
	}
	
	return ret;
}

#define swap(a, b) a ^= b; b ^= a; a ^= b;

void bubble_sort(int* a) {
	int m = n;

	while (m >= 1) {
		int new_m = 0;

		for (int i = 1; i < m; i++) {
			if (a[i - 1] > a[i]) {
				swap(a[i - 1], a[i]);
				new_m = i;
			}
		}

		m = new_m;
	}
}

void shaker_sort(int* a) {
	bool swapped;
	do {
		swapped = false;
		
		for (int i = 0; i < n - 1; i++) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}

		for (int i = n - 1; i > 0; i--) {
			if (a[i - 1] > a[i]) {
				swap(a[i - 1], a[i]);
				swapped = true;
			}
		}
	} while (swapped);
}

void sort(void s(int*), int* a) {
	struct timespec start, end, diff;
	timespec_get(&start, TIME_UTC);
	
	s(a);

	timespec_get(&end, TIME_UTC);

	diff.tv_sec = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000ll;
	diff.tv_nsec = (end.tv_nsec - start.tv_nsec) % 1000000000ll;

    if (diff.tv_nsec < 0) {
        diff.tv_sec--;
        diff.tv_nsec += 1000000000ll;
    }

	printf("Done sorting in %ld.%03lds\n", diff.tv_sec, (diff.tv_nsec / 1000000));
}

int main(int argc, char** argv) {
	int l = -1, r = -1;

#define parse_arg_int(x) {\
	if (i + 1 < argc) {\
		if (!is_integer(argv[i + 1])) {\
			fprintf(stderr, "%s must be integer\n", #x);\
			return 1;\
		}\
\
		x = stoi(argv[++i]);\
	} else {\
		fprintf(stderr, "Please, provide output file correctly\n");\
		return 1;\
	}}\

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
			parse_arg_int(n);
		} else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--left") == 0) {
			parse_arg_int(l);
		} else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--right") == 0) {
			parse_arg_int(r);
		} else {
			fprintf(stderr, "Unexpected argument: %s\n", argv[i]);
			return 1;
		}
	}

#undef parse_arg_int

#define oops(x) {\
	if (x == -1) {\
		fprintf(stderr, "You forgot to add %s\n", #x);\
		return 1;\
	}}

	oops(n);
	oops(l);
	oops(r);

#undef oops

	if (l >= r) {
		fprintf(stderr, "r must be larger than l\n");
		return 1;
	}

	init_xorshift();

	int *a = (int*)malloc(sizeof(int) * n),
		*b = (int*)malloc(sizeof(int) * n);

	if (a == NULL || b == NULL) {
		fprintf(stderr, "Error initializing arrays :(\n");
		return 1;
	}

	for (int i = 0; i < n; i++) a[i] = xs_rand(l, r);

#define output_arr(a)\
	if (n <= 30) {\
		for (int i = 0; i < n; i++) printf("%d ", a[i]);\
		printf("\n");\
	}\

	output_arr(a);

#define do_sort(type_of_sort)\
	memcpy(b, a, sizeof(int) * n);\
	printf("%s:\n", #type_of_sort);\
	sort(type_of_sort, b);\
	output_arr(b);\

	do_sort(bubble_sort);
	do_sort(shaker_sort);

	return 0;
}
