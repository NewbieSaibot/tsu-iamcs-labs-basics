#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

int key = -1;
bool verbose = false;
char *fnamein = NULL;
char *fnameout = NULL;

#define file FILE

file *in = NULL, *out = NULL;

char decrypt_char(char c) {
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
		d = decrypt_char(c);
		if (verbose) putc(d, stdout);
		fputc(d, out);
	}

	fclose(in);
	fclose(out);
}

int main(void) {
	srand(time(NULL));

	if (rand() % 2) verbose = true;
	
	scanf("%d", &key);
	scanf("%s", fnamein);
	scanf("%s", fnameout);

	if (fnamein == NULL) {
		fprintf(stderr, "No input file provided\n");
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
