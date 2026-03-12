#include <stdio.h>
#include <stdlib.h>

#define LIST_IMPLEMENTATION
#include "list.h"

int main() {
	List* list = ListInit();
	
	for (int i = 0; i < 5; i++) {
		ListPushTail(list, i);
	}

	ListPrint(list);

	for (int i = 0; i < 5; i++) {
		ListPushHead(list, i);
	}

	ListPrint(list);

	ListPushAfterKey(list, 0, 1337);

	ListPrint(list);

	ListFree(list);

	return 0;
}
