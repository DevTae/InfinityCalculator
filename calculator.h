/* calculator.h */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b) ((a > b) ? a : b)
#define MIN(a,b) ((a > b) ? b : a)
#define INSERT_NUMBER 1 	// 00001
#define INSERT_OPERATOR 2	// 00010
#define INSERT_FIRST 4		// 00100
#define INSERT_END 8		// 01000
#define INSERT_0REVERSE 16	// 10000
#define MAXDIGIT_PER_NUMBER 9
typedef int ONE_OF_NUMBERS;

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
int getSize(Stack*);
void print(Stack*); // useless

// in-postfix.c
char* storeExpr(char*, const int, const int);
char* toPostFix(char*);

// numSet.c
struct linked_list {
	ONE_OF_NUMBERS data;
	struct linked_list* left;
	struct linked_list* right;
};
typedef struct linked_list numSet;
int isEndL(const numSet*);
int isEndR(const numSet*);
void push_backL(numSet**, ONE_OF_NUMBERS);
void push_backR(numSet**, ONE_OF_NUMBERS);
void printSetL(numSet*);
void printSetR(numSet*);
int rtn_dataL(numSet*, int);
int rtn_dataR(numSet*, int);
int rtn_sizeL(numSet*);
int rtn_sizeR(numSet*);
int rtn_topL(numSet*);
int rtn_topR(numSet*);
void chg_dataL(numSet**, int, ONE_OF_NUMBERS);
void chg_dataR(numSet**, int, ONE_OF_NUMBERS);
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
char* substring_udf(char *cArr, int start, int size);
infinite* initialize(char*);
void printInfinite(infinite*);
int infcmp(infinite*, infinite*);
void freeInfinite(infinite**);

// calculate.c
infinite* add(infinite*, infinite*);
infinite* subtract(infinite*, infinite*);
int intlen(ONE_OF_NUMBERS);
void put_toArr(infinite*, int***, int, int, int);
infinite* multiply(infinite*, infinite*);

// decryptor.c
struct stackInfinite {
	infinite* data;
	struct stackInfinite* next;
};
typedef struct stackInfinite stackInf;
stackInf* new_node_sInf(infinite*);
void push_back_sInf(stackInf**, infinite*);
infinite* pop_back_sInf(stackInf**);
int isEmpty_sInf(stackInf*);
int getSize_sInf(stackInf*);
void print_sInf(stackInf*); // testing function
//infinite* (*getPtr(const char opCode))(infinite*, infinite*);
infinite* calculateManager(infinite*, infinite*, char);
infinite* calcul_box(char* elem, int option);
infinite* decrypt(char*);
