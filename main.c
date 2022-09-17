#include "src/core.h"
#include <stdio.h>

int main() {
	char* s = malloc(sizeof(char) * 101);
	if (s == NULL) {
		printf("no mem\n");
		return -1;
	}
input:
	printf("expression: ");
	char c;
	int count = 0;
	while ((c = getchar()) != '\n') {
		s[count] = c;
		count++;
		if (count == 101) {
			printf("expression too long");
			break;
		}
	}
	s[count] = '\0';
	printf("res: %f\n",calcPostfixExpression(s));
	printf("continue? (y/n) ");
	c = getchar();
	if (c == 'y') {
		c = getchar();
		goto input;
	}
	return 0;
}