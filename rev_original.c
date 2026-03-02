#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//unlink(file)
#ifdef _WIN32
#include <io.h>
#define _unlink unlink
#else
#include <unistd.h>
#endif

#define file FILE

void flecpy(file *src, file* dest) {
	if (src == NULL || dest == NULL) return;

	int x;
	while (fscanf(src, "%d", &x) != EOF) {
		fprintf(dest, "%d ", x);
	}
}

int main(void) {
	file *f = NULL, *g1 = NULL, *g2 = NULL;
	long long n = 0;
	int x;

	const char *in = "rev_example.txt", *out1 = "out1.txt", *out2 = "out2.txt";

	f = fopen(in, "r"), g1 = fopen(out1, "w"), g2 = fopen(out2, "w");
		
	if (f == NULL) {
		fprintf(stderr, "Could not open %s\n", in);
		return 1;
	}

	if (g1 == NULL) {
		fprintf(stderr, "Could not open %s\n", out1);
		return 1;
	}

	if (g2 == NULL) {
		fprintf(stderr, "Could not open %s\n", out2);
		return 1;
	}

	fscanf(f, "%d", &x);
	fprintf(g1, "%d", x);

	fclose(g1);
	fclose(g2);

	bool t = 1;

	while (fscanf(f, "%d", &x) != EOF) {

		if (t) {
			g1 = fopen(out1, "r");
			g2 = fopen(out2, "w");
			if (g1 == NULL || g2 == NULL) {
				perror(":(\n");
				return 1;
			}
			fprintf(g2, "%d ", x);
			flecpy(g1, g2);
			fclose(g1);
			fclose(g2);
		} else {
			g1 = fopen(out1, "w");
			g2 = fopen(out2, "r");
			if (g1 == NULL || g2 == NULL) {
				perror(":(\n");
				return 1;
			}
			fprintf(g1, "%d ", x);
			flecpy(g2, g1);
			fclose(g1);
			fclose(g2);
		}
		
		t ^= 1;

	}

	const char *ans = "out.txt";
	file *g = fopen(ans, "w");
	if (t) {
		g1 = fopen(out1, "r");
		flecpy(g1, g);
		fclose(g1);
	} else {
		g2 = fopen(out2, "r");
		flecpy(g2, g);
		fclose(g2);
	}

	unlink(out1);
	unlink(out2);

	fclose(f);
	fclose(g);
	
	return 0;
}
