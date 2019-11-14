/* calculator.h */
#include <stdio.h>
#include <stdlib.h>

struct stack {
	//Element data;
	int data;
	struct stack* next;
};

typedef struct stack Stack;

struct bidirection_linked_list {
	//Element data; temp
	int data;
	struct bidirection_linked_list* previous;
	struct bidirection_linked_list* next;
};

typedef struct bidirection_linked_list *Link;
typedef Link Element; // Link is the pointer of expression.
typedef Element List; // one element that show its value.

// inputPrcess.c
int input_expression(int**);
List makeList(int*);
Element makeElement(int*);

// outputProcess.c
void printList(int*);

// stack.c
Stack* new_node(int);
void push_back(Stack**, int);
int pop_back(Stack**);
int isEmpty(Stack*);
void print(Stack*);

// in-postfix.c
int* toPostfix(int*, int);
