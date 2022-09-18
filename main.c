#include "src/core.h"
#include <stdio.h>

int main() {
	char* s = malloc(sizeof(char) * 201);
//	if (s == NULL) {
//		printf("no mem\n");
//		return -1;
//	}
//input:
//	printf("expression: ");
//	char c;
//	int count = 0;
//	while ((c = getchar()) != '\n') {
//		s[count] = c;
//		count++;
//		if (count == 101) {
//			printf("expression too long");
//			break;
//		}
//	}
//	s[count] = '\0';
//	printf("res: %f\n", calcInfixExpression(s));
//	printf("continue? (y/n) ");
//	c = getchar();
//	if (c == 'y') {
//		c = getchar();
//		goto input;
//	}
	for (int i = 0; i < 200; i += 2) {
		s[i] = '1';
		s[i + 1] = '+';
	}
	s[200] = '1';
	s[201] = '\0';
	printf("exp: %s\n", s);
	int j = 0;
	long double res;
	while (j < 1000) {
		res=calcInfixExpression(s);
		j++;
	}
	printf("res: %f\n", res);
	getchar();
	printf("done\n");
	return 0;
}