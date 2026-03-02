#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define XORSHIFT_IMPL
#include "xorshift.h"

#define N 256
#define max(a, b) ((a > b) ? (a) : (b))

int n, m;
char *s;
char t[] = "Find me!";

int bad[N];
int ans[N];
int ans_idx = 0;

void bad_char_preprocess() {
	for (int i = 0; i < N; i++) {
		bad[i] = -1;
	}

	for (int i = 0; i < m; i++) {
		bad[(int)t[i]] = i;
	}
}

void search() {
	bad_char_preprocess();

	int sh = 0;

	while (sh <= (n - m)) {
		int j = m - 1;

		while (j >= 0 && t[j] == s[j + sh]) {
			j--;
		}

		if (j < 0) {
			ans[ans_idx++] = sh;
			sh += (s + m < n) ? m - bad[s[sh + m]] : 1;
		} else {
			sh += max(1, j - bad[s[sh + j]]);
		}
	}
}

int main() {
	for (int i = 0; i < N; i++) ans[i] = -1;

	init_xorshift();

	n = 200, m = strlen(t);
	
	if (m > n) {
		fprintf(stderr, "Why? Just why?");
		return 1;
	}

	s = (char*)malloc(n + 1);
	s[n] = '\0';

	for (int i = 0; i < n; i++) {
		s[i] = (xs_rand(0, 2) ? ('a') : ('A')) + xs_rand(0, 26);
	}

	for (int k = 0; k < 4; k++) {
		int p = xs_rand(0, n - m);
		for (int j = 0; j < m; j++) {
			s[j + p] = t[j];
		}
	}

	printf("%s\n", s);

	search();

	int i = 0;
	for (int j = 0; j < n; j++) {
		if (ans[i] == j) {
			printf("\x1b[32m");
		}
		
		putc(s[j], stdout);

		if (ans[i] == j - m + 1) {
			printf("\x1b[0m");
			i++;
		}
	}
	printf("\n");

	free(s);
	
	return 0;
}
