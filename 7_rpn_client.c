#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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

			if (strcmp(expr, "quit") == 0) {
				free(expr);
				break;
			}
		}

		char* ex = (char*)malloc((32 + strlen(expr)) * sizeof(char));

		if (ex == NULL) {
			fprintf(stderr, "Malloc fail\n");
			free(expr);
			continue;
		}

		strcpy(ex, "./7_rpn '");
		strcat(ex, expr);
		strcat(ex, "'");

		printf("%s\n", ex);

		system(ex);
		free(ex);
		free(expr);
	}

	return 0;
}
