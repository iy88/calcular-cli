#ifndef CALC_H
#define CALC_H
#include "../lib/stack.h"
#include "../lib/anyTypeHashMap.h"
long double calcPostfixExpression(char *expression);
long double calcInfixExpression(char* expression);
#endif