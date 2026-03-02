#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define XORSHIFT_IMPL
#include "xorshift.h"

#define file FILE
#define max(a, b) ((a > b) ? (a) : (b))

int n, m;
char *s;
char t[] = "Find me!";

int main() {
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

	file *tmp = fopen("tmp.txt", "w");
	fprintf(tmp, "%s", s);
	fclose(tmp);

	char cmd[512];

	snprintf(cmd, sizeof(cmd), "grep -b --color=always '%s' tmp.txt", t);

	int res = system(cmd);

	if (res != 0) {
		printf("Not found!\n");
	}

	unlink("tmp.txt");
	free(s);
	
	return 0;
}
