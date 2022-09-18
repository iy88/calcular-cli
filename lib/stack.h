#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <stdio.h>

typedef struct s_n {
	unsigned long long size;
	void* data;
	struct s_n* next;
} stack_node;

typedef stack_node* stack_node_ptr;

typedef struct {
	unsigned long long size;
	stack_node_ptr root;
	void* top;
} stack;

typedef stack* stackPtr;

stackPtr createStack();

int stackPush(stackPtr st,void* data, unsigned long long size);

void* stackPop(stackPtr st);

void stackClean(stackPtr st);

void stackDestory(stackPtr st);

#endif