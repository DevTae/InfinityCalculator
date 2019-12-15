/* stack.c */
#include "calculator.h"

Stack* new_node(int data) {
	Stack *stack = (Stack*)malloc(sizeof(Stack));
	stack->data = data;
	stack->next = NULL;
	return stack;
}

void push_back(Stack **stack, int data) {
	Stack* new = new_node(data);
	new->next = *stack;
	(*stack) = new;
}

int pop_back(Stack **stack) {
	int data = (*stack)->data;
	Stack* temp = *stack;
	(*stack) = (*stack)->next;
	free(temp);
	return data;
}

int isEmpty(Stack *stack) {
	if(stack == NULL)
		return 1;
	else return 0;
}

int getSize(Stack *stack) {
	int c = 0;
	while(!isEmpty(stack)) {
		c++;
		stack = stack->next;
	}
	return c;
}

void print(Stack *stack) {
	while(isEmpty(stack) == 0) {
		printf("%d ", stack->data);
		stack = stack-> next;
	}
	printf("\n");
}
// practice function main
/*
int main(void) {
	Stack* a = NULL;
	printf("a = NULL\n");
	push_back(&a, 1);
	push_back(&a, 2);
	push_back(&a, 35);
	print(a);
	printf("\nsize: %d\n", getSize(a));
	print(a);
	return 0;
}*/
