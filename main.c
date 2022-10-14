#include "src/core.h"
#include <stdio.h>

int main() {
	char* s = malloc(sizeof(char) * 202);
	long double res = 0;
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
		if (count == 202) {
			printf("expression too long");
			break;
		}
	}
	s[count] = '\0';
	res = calcInfixExpression(s);
	printf("%s => %Lf\n", s, res);
	printf("continue? (y/n) ");
	c = getchar();
	if (c == 'y') {
		c = getchar();
		goto input;
	}
	free(s);
	return 0;
}