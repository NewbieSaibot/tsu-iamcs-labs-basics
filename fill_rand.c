#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XORSHIFT_IMPL
#include "xorshift.h"

#define file FILE

int main(int argc, char** argv) {
	bool verbose = 0;
	size_t n = 0;
	int l = 0, r = 10;
	file *output = NULL;

	init_xorshift();

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
			if (i + 1 < argc) {
				output = fopen(argv[++i], "w");
			} else {
				//fprintf(stderr, "Error opening the output file\n");
				//return 1;
			}
		} else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--left") == 0) {
			if (i + 1 < argc) {
				if (sscanf(argv[++i], "%d", &l) != 1) {
					fprintf(stderr, "Please, specify the left border correctly\n");
					return 1;
				}
			} else {
				fprintf(stderr, "Please, specify the left border correctly\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--right") == 0) {
			if (i + 1 < argc) {
				if (sscanf(argv[++i], "%d", &r) != 1) {
					fprintf(stderr, "Please, specify the right border correctly\n");
					return 1;
				}
			} else {
				fprintf(stderr, "Please, specify the right border correctly\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
			if (i + 1 < argc) {
				if (sscanf(argv[++i], "%zu", &n) != 1) {
					fprintf(stderr, "Please, specify the number of output files correctly\n");
					return 1;
				}
			} else {
				fprintf(stderr, "Please, specify the number of output files\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
			verbose = true;
		} else {
			fprintf(stderr, "Invalid argument: %s\n", argv[i]);
			return 1;
		}
	}

	if (output == NULL) {
		for (size_t i = 0; i < n; i++) {
			printf("%d ", xs_rand(l, r));
		}
	} else {
		for (size_t i = 0; i < n; i++) {
			if (verbose) {
				int x = xs_rand(l, r);
				fprintf(output, "%d ", x);
				printf("%d ", x);
			} else {
				fprintf(output, "%d ", xs_rand(l, r));
			}
		}
		fclose(output);
	}
	
	return 0;
}
