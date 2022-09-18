#include "stack.h"

void __copy(void* dst, void* src, unsigned long long size) {
	char* d = dst;
	char* s = src;
	while (size-- > 0) {
		*d++ = *s++;
	}
}

stackPtr createStack() {
	stackPtr st = (stackPtr)malloc(sizeof(stack));
	if (st == NULL) {
		return NULL;
	}
	st->size = 0;
	st->root = (stack_node_ptr)malloc(sizeof(stack_node));
	if (st->root == NULL) {
		free(st);
		return NULL;
	}
	st->root->next = NULL;
	st->root->data = NULL;
	st->root->size = 0;
	st->top = st->root->data;
	return st;
}

int stackPush(stackPtr st, void* data, unsigned long long size) {
	stack_node_ptr current = st->root;
	if (current->data == NULL) {
		current->data = malloc(size);
		if (current->data == NULL) {
			return 0;
		}
		current->size = size;
		__copy(current->data, data, size);
		st->top = st->root->data;
		st->size++;
		return 1;
	}
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = (stack_node_ptr)malloc(sizeof(stack_node));
	if (current->next == NULL) {
		return 0;
	}
	current->next->data = malloc(size);
	if (current->next->data == NULL) {
		return 0;
	}
	current->next->size = size;
	__copy(current->next->data, data, size);
	current->next->next = NULL;
	st->top = current->next->data;
	st->size++;
	return 1;
}

void* stackPop(stackPtr st) {
	stack_node_ptr current = st->root;
	if (current->next == NULL) {
		if (current->data == NULL) {
			return NULL;
		}
		else {
			void* res = malloc(current->size);
			if (res == NULL) {
				return NULL;
			}
			__copy(res, current->data, current->size);
			free(current->data);
			current->data = NULL;
			current->size = 0;
			st->top = current->data;
			st->size = 0;
			return res;
		}
	}
	while (current->next->next != NULL) {
		current = current->next;
	}
	void* res = malloc(current->next->size);
	if (res == NULL) {
		return NULL;
	}
	__copy(res, current->next->data, current->next->size);
	free(current->next->data);
	free(current->next);
	current->next = NULL;
	st->top = current->data;
	st->size--;
	return res;
}

void __cleanNode(stack_node_ptr node) {
	if (node->next != NULL) {
		__cleanNode(node->next);
	}
	free(node->data);
	free(node);
}

void stackClean(stackPtr st) {
	stack_node_ptr current = st->root;
	if (current->next == NULL) {
		if (current->data) {
			free(current->data);
			current->data = NULL;
			current->size = 0;
		}
	}
	else {
		free(current->data);
		current->data = NULL;
		current->size = 0;
		__cleanNode(current->next);
		current->next = NULL;
	}
	st->size = 0;
	st->top = st->root->data;
}

void stackDestory(stackPtr st) {
	free(st->root);
	free(st);
}