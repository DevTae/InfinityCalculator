/* in-postfix.c */
#include "calculator.h"
// we could distinguish operator with expression.

int* toPostfix(int *infix, int size) {
	Stack *operator = NULL;
	int *postfix = (int*)malloc(sizeof(int) * size);
	int index = 0;
	for(int i = 0; *(infix+i) != '\0'; i++) {
		int c = *(infix+i);
		if(c < 48 || c > 57) {
			switch((char)c) {
				case '+':
					while(operator != NULL
						&&(operator->data == (int)'+'
						||operator->data == (int)'-'
						||operator->data == (int)'*')) {
						*(postfix + index++) = operator->data;
						pop_back(&operator);
					}
					push_back(&operator, c);
					break;
				case '-':
					while(operator != NULL
						&&(operator->data == (int)'+'
						||operator->data == (int)'-'
						||operator->data == (int)'*')) {
						*(postfix + index++) = operator->data;
						pop_back(&operator);
					}
					push_back(&operator, c);
					break;
				case '*':
					while(operator != NULL && operator->data == (int)'*') {
						*(postfix + index++) = operator->data;
						pop_back(&operator);
					}
					push_back(&operator, c);
					break;
				case '(':
					push_back(&operator, c);
					break;
				case ')':
					while(operator->data != '(')
						*(postfix + index++) = pop_back(&operator);
					pop_back(&operator); // clear the garbage.
					break;
				default:
					printf("you conveyed incorrect sentence with other operators.\n");
					exit(1);
			}
		} else {
			*(postfix + index++) = c;
		}
	}
	while(isEmpty(operator) == 0)
		*(postfix + index++) = pop_back(&operator);
	*(postfix + index) = '\0'; // Filling End point with '\0'(NULL) value.
	return postfix;
}
