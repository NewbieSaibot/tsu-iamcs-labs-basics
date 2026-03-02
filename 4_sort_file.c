#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define file FILE

file *f = NULL, *g1 = NULL, *g2 = NULL;

size_t iter = 0;
int x1, x2, y1, y2;
bool verbose = false;

int main(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
			if (i + 1 < argc) {
				f = fopen(argv[++i], "r");
			} else {
				fprintf(stderr, "Please specify input file correctly\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
			verbose = true;
		} else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
			if (i + 1 < argc) {
				g1 = fopen(argv[++i], "w");
			} else {
				fprintf(stderr, "Please specify output file correctly\n");
				return 1;
			}
		} else {
			fprintf(stderr, "Invalid argument: %s\n", argv[i]);
			return 1;
		}
	}

	if (f == NULL) {
		fprintf(stderr, "Error reading input file\n");
		return 1;
	}

	g2 = fopen(".tmpsortfile", "w");
	
	
	
	return 0;
}
