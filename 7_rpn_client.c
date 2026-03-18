#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

int main(void) {
	char* expr = NULL;

	for (;;) {
		expr = readline("\x1b[31m\e[1mRPN> \x1b[0m\e[m");

		if (expr == NULL) {
			printf("Exiting...\n");
			break;
		}
		if (strlen(expr) > 0) {
			add_history(expr);

			if (strcmp(expr, "exit") == 0) {
				free(expr);
				break;
			}
		}

		char* input = NULL;

		sscanf(input, "./7_rpn %s", expr);

		system(input);
	}

	return 0;
}
