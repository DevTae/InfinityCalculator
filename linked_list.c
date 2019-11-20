/* linked_list.c */
#include "calculator.h"

// bidirection-linked-list
struct linked_list {
	int data;
	struct linked_list* left;
	struct linked_list* right;
};
// typedef struct linked_list numSet;

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
	newNumSet->left = NULL;
	if(*set == NULL) {
		newNumSet->right = NULL;
	} else {
		newNumSet->right = *set;
		(*set)->left = newNumSet;
	}
	*set = newNumSet;
}

void printSetL(numSet* set) {
	while(isEndL(set) == 0) set = set->left;
	while(isEndR(set) == 0) {
		printf("%d ", set->data);
		set = set->right;
	}
	printf("%d\n", set->data);
}

void printSetR(numSet* set) {
	while(isEndR(set) == 0) {
		printf("%d ", set->data);
		set = set->right;
	}
	printf("%d\n", set->data);
}

// below this line, there are no use functions now.
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

// prototype test code 
int main(void) {
	numSet* left = NULL;
	push_backL(&left, 3224224);
	push_backL(&left, 32525252);
	push_backL(&left, 12411);
	printSetL(left);
	printf("rtn_dataL: 1:%d, 2:%d, 3:%d\n", rtn_dataL(left, 1),
			rtn_dataL(left, 2), rtn_dataL(left, 3));
	return 0;
}
