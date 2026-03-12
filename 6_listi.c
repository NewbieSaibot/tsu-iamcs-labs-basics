#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LIST_IMPLEMENTATION
#include "list.h"

#define XORSHIFT_IMPL
#include "xorshift.h"

void exit_msg_sig(int sig) {
	printf("\nExiting listi (%d)...\n", sig);

	exit(0);
}

void exit_msg_atexit() {
	printf("Exiting listi...\n");
}

int main(void) {
	init_xorshift();

	List* list = ListInit();
	
	char cmd[40] = { 0 };

	printf("Hello %s!\n", getlogin());

	signal(SIGINT, exit_msg_sig);
	signal(SIGTERM, exit_msg_sig);

	while (true) {
		printf("\x1b[32m\e[1m");
		printf("listi> ");
		printf("\x1b[30m\e[m");

		if (scanf("%s", cmd) != 1) {
			continue;
		}

		if (!strcmp("rand", cmd) || !strcmp("r", cmd)) {
			int l, r;
			scanf("%d%d", &l, &r);
			int x = xs_rand(l, r);

			ListPushTail(list, x);
		} else if (!strcmp("add", cmd) || !strcmp("a", cmd)) {
			int x;
			scanf("%d", &x);

			ListPushAfterKey(list, x, x);
		} else if (!strcmp("quit", cmd) || !strcmp("q", cmd)) {
			break;
		} else if (!strcmp("clear", cmd) || !strcmp("c", cmd)) {
			ListClear(list);
		} else if (!strcmp("tail", cmd) || !strcmp("t", cmd)) {
			int x;
			scanf("%d", &x);

			ListPushTail(list, x);
		} else if (!strcmp("head", cmd) || !strcmp("h", cmd)) {
			int x;
			scanf("%d", &x);

			ListPushHead(list, x);
		} else if (!strcmp("print", cmd) || !strcmp("p", cmd)) {
			ListPrint(list);
		} else if (!strcmp("kill", cmd) || !strcmp("k", cmd)) {
			int x;
			scanf("%d", &x);

			ListKill(list, x);
		} else if (!strcmp("flush", cmd) || !strcmp("f", cmd)) {
			system("clear");
		} else {
			printf("Invalid command: %s\n", cmd);
			/*
			if (!atexit(exit_msg_atexit)) {
				return EXIT_FAILURE;
			}
			*/
		}
	}

	ListFree(list);

	if (!atexit(exit_msg_atexit)) {
		return EXIT_SUCCESS;
	}
}
