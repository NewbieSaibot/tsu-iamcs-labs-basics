#ifdef LIST_IMPLEMENTATION

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define null NULL

typedef struct Node {
	struct Node *prev;
	struct Node *next;
	int key;
} Node;

typedef struct List {
	Node* head;
	Node* tail;
	size_t size;
} List;

Node* NodeInit(int key) {
	Node* node = (Node*)malloc(sizeof(Node));

	node->prev = null;
	node->next = null;
	node->key = key;

	return node;
}

void NodeFree(Node* node) {
	if (node == null) return;
	node->prev = null;
	node->next = null;
	free(node);
}

List* ListInit() {
	List* list = (List*)malloc(sizeof(List));

	list->head = null;
	list->tail = null;
	list->size = 0;

	return list;
}

void ListClear(List* list) {
	if (list == null) return;

	Node* cur = list->tail;
	
	while (cur != null) {
		Node* tmp = cur->prev;
		NodeFree(cur);
		cur = tmp;
	}
	list->tail = list->head = null;

	list->size = 0;
}

void ListFree(List* list) {
	if (list == null) return;

	ListClear(list);

	free(list);
}

void ListPushTail(List* list, int key) {
	if (list == null) return;

	Node* node = NodeInit(key);
	
	if (list->size == 0) {
		list->head = list->tail = node;
	}
	else {
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}

void ListPushHead(List* list, int key) {
	if (list == null) return;

	Node* node = NodeInit(key);
	
	if (list->size == 0) {
		list->head = list->tail = node;
	}
	else {
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}
	list->size++;
}

void ListKill(List* list, int key) {
	if (list == null || list->size == 0) return;

	Node* cur = list->head;
	while (cur != null) {
		if (cur->key == key) {
			if (cur->prev != null) {
				cur->prev->next = cur->next;
			} else {
				list->head = cur->next;
			}
			
			if (cur->next != null) {
				cur->next->prev = cur->prev;
			} else {
				list->tail = cur->prev;
			}

			NodeFree(cur);
			list->size--;

			return;
		}
		cur = cur->next;
	}
}

void ListPushAfterKey(List* list, int key, int val) {
	if (list == null) return;

	if (list->size == 0) {
		ListPushHead(list, val);
		return;
	}

	Node* cur = list->head;
	while (cur != null) {
		if (cur->key == key) {
			Node* node = NodeInit(val);

			node->prev = cur;
			node->next = cur->next;

			if (cur->next != null) {
				cur->next->prev = node;
			} else {
				list->tail = node;
			}

			cur->next = node;
			list->size++;
			return;
		}
		cur = cur->next;
	}

	ListPushTail(list, val);
}

void ListPrint(List* list) {
	if (list == null) return;

	printf("Population: %zu\n", list->size);
	if (list->head && list->tail) {
		printf("Head: %d\n", list->head->key);
		printf("Tail: %d\n", list->tail->key);
	}
	Node* cur = list->head;
	while (cur != null) {
		printf("%d ", cur->key);
		cur = cur->next;

		if (cur != null) printf("<-> ");
	}

	if (list->head) {
		printf("\n");
	}
}

#endif
