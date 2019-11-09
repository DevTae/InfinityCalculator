/* in-postfix.c */
#include <stdio.h>
#include <stdlib.h> // function "malloc" is used.

struct stack {
	//Element data;
	int data;
	Stack* next;
}

typedef struct stack Stack;

struct bidirection_linked_list {
	//Element data; temp
	int data;
	Link previous;
	Link next;
}

typedef struct bidirection_linked_list *Link;
typedef *Link Element; // Link is the pointer of expression.
typedef Element List; // one element that show its value.

//List getList(int*); // This is the input-function, building number struct.
int input_expression(int*);
List makeList(int*);
Element makeElement(int*);

int main(void) {
	int* infix;
	// assume that we could enter the string with no space.
	int c;
	while((c = getchar()) != '\n') {
		infix = (int*)malloc(sizeof(int) * 
	}
	getchar(); // clear the buffer.
	return 0;
}

int input_expression(int* expr) {
	int c; // input data that change frequently.
	int i = 0; // expr's index size.
	// array size is sizable to use byte of memory efficiently.
	while((c = getchar()) != '\n') {
		expr + i++ = (int*)malloc(sizeof(int) * 2);
		*(expr+i-1) = c;
	}
	// fill the last element with NULL value.
	*(expr + i++) = '\0';
	return i; // return size of array.
}

// this function is only built to make a decrete integer to continuous number data.
List makeList(int* expr) {
	List newList;
	newList->previous = '\0';
	int data;
	for(int i = 0; i < *(expr+i) != '\0'; i++) {
		// practice mode. input data can be entered in one digit value.
		// we have to make a function, guaranteeing none of one digit value can be entered.
		//*(expr + i) = 
	}
}

// we could distinguish operator with expression.

