/* calculator.c */
#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

int main(void) {
	int* expr;
	int size = input_expression(&expr);
	printf("size : %d\n", size);
	printList(expr);
	printf("\nafter: ");
	int* postfix = toPostfix(expr, size);
	printList(postfix);
	printf("\n");
	free(expr);
	free(postfix);
	return 0;
}
