#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LIST_IMPLEMENTATION
#include "list.h"

#define XORSHIFT_IMPL
#include "xorshift.h"

#define file FILE

int main(int argc, char** argv) {
	file *f = fopen(argv[1], "r");

	if (f == NULL) {
		perror(":(\n");
		return 1;
	}

	init_xorshift();

	List* list = ListInit();
	
	char token[2000] = { 0 };

	while (fscanf(f, "%s", token) == 1) {
		if (token[0] == '#') {
			continue;
		}

		if (!strcmp("rand", token) || !strcmp("r", token)) {
			int l, r;
			scanf("%d%d", &l, &r);
			int x = xs_rand(l, r);

			ListPushTail(list, x);
		} else if (!strcmp("add", token) || !strcmp("a", token)) {
			int x;
			fscanf(f, "%d", &x);

			ListPushAfterKey(list, x, x);
		} else if (!strcmp("quit", token) || !strcmp("q", token)) {
			break;
		} else if (!strcmp("clear", token) || !strcmp("c", token)) {
			ListClear(list);
		} else if (!strcmp("tail", token) || !strcmp("t", token)) {
			int x;
			fscanf(f, "%d", &x);

			ListPushTail(list, x);
		} else if (!strcmp("head", token) || !strcmp("h", token)) {
			int x;
			fscanf(f, "%d", &x);

			ListPushHead(list, x);
		} else if (!strcmp("print", token) || !strcmp("p", token)) {
			ListPrint(list);
		} else if (!strcmp("kill", token) || !strcmp("k", token)) {
			int x;
			fscanf(f, "%d", &x);

			ListKill(list, x);
		} else if (!strcmp("flush", token) || !strcmp("f", token)) {
			system("clear");
		} else {
			printf("Invalid command: %s\n", token);
			return 1;
		}
	}

	ListFree(list);

	return 0;
}
