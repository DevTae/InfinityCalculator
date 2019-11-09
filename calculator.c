/* calculator.c */
#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

int main(void) {
	int* expr;
	int size = input_expression(&expr);
	printf("size : %d\n", size);
	printList(expr);
	free(expr);
	return 0;
}
