#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int key = -1;
bool verbose = false;
char *fnamein = "in.txt";
char *fnameout = NULL;

#define file FILE

file *in = NULL, *out = NULL;

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

char encrypt_char(char c) {
	bool l = islower(c), u = isupper(c);

	if (!l && !u) {
		return c;
	}

	char ret = c, foo = (l ? 'a' : 'A');
	
	ret -= foo;

	ret = (ret + key) % 26;
	
	ret += foo;

	return ret;
}

void encrypt_file() {
	char c, d;

	while ((c = fgetc(in)) != EOF) {
		d = encrypt_char(c);
		if (verbose) putc(d, stdout);
		fputc(d, out);
	}

	fclose(in);
	fclose(out);
}

int main(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
			if (i + 1 < argc) {
				fnameout = argv[++i];
			} else {
				fprintf(stderr, "Please, provide output file correctly\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--key") == 0) {
			if (i + 1 < argc) {
				if (!is_integer(argv[i + 1])) {
					fprintf(stderr, "Key should be integer\n");
					return 1;
				} else {
					key = stoi(argv[++i]);
				}
			} else {
				fprintf(stderr, "Please, provide key correctly\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
			verbose = true;
		} else {
			if (fnamein == NULL) {
				fnamein = argv[i];
			} else {
				fprintf(stderr, "Unexpected argument: %s\n", argv[i]);
				return 1;
			}
		}
	}

	if (fnamein == NULL) {
		fprintf(stderr, "No input file provided\n");
		return 1;
	}

	if (key == -1) {
		fprintf(stderr, "No key provided\n");
		return 1;
	}

	in = fopen(fnamein, "r");
	if (in == NULL) {
		perror("Cannot open input file correctly");
		return 1;
	}

	out = fopen(fnameout, "w");
	if (out == NULL) {
		perror("Cannot open output file correctly");
		return 1;
	}

	encrypt_file();

	return 0;
}
