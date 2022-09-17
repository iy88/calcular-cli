#include "core.h"

long double calcPostfixExpression(char* expression) {
	hashMapPtr m = createHashMap();
	int* t = calloc(1, sizeof(int));
	mapSet(m, "+", t, sizeof(int));
	mapSet(m, "-", t, sizeof(int));
	*t = 1;
	mapSet(m, "*", t, sizeof(int));
	mapSet(m, "/", t, sizeof(int));
	free(t);
	t = NULL;
	stackPtr st = createStack();
	int i = 0;
	stackPtr tmp = createStack();
	char c;
	int sign = 0;
	while ((c = expression[i]) != '\0') {
		if (c == '.' || '0' <= c && '9' >= c) {
			if (c == '.') {
				sign = 1;
			}
			stackPush(tmp, &c, sizeof(char));
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			int flag = 0;
			long double num2 = 0.0;
			if (tmp->size != 0) {
				unsigned int tInt = 0;
				char *tChar = NULL;
				int e10 = 1;
				if (sign) {
					while (*(tChar = stackPop(tmp)) != '.') {
						tInt = (*tChar - 48) * e10 + tInt;
						e10 *= 10;
					}
					num2 += (long double)tInt / e10;
				}
				e10 = 1;
				tInt = 0;
				while ((tChar = stackPop(tmp)) != NULL) {
					tInt = (*tChar - 48) * e10 + tInt;
					e10 *= 10;
				}
				num2 += tInt;
				sign = 0;
				flag = 1;
			}
			if (flag) {
				long double num1 = *(long double*)stackPop(st);
				long double res;
				switch (c) {
				case '+':
					res = num1 + num2;
					break;
				case '-':
					res = num1 - num2;
					break;
				case '*':
					res = num1 * num2;
					break;
				case '/':
					res = num1 / num2;
					break;
				default:
					break;
				}
				stackPush(st, &res, sizeof(long double));
			}
			else {
				num2 = *(long double*)stackPop(st);
				long double num1 = *(long double*)stackPop(st);
				long double res;
				switch (c) {
				case '+':
					res = num1 + num2;
					break;
				case '-':
					res = num1 - num2;
					break;
				case '*':
					res = num1 * num2;
					break;
				case '/':
					res = num1 / num2;
					break;
				default:
					break;
				}
				stackPush(st, &res, sizeof(long double));
			}
		}
		else {
			if (tmp->size != 0) {
				long double num = 0.0;
				unsigned int tInt = 0;
				char *tChar;
				int e10 = 1;
				if (sign) {
					while (*(tChar = stackPop(tmp)) != '.') {
						tInt = (*tChar - 48) * e10 + tInt;
						e10 *= 10;
					}
					num += (long double)tInt / e10;
				}
				e10 = 1;
				tInt = 0;
				while ((tChar = stackPop(tmp)) != NULL) {
					tInt = (*tChar - 48) * e10 + tInt;
					e10 *= 10;
				}
				num += tInt;
				stackPush(st, &num, sizeof(long double));
				sign = 0;
			}
		}
		i++;
	}
	return *(long double *)stackPop(st);
}

long double calcInfixExpression(char* expression) {
	return 0.0;
}
