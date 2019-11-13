/* stack.c */
#include "calculator.h"
#include <stdio.h>

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
	(*stack) = (*stack)->next;
	return data;
}

int isEmpty(Stack *stack) {
	if(stack == NULL)
		return 1;
	else return 0;
}

void print(Stack *stack) {
	while(isEmpty(stack) == 0)
		printf("%d ", pop_back(&stack));
	printf("\n");
}

