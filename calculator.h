/* calculator.h */
#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) (a > b) ? a : b

// inputProcess.c
int input_expression(int**);

// outputProcess.c
void printList(int*);

// stack.c
struct stack {
	int data;
	struct stack* next;
};
typedef struct stack Stack;
Stack* new_node(int);
void push_back(Stack**, int);
int pop_back(Stack**);
int isEmpty(Stack*);
void print(Stack*);

// in-postfix.c
int* toPostfix(int*, int);

// numSet.c
struct linked_list {
	int data;
	struct linked_list* left;
	struct linked_list* right;
};
typedef struct linked_list numSet;
int isEndL(const numSet*);
int isEndR(const numSet*);
void push_backL(numSet**, int);
void push_backR(numSet**, int);
void printSetL(numSet*);
void printSetR(numSet*);
int rtn_dataL(numSet*, int);
int rtn_dataR(numSet*, int);
int rtn_sizeL(numSet*);
int rtn_sizeR(numSet*);
int rtn_topL(numSet*);
int rtn_topR(numSet*);
void chg_dataL(numSet**, int, int);
void chg_dataR(numSet**, int, int);

// infinite.c
struct infinite {
	int isMinus;
	numSet *left;
	numSet *right;
};
typedef struct infinite infinite;
numSet* makeSetL(infinite**, char*);
numSet* makeSetR(infinite**, char*);
char* substring(char *, char[], int, int);
infinite* initialize(char*);

// calculate.c
int math_pow(int, int);
int intlen(int);
infinite* multiply(infinite*, infinite*);

