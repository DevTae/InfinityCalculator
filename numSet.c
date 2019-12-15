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

void push_backL(numSet** set, ONE_OF_NUMBERS data) {
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

void push_backR(numSet** set, ONE_OF_NUMBERS data) {
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
		printf("%09d", set->data);
		set = set->right;
	}
	if(set == NULL) return;
	printf("%09d", set->data);
}

void printSetR(numSet* set) {
	if(set == NULL) return;
	while(isEndR(set) == 0) {
		printf("%09d", set->data);
		set = set->right;
	}
	if(set == NULL) return;
	ONE_OF_NUMBERS data = set->data;
	// 마지막 의미 없는 숫자 0 제거 과정 (below 7 lines)
	for(int i = 0; i < 9 - intlen(data); i++)
		printf("0");
	while(data != 0 && data % 10 == 0) {
		data /= 10;
	}
	printf("%d", data);
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

void chg_dataL(numSet** set, int index, ONE_OF_NUMBERS val) {
	numSet* temp = *set;
	for(int i = 0; i < index-1; i++) {
		temp = temp->left;
	}
	temp->data = val;
}

// 오른쪽의 numSet의 index번째 원소의 값을 수정한다. change
void chg_dataR(numSet** set, int index, ONE_OF_NUMBERS val) {
	numSet* temp = *set;
	for(int i = 0; i < index-1; i++) {
		temp = temp->right;
	}
	temp->data = val;
}

// 0인 top 데이터를 하나씩 지운다. clean data
void cln_dataL(numSet** set) {
	if(*set == NULL) return;
	numSet* pin = *set;
	while(isEndL(pin) == 0) {
		pin = pin->left;
	}
	if(pin->data != 0) return;
	else if(pin->data == 0) {
		if(pin->right == NULL) { // 첫째 자리이면.
			pin = *set;
			*set = NULL;
			free(pin);
			return;
		}
		numSet* tmp = pin;
		pin = pin->right;
		pin->left = NULL;
		free(tmp);
		while(isEndR(pin) == 0) {
			if(pin->data == 0) {
				numSet* tmp1 = pin;
				pin = pin->right;
				pin->left = NULL;
				free(tmp1);
			} else break;
		}
	}
}

void cln_dataR(numSet** set) {
	if(*set == NULL) return;
	numSet* pin = *set;
	while(isEndR(pin) == 0) {
		pin = pin->right;
	}
	if(pin->data != 0) return;
	else if(pin->data == 0) {
		if(pin->left == NULL) { // 첫째 자리이면.
			pin = *set;
			*set = NULL;
			free(pin);
			return;
		}
		numSet* tmp = pin;
		pin = pin->left;
		pin->right = NULL;
		free(tmp);
		while(isEndL(pin) == 0) {
			if(pin->data == 0 && pin->left != NULL) {
				numSet* tmp1 = pin;
				pin = pin->left;
				pin->right = NULL;
				free(tmp1);
			} else break;
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
