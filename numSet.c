/* numSet.c */
#include "calculator.h"

// bidirection-linked-list

int isEndL(const numSet *set) {
	if(set->left == NULL) return 1;
	else return 0;
}

int isEndR(const numSet *set) {
	if(set->right == NULL) return 1;
	else return 0;
}

void push_backL(numSet** set, int data) {
	numSet *newNumSet = (numSet*)malloc(sizeof(numSet));
	newNumSet->data = data;
	newNumSet->right = NULL;
	if(*set == NULL) {
		newNumSet->left = NULL;
	} else {
		newNumSet->left = *set;
		(*set)->right = newNumSet;
	}
	*set = newNumSet;
}

void push_backR(numSet** set, int data) {
	numSet *newNumSet = (numSet*)malloc(sizeof(numSet));
	newNumSet->data = data;
	newNumSet->right = NULL;

	if(*set == NULL) {
		newNumSet->left = NULL;
		*set = newNumSet;
	} else {
		numSet* temp = *set;
		for(; isEndR(temp) == 0; temp = temp->right);
		temp->right = newNumSet;
	}
}

void printSetL(numSet* set) {
	while(isEndL(set) == 0) set = set->left;
	while(isEndR(set) == 0) {
		printf("%09d ", set->data);
		set = set->right;
	}
	printf("%09d", set->data);
}

void printSetR(numSet* set) {
	while(isEndR(set) == 0) {
		printf("%09d ", set->data);
		set = set->right;
	}
	printf("%09d\n", set->data);
}

int rtn_dataL(numSet* set, int index) {
	for(int i = 1; i < index; i++) {
		set = set->left;
	}
	return set->data;
}

int rtn_dataR(numSet* set, int index) {
	for(int i = 1; i < index; i++) {
		set = set->right;
	}
	return set->data;
}

/* prototype test code 
int main(void) {
	numSet* left = NULL;
	push_backL(&left, 3224224);
	push_backL(&left, 32525252);
	push_backL(&left, 12411);
	printSetL(left);
	printf("rtn_dataL: 1:%d, 2:%d, 3:%d\n", rtn_dataL(left, 1),
			rtn_dataL(left, 2), rtn_dataL(left, 3));
	numSet* right = NULL;
	push_backR(&right, 41414141);
	push_backR(&right, 23232323);
	push_backR(&right, 12121212);
	printSetR(right);
	printf("rtndataR: 1:%d, 2:%d, 3:%d\n", rtn_dataR(right, 1),
			rtn_dataR(right, 2), rtn_dataR(right, 3));

	return 0;
}*/
