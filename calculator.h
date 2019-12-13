/* calculator.h */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b) (a > b) ? a : b
#define MIN(a,b) (a > b) ? b : a
#define INSERT_NUMBER 1 	// 0001
#define INSERT_OPERATOR 2	// 0010
#define INSERT_FIRST 4		// 0100
#define INSERT_END 8		// 1000

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
char* storeExpr(char*, const int, const int);
char* toPostFix(char*);

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
void cln_dataL(numSet**);
void cln_dataR(numSet**);

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
void printInfinite(infinite*);

// calculate.c
infinite* add(infinite*, infinite*);
infinite* subtract(infinite*, infinite*);
int intlen(int);
void put_toArr(infinite*, int***, int, int, int);
infinite* multiply(infinite*, infinite*);

