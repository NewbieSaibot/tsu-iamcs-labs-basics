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

size_t digit_count(long long n) {
	if (n == 0) return 1;

	int cnt = 0;
	
	while (n) {
		n /= 10;
		cnt++;
	}
	
	return cnt;
}

int main(void) {
	file *f = NULL, *g = NULL;
	long long n = 0;
	int x;

	const char *in = "rev_example.txt", *out = "out.txt";

	f = fopen(in, "r"), g = fopen(out, "w");
		
	if (f == NULL) {
		fprintf(stderr, "Could not open %s\n", in);
		return 1;
	}

	if (g == NULL) {
		fprintf(stderr, "Could not open %s\n", out);
		return 1;
	}
	
	while (fscanf(f, "%d", &x) == 1) {
		file *tmp = NULL;
		char *tmp_name = (char*)malloc(4 + digit_count(n)); //"tmp123\0"

		sprintf(tmp_name, "%s%lld", "tmp", n);

		tmp = fopen(tmp_name, "w");

		if (tmp == NULL) {
			fprintf(stderr, "Could not open %s\n", tmp_name);
			return 1;
		}

		fprintf(tmp, "%d", x);
		
		fclose(tmp);

		n++;
	}

	fclose(f);

	while (n) {
		n--;
		file *tmp = NULL;
		char *tmp_name = (char*)malloc(4 + digit_count(n));

		sprintf(tmp_name, "%s%lld", "tmp", n);

		tmp = fopen(tmp_name, "r");

		if (tmp == NULL) {
			fprintf(stderr, "Could not open %s\n", tmp_name);
			return 1;
		}
		
		int x;
		fscanf(tmp, "%d", &x);
		
		fprintf(g, "%d ", x);
		
		fclose(tmp);

		// Remove temporary file
		unlink(tmp_name);
	}
	
	fclose(g);
	
	return 0;
}
