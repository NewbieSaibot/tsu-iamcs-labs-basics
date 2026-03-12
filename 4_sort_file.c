#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define file FILE

bool verbose = false;
void print_file(const char* name) {
	if (!verbose) return;

	file *f = fopen(name, "r");
	
	if (f == NULL) {
		fprintf(stderr, ":(\n");
		exit(1);
	}

	printf("%s: ", name);
	int x;
	while (fscanf(f, "%d", &x) == 1) {
		printf("%d ", x);
	}
	printf("\n");
	fclose(f);
}

file *f = NULL, *g1 = NULL, *g2 = NULL;

size_t iter = 0;
int x[2];
size_t out_idx = 0, in_idx = 0;

int main(int argc, char** argv) {
	struct timespec ts_begin, ts_end, ts_diff;
	timespec_get(&ts_begin, TIME_UTC);

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
			if (i + 1 < argc) {
				in_idx = i + 1;
				f = fopen(argv[++i], "r");
			} else {
				fprintf(stderr, "Please specify input file correctly\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
			verbose = true;
		} else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
			if (i + 1 < argc) {
				out_idx = i + 1;
				i++;
				//g1 = fopen(argv[++i], "w");
			} else {
				fprintf(stderr, "Please specify output file correctly\n");
				return 1;
			}
		} else {
			fprintf(stderr, "Invalid argument: %s\n", argv[i]);
			return 1;
		}
	}

	g1 = fopen(".tmpsortfile1", "w");
	g2 = fopen(".tmpsortfile2", "w");
	
	if (f == NULL || g1 == NULL || g2 == NULL) {
		fprintf(stderr, ":(\n");
		return 1;
	}

	size_t n = 0;
	
	if (fscanf(f, "%d", &x[0]) != 1) {
		printf("Empty input file\n");
		fclose(f);
		fclose(g1);
		fclose(g2);
		return 0;
	}

	while (fscanf(f, "%d", &x[1]) == 1) {
		if (!n) {
			fprintf(g1, "%d ", x[0]);
		} else {
			fprintf(g2, "%d ", x[0]);
		}
		
		if (!feof(f) && x[0] <= x[1]) {
			x[0] = x[1];
		} else {
			x[0] = x[1];
			n ^= 1;
		}
	}

	if (!n) {
		fprintf(g1, "%d ", x[0]);
	} else {
		fprintf(g2, "%d ", x[0]);
	}

	fclose(f);
	fclose(g1);
	fclose(g2);

	print_file(".tmpsortfile1");
	print_file(".tmpsortfile2");

	int runs = 2;
	n = 0;

	while (runs > 1) {
		g1 = fopen(".tmpsortfile1", "r");
		g2 = fopen(".tmpsortfile2", "r");
		f = fopen(argv[out_idx], "w");

		if (f == NULL || g1 == NULL || g2 == NULL) {
			fprintf(stderr, ":(\n");
			return 1;
		}

		runs = 0;
		bool has_x[2] = { 0, 0 };
		bool run[2] = { 0, 0 };
		int prev[2];

		has_x[0] = (fscanf(g1, "%d", &x[0]) == 1);
		has_x[1] = (fscanf(g2, "%d", &x[1]) == 1);

		for (int i = 0; i < 2; i++) if (has_x[i]) {
			if (has_x[i]) {
				run[i] = true;
				prev[i] = x[i];
			}
		}

		while (has_x[0] || has_x[1]) {
			bool active[2] = { run[0], run[1] };

			while (active[0] || active[1]) {
				if (active[0] && active[1]) {
					if (x[0] <= x[1]) {
						fprintf(f, "%d ", x[0]);
						prev[0] = x[0];
						has_x[0] = (fscanf(g1, "%d", &x[0]) == 1);
						if (!has_x[0] || x[0] < prev[0]) {
							active[0] = run[0] = false;
						}
					} else {
						fprintf(f, "%d ", x[1]);
						prev[1] = x[1];
						has_x[1] = (fscanf(g2, "%d", &x[1]) == 1);
						if (!has_x[1] || x[1] < prev[1]) {
							active[1] = run[1] = false;
						}
					}
				} else if (active[0]) {
					fprintf(f, "%d ", x[0]);
					prev[0] = x[0];
					has_x[0] = (fscanf(g1, "%d", &x[0]) == 1);
					if (!has_x[0] || x[0] < prev[0]) {
						active[0] = run[0] = false;
					}
				} else if (active[1]) {
					fprintf(f, "%d ", x[1]);
					prev[1] = x[1];
					has_x[1] = (fscanf(g2, "%d", &x[1]) == 1);
					if (!has_x[1] || x[1] < prev[1]) {
						active[1] = run[1] = false;
					}
				}

				if (!run[0] && has_x[0]) {
					run[0] = true;
					prev[0] = x[0];
				}
				if (!run[1] && has_x[1]) {
					run[1] = true;
					prev[1] = x[1];
				}
			}

			runs++;
		}

		fclose(f);
		fclose(g1);
		fclose(g2);

		//Output is done!
		if (runs == 1) break;

		f = fopen(argv[out_idx], "r");
		g1 = fopen(".tmpsortfile1", "w");
		g2 = fopen(".tmpsortfile2", "w");

		if (f == NULL || g1 == NULL || g2 == NULL) {
			fprintf(stderr, ":(\n");
			return 1;
		}

		n = 0;

		if (fscanf(f, "%d", &x[0]) != 1) {
			fclose(f);
			fclose(g1);
			fclose(g2);
			break;
		}

		while (fscanf(f, "%d", &x[1]) == 1) {
			if (!n) fprintf(g1, "%d ", x[0]);
			else fprintf(g2, "%d ", x[0]);

			if (x[0] <= x[1]) {
				x[0] = x[1];
			} else {
				x[0] = x[1];
				n ^= 1;
			}
		}

		if (!n) {
			fprintf(g1, "%d ", x[0]);
		} else {
			fprintf(g2, "%d ", x[0]);
		}

		fclose(f);
		fclose(g1);
		fclose(g2);

		if (verbose) {
			printf("Iteration %zu:\n", ++iter);
			print_file(argv[out_idx]);
			print_file(".tmpsortfile1");
			print_file(".tmpsortfile2");
		}
	}
	
	remove(".tmpsortfile1");
	remove(".tmpsortfile2");

	print_file(argv[out_idx]);

	printf("Yay! :D\n");

	timespec_get(&ts_end, TIME_UTC);
	ts_diff.tv_sec = ts_end.tv_sec - ts_begin.tv_sec + (ts_end.tv_nsec - ts_end.tv_nsec) / 1000000000;
	ts_diff.tv_nsec = (ts_end.tv_nsec - ts_begin.tv_nsec) % 1000000000;

	if (ts_diff.tv_nsec < 0) {
		ts_diff.tv_sec--;
		ts_diff.tv_nsec += 1000000000;
	}

	printf("Done sorting in %ld.%0.3lds.\n", ts_diff.tv_sec, ts_diff.tv_nsec / 1000000);

	return 0;
}
