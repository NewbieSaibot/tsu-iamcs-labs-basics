#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
	T_CLOSING,
	T_OPENING,
	T_NUMBER,
	T_OPERAND,
	T_EMPTY
} TokenType;

typedef struct {
	size_t size;
	int priority;
	TokenType type;
	char* str;
} Token;

const char* operands[] = {
	"+",
	"-",
	"*",
	"/",
	"`mod`",
	"^^",
	"&",
	"|",
	"^",
	"\0"
};

bool isoperand(const char* str) {
	for (size_t i = 0; operands[i][0]; i++) {
		if (strcmp(operands[i], str) == 0) {
			return true;
		}
	}
	return false;
}

int operand_priority(const char* str) {
	if (strcmp("&", str) == 0 || strcmp("|", str) == 0 || strcmp("^", str) == 0) {
		return 4;
	} else if (strcmp("^^", str) == 0) {
		return 3;
	} else if (strcmp("*", str) == 0 || strcmp("/", str) == 0 || strcmp("`mod`", str) == 0) {
		return 2;
	}
	return 1;
}

bool isbbs(const char* str) {
	int cnt = 0;

	for (size_t i = 0; str[i]; i++) {
		if (str[i] == '(') {
			cnt++;
		} else if (str[i] == ')') {
			cnt--;
		}

		if (cnt < 0) return false;
	}

	return cnt == 0;
}

#define N 512
#define isword(c) (isdigit(c) || islower(c) || isupper(c))

int rpn(const char* expr) {
	size_t n = strlen(expr);
	bool operand_expected = false;

	Token tokens[512];
	size_t m = 0;

	if (!isbbs(expr)) {
		fprintf(stderr, "Unbalanced bracket sequence.\n");
		return 1;
	}

	Token to_add;
	to_add.priority = -1;
	to_add.size = 0;
	to_add.str = "\0";
	to_add.type = T_EMPTY;
	
	int priority_multiplier = 1;

	for (size_t i = 0; expr[i] != '\0' && expr[i] != '\n'; i++) {
		if (isspace(expr[i])) {
			continue;
		}
		
		if (expr[i] == '(') {
			priority_multiplier *= 8;
			continue;
		}
		else if (expr[i] == ')') {
			bracket_close:
				priority_multiplier /= 8;
				continue;
		}

		if (!isprint(expr[i])) {
			fprintf(stderr, "Why? Just why?\n");
			return 1;
		}
		
		if (isword(expr[i])) {
			to_add.type = T_NUMBER;

			if (operand_expected) {
				fprintf(stderr, "%zu character: operand expected", i);
				return 1;
			}

			int j = i;

			while (isword(expr[i]) || isspace(expr[i])) {
				if (isspace(expr[i])) {
					i++;
					continue;
				}

				if (to_add.size <= i - j + 1) {
					to_add.size *= 2;
					to_add.str = (char*)realloc(to_add.str, to_add.size);
				}
			}
		}

		else {
			
		}
	}
}

int main(int argc, char** argv) {
	//const char* expr = "(hello_world + 5) * 7 / 8 + 9";
	const char* expr = "a + 5 * 7";

	if (rpn(expr) == 0) {
		printf("Done\n");
	} else {
		fprintf(stderr, ":(\n");
	}
	
	return 0;
}
