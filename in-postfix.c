/* in-postfix.c */
#include "calculator.h"
// we could distinguish operator with expression.

int* toPostfix(int *infix, int size) {
	Stack *operator = NULL;
	int *postfix = (int*)malloc(sizeof(int) * size);
	int index = 0;
	int isParenthese = 0;
	for(int i = 0; *(infix+i) != '\0'; i++) {
		int c = *(infix+i);
		if(c < 48 || c > 57) {
			switch((char)c) {
				case '+':
					if(isParenthese == 0) {
						*(postfix + index++) = c;
						continue;
					}
					if(!isEmpty(operator) && operator->data == (int)'*') {
						pop_back(&operator);
						push_back(&operator, c);
						push_back(&operator, (int)'*');
					} else {
						push_back(&operator, c);
					}
					break;
				case '-':
					if(isParenthese == 0) {
						*(postfix + index++) = c;
						continue;
					}
					if(!isEmpty(operator) && operator->data == (int)'*') {
						pop_back(&operator);
						push_back(&operator, c);
						push_back(&operator, (int)'*');
					} else {
						push_back(&operator, c);
					}
					break;
				case '*':
					if(isParenthese == 0) {
						*(postfix + index++) = c;
						continue;
					}
					push_back(&operator, (int)'*');
					break;
				case '(':
					isParenthese += 1;
					push_back(&operator, (int)'(');
					break;
				case ')':
					isParenthese -= 1;
					int t;
					while((t = pop_back(&operator)) != (int)'(')  {
						*(postfix + index++) = t;
					}
					break;
				default:
					printf("you entered another opreator that we cant provide you.\n");
					break;
			}
			push_back(&operator, c);
		} else {
			// infinity linked list will be implemented.
			*(postfix + index++) = c;
		}
	}
	while(isEmpty(operator) == 0) {
		*(postfix + index++) = pop_back(&operator);
	}
	*(postfix + index) = '\0';
	return postfix;
}
