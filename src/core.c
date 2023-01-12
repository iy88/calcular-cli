#include "core.h"

unsigned long long slen(char* s) {
	unsigned long long len = 0;
	while (s[len] != '\0') {
		len++;
	}
	return len;
}

void _copy(void* dst, void* src, unsigned long long size) {
	char* d = dst;
	char* s = src;
	while (size-- > 0) {
		*d++ = *s++;
	}
}

long double calcPostfixExpression(char* expression) {
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
			long double* num2 = malloc(sizeof(long double));
			if (!num2) {
				perror("alloc failure\n");
				return 0;
			}
			*num2 = 0.0;
			if (tmp->size != 0) {
				unsigned int tInt = 0;
				char* tChar = NULL;
				int e10 = 1;
				if (sign) {
					while (*(tChar = stackPop(tmp)) != '.') {
						tInt = (*tChar - 48) * e10 + tInt;
						free(tChar);
						e10 *= 10;
					}
					*num2 += (long double)tInt / e10;
				}
				e10 = 1;
				tInt = 0;
				while ((tChar = stackPop(tmp)) != NULL) {
					tInt = (*tChar - 48) * e10 + tInt;
					free(tChar);
					e10 *= 10;
				}
				num2 += tInt;
				sign = 0;
				flag = 1;
			}
			if (flag) {
				long double* num1 = (long double*)stackPop(st);
				long double* res = malloc(sizeof(long double));
				if (!res) {
					perror("alloc failure\n");
					return 0;
				}
				*res = 0.0;
				switch (c) {
				case '+':
					*res = *num1 + *num2;
					break;
				case '-':
					*res = *num1 - *num2;
					break;
				case '*':
					*res = *num1 * *num2;
					break;
				case '/':
					*res = *num1 / *num2;
					break;
				default:
					break;
				}
				free(num1);
				free(num2);
				stackPush(st, res, sizeof(long double));
			}
			else {
				free(num2);
				num2 = (long double*)stackPop(st);
				long double* num1 = (long double*)stackPop(st);
				long double* res = malloc(sizeof(long double));
				if (!res) {
					perror("alloc failure\n");
					return 0;
				}
				*res = 0.0;
				switch (c) {
				case '+':
					*res = *num1 + *num2;
					break;
				case '-':
					*res = *num1 - *num2;
					break;
				case '*':
					*res = *num1 * *num2;
					break;
				case '/':
					*res = *num1 / *num2;
					break;
				default:
					break;
				}
				free(num1);
				free(num2);
				stackPush(st, res, sizeof(long double));
			}
		}
		else {
			if (tmp->size != 0) {
				long double* num = malloc(sizeof(long double));
				if (!num) {
					perror("alloc failure\n");
					return 0;
				}
				*num = 0.0;
				unsigned int tInt = 0;
				char* tChar;
				int e10 = 1;
				if (sign) {
					while (*(tChar = stackPop(tmp)) != '.') {
						tInt = (*tChar - 48) * e10 + tInt;
						free(tChar);
						e10 *= 10;
					}
					*num += (long double)tInt / e10;
				}
				e10 = 1;
				tInt = 0;
				while ((tChar = stackPop(tmp)) != NULL) {
					tInt = (*tChar - 48) * e10 + tInt;
					free(tChar);
					e10 *= 10;
				}
				*num += tInt;
				stackPush(st, num, sizeof(long double));
				sign = 0;
			}
		}
		i++;
	}
	stackClean(tmp);
	stackDestory(tmp);
	long double* p = (long double*)stackPop(st);
	stackClean(st);
	stackDestory(st);
	long double res = *p;
	free(p);
	return res;
}

long double calcInfixExpression(char* expression) {
	stackPtr nums = createStack();
	stackPtr ops = createStack();
	hashMapPtr m = createHashMap();
	int t = 0;
	mapSet(m, "+", &t, sizeof(int));
	mapSet(m, "-", &t, sizeof(int));
	t = 1;
	mapSet(m, "*", &t, sizeof(int));
	mapSet(m, "/", &t, sizeof(int));
	stackPtr tmp = createStack();
	int sign = 0;
	char c;
	int i = 0;
	while ((c = expression[i]) != '\0') {
		if (c == '.' || '0' <= c && '9' >= c) {
			stackPush(tmp, &c, sizeof(char));
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			if (tmp->size != 0) {
				char* num = malloc(sizeof(char) * (tmp->size + 1));
				if (!num) {
					perror("alloc error\n");
					return 0;
				}
				const unsigned long long size = tmp->size;
				num[size] = '\0';
				int j = 0;
				char* tmpC;
				while (tmp->size != 0) {
					tmpC = (char*)stackPop(tmp);
					num[size - 1 - j] = *tmpC;
					free(tmpC);
					j++;
				}
				stackPush(nums, num, sizeof(char) * (size + 1));
				free(num);
			}
			if (ops->size == 0 || *(char*)ops->top == '(') {
				char* s = malloc(sizeof(char) * 2);
				s[0] = c;
				s[1] = '\0';
				stackPush(ops, s, sizeof(char) * 2);
				free(s);
			}
			else {
				char* s1 = malloc(sizeof(char) * 2);
				if (!s1) {
					perror("alloc error\n");
					return 0;
				}
				s1[0] = c;
				s1[1] = '\0';
				char* s2 = malloc(sizeof(char) * 2);
				if (!s2) {
					perror("alloc error\n");
					return 0;
				}
				s2[0] = *(char*)ops->top;
				s2[1] = '\0';
				if (*(int*)mapGet(m, s1) > *(int*)mapGet(m, s2)) {
					stackPush(ops, s1, sizeof(char));
				}
				else {
					while (ops->size > 0 && *(char*)ops->top != '(' && *(int*)mapGet(m, s1) <= *(int*)mapGet(m, s2)) {
						stackPush(nums, s2, sizeof(char) * 2);
						free(stackPop(ops));
						if (ops->size > 0) {
							s2[0] = *(char*)ops->top;
						}

					}
					stackPush(ops, s1, sizeof(char) * 2);
					free(s1);
					free(s2);
				}
			}
		}
		else if (c == '(') {
			if (tmp->size != 0) {
				char* num = malloc(sizeof(char) * (tmp->size + 1));
				if (!num) {
					perror("alloc error\n");
					return 0;
				}
				const unsigned long long size = tmp->size;
				num[size] = '\0';
				int j = 0;
				char* tmpC;
				while (tmp->size != 0) {
					tmpC = (char*)stackPop(tmp);
					num[size - 1 - j] = *tmpC;
					free(tmpC);
					j++;
				}
				stackPush(nums, num, sizeof(char) * (size + 1));
				free(num);
			}
			char* s = malloc(sizeof(char) * 2);
			if (!s) {
				perror("alloc error\n");
				return 0;
			}
			s[0] = c;
			s[1] = '\0';
			stackPush(ops, s, sizeof(char) * 2);
			free(s);
		}
		else if (c == ')') {
			if (tmp->size != 0) {
				char* num = malloc(sizeof(char) * (tmp->size + 1));
				if (!num) {
					perror("alloc error\n");
					return 0;
				}
				const unsigned long long size = tmp->size;
				num[size] = '\0';
				int j = 0;
				char* tmpC;
				while (tmp->size != 0) {
					tmpC = (char*)stackPop(tmp);
					num[size - 1 - j] = *tmpC;
					free(tmpC);
					j++;
				}
				stackPush(nums, num, sizeof(char) * (size + 1));
				free(num);
			}
			char* s = malloc(sizeof(char) * 2);
			if (!s) {
				perror("alloc error\n");
				return 0;
			}
			char* tmpC;
			s[1] = '\0';
			while (*(char*)ops->top != '(') {
				tmpC = (char*)stackPop(ops);
				s[0] = *tmpC;
				free(tmpC);
				stackPush(nums, s, sizeof(char) * 2);
			}
			free(stackPop(ops));
			free(s);
		}
		else {
			if (tmp->size != 0) {
				char* num = malloc(sizeof(char) * (tmp->size + 1));
				if (num == NULL) {
					printf("no mem\n");
					exit(-1);
				}
				const unsigned long long size = tmp->size;
				num[size] = '\0';
				int j = 0;
				char* tmpC;
				while (tmp->size != 0) {
					tmpC = (char*)stackPop(tmp);
					num[size - 1 - j] = *tmpC;
					free(tmpC);
					j++;
				}
				stackPush(nums, num, sizeof(char) * (size + 1));
				free(num);
			}
		}
		i++;
	}
	if (tmp->size != 0) {
		char* num = malloc(sizeof(char) * (tmp->size + 1));
		if (num == NULL) {
			printf("no mem\n");
			exit(-1);
		}
		const unsigned long long size = tmp->size;
		num[size] = '\0';
		int j = 0;
		char* tmpC;
		while (tmp->size != 0) {
			tmpC = (char*)stackPop(tmp);
			num[size - 1 - j] = *tmpC;
			free(tmpC);
			j++;
		}
		stackPush(nums, num, sizeof(char) * (size + 1));
		free(num);
	}
	stackClean(tmp);
	stackDestory(tmp);
	mapClean(m);
	mapDestory(m);
	char* s = malloc(sizeof(char) * 2);
	if (s == NULL) {
		printf("no mem\n");
		exit(-1);
	}
	s[1] = '\0';
	char* tmpC;
	while (ops->size > 0) {
		tmpC = (char*)stackPop(ops);
		s[0] = *tmpC;
		free(tmpC);
		stackPush(nums, s, sizeof(char) * 2);
	}
	free(s);
	stackClean(ops);
	stackDestory(ops);
	unsigned long long fullSize = nums->size;
	stackPtr tNums = createStack();
	while (nums->size > 0) {
		s = stackPop(nums);
		unsigned long long size = slen(s);
		fullSize += size;
		stackPush(tNums, s, sizeof(char*) * size);
		free(s);
	}
	stackClean(nums);
	stackDestory(nums);
	char* exp = malloc(fullSize * sizeof(char));
	if (exp == NULL) {
		printf("no mem\n");
		exit(-1);
	}
	unsigned long long idx = 0;
	while (tNums->size > 0LL) {
		s = stackPop(tNums);
		const unsigned long long size = slen(s);
		_copy(exp + idx, s, size);
		idx += size;
		exp[idx] = ' ';
		idx++;
		free(s);
	}
	exp[fullSize - 1] = '\0';
	stackClean(tNums);
	stackDestory(tNums);
	//printf("RPN: %s\n", exp);
	long double res = calcPostfixExpression(exp);
	free(exp);
	return res;
}
