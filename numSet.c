/* numSet.c */
#include "calculator.h"

// bidirection-linked-list

int isEndL(const numSet *set) {
	if(set == NULL || set->left == NULL) return 1;
	else return 0;
}

int isEndR(const numSet *set) {
	if(set == NULL || set->right == NULL) return 1;
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
	if(set == NULL) return;
	while(isEndL(set) == 0) set = set->left;
	printf("%d", set->data);
	set = set->right;
	while(isEndR(set) == 0) {
		printf("%09d ", set->data);
		set = set->right;
	}
	printf("%09d", set->data);
}

void printSetR(numSet* set) {
	if(set == NULL) return;
	while(isEndR(set) == 0) {
		printf("%09d ", set->data);
		set = set->right;
	}
	int data = set->data;
	// 마지막 의미 없는 숫자 0 제거
	while(data % 10 == 0) {
		data /= 10;
	}
	printf("%d\n", set->data);
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

int rtn_sizeL(numSet* set) {
	if(set == NULL) return 0; // if havent element left of the point, rtn 0.
	int size = 0;
	while(isEndL(set) == 0) {
		++size;
		set = set->left;
	}
	return ++size;
}

int rtn_sizeR(numSet* set) {
	if(set == NULL) return 0; // if havent element left of the point, rtn 0.
	int size = 0;
	while(isEndR(set) == 0) {
		++size;
		set = set->right;
	}
	return ++size;
}

int rtn_topL(numSet* set) {
	while(isEndL(set) == 0) {
		set = set->left;
	}
	return set->data;
}

int rtn_topR(numSet* set) {
	while(isEndR(set) == 0) {
		set = set->right;
	}
	return set->data;
}

void chg_dataL(numSet** set, int index, int val) {
	numSet* temp = *set;
	for(int i = 0; i < index-1; i++) {
		temp = temp->left;
	}
	temp->data = val;
}

// 오른쪽의 numSet의 index번째 원소의 값을 수정한다. change
void chg_dataR(numSet** set, int index, int val) {
	numSet* temp = *set;
	for(int i = 0; i < index-1; i++) {
		temp = temp->right;
	}
	temp->data = val;
}

// 0인 top 데이터를 하나씩 지운다. clean data
void cln_dataL(numSet** set) {
	if(*set == NULL) return;
	numSet* del = *set;
	int index = 1;
	while(isEndL(del) == 0) {
		printf("1");
		del = del->left;
		index++;
	}
	while(index > 0 && rtn_dataL(del, index--) == 0) {
		if(index != 1) {
			printf(":%d:", index);
			numSet* tmp = del;
			del = del->right;

			free(tmp);
		} else { // if index is 1
			free(del = *set);
			*set = NULL;
			break;
		}
	}
}

void cln_dataR(numSet** set) {
	if(*set == NULL) return;
	numSet* del = *set;
	int index = 1;
	while(isEndR(del) == 0) {
		del = del->right;
		index++;
	}
	while(index > 0 && rtn_dataR(del, index--) == 0) {
		if(index != 1) {
			numSet* tmp = del;
			del = del->left;
			free(tmp);
		} else { // if index is 1
			free(del = *set);
			*set = NULL;
			break;
		}
	}
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
