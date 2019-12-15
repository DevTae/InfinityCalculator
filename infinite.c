/* infinite.c */
#include "calculator.h"

char* substring_udf(char *cArr, int start, int size) {
	char* newArr = (char*)malloc(sizeof(char) * (size+1));
	for(int i = 0; i < size; i++) {
		*(newArr + i) = *(cArr + start + i);	
	}
	*(newArr + size) = '\0';
	//printf("?%s?\n", newArr);
	
	return newArr;
}

numSet* makeSetL(infinite** inf, char *num) {
	//printf("makeSetL: %s\n", num);
	numSet* left = NULL;
	int length = strlen(num);
	int remain = length % 9;
	if (remain != 0) {
		char *newArr = substring_udf(num, 0, remain);
		push_backL(&left, atoi(newArr));
		free(newArr);
	}
	for(int i = 0; length-remain-9*i > 0; i++) {
		char *newArr = substring_udf(num, remain+(9*i), 9);
		push_backL(&left, atoi(newArr));
		free(newArr);
	}
	return left;
}

numSet* makeSetR(infinite** inf, char *num) {
	//printf("makeSetR: %s\n", num);
	numSet* right = NULL;
	int length = strlen(num);
	int i = 0;
	while(length >= 9) {
		char *newArr = substring_udf(num, 9*(i++), 9);
		push_backR(&right, atoi(newArr));
		free(newArr);
		length -= 9;
	}
	if(length != 0) {
		char *newArr = substring_udf(num, 9*i, length);
		ONE_OF_NUMBERS rtn = atoi(newArr); //유지보수 atoi 함수 변경 가능
		free(newArr);
		//printf("atoi:%d\n", rtn);
		for(int p = 0; p < 9-length; p++) { // processing under real num.
			rtn *= 10;
		}
		push_backR(&right, rtn);
	}
	return right;
}

infinite* initialize(char* before) {
	infinite* inf = (infinite*)malloc(sizeof(infinite));
	char* pindex;
	if((pindex = strstr(before, ".")) != NULL) {
		int index = pindex - before;
		char *newArrL = substring_udf(before, 0, index);
		char *newArrR = substring_udf(before, index+1, strlen(before)-(index+1));
		inf->left = makeSetL(&inf, newArrL);
		inf->right = makeSetR(&inf, newArrR);
		free(newArrL);
		free(newArrR);
	} else {
		inf->left = makeSetL(&inf, before);
		inf->right = NULL;
	}
	inf->isMinus = 0; // isMinus Variable Activation
	return inf;
}

void printInfinite(infinite* inf) {
	if(inf == NULL) return;
	//if(inf->isMinus == 1) printf("-"); // isMinus
	if(inf->left == NULL) {
		printf("0");
	} else {
		printSetL(inf->left);
	}
	if(inf->right != NULL) {
		printf(".");
		printSetR(inf->right);
	}
	printf("\n");
}

// first > second : return 1
// first == second : return 0
// first < second : return -1
// 전제 : 불필요한 0 값 모두 없음. (양쪽 끝값의 0)
int infcmp(infinite* first, infinite* second) {
	// 정수부 비교
	int fsizeL = rtn_sizeL(first->left);
	int ssizeL = rtn_sizeL(second->left);
	// 정수부 존재 시 비교
	if(fsizeL != 0 || ssizeL != 0) {
		if(fsizeL > ssizeL) return 1;
		else if(fsizeL < ssizeL) return -1;
		else if(fsizeL == ssizeL) {
			for(int i = fsizeL; i >= 1; i--) { // fsizeL = ssizeL
				int fdataL = rtn_dataL(first->left, i);
				int sdataL = rtn_dataL(second->left, i);
				if(fdataL > sdataL) return 1;
				else if(fdataL < sdataL) return -1;
			}
		}
	}
	// 실수부 비교
	int fsizeR = rtn_sizeR(first->right);
	int ssizeR = rtn_sizeR(second->right);
	for(int i = 1; i <= MIN(fsizeR, ssizeR); i++) {
		int fdataR = rtn_dataR(first->right, i);
		int sdataR = rtn_dataR(second->right, i);
		if(fdataR > sdataR) return 1;
		else if(fdataR < sdataR) return -1;
	}
	if(fsizeR == ssizeR) return 0;
	else if(fsizeR > ssizeR) return 1;
	else if(fsizeR < ssizeR) return -1;
}

// cln_dataInf() needs

/*
// testing function main
int main() {
	infinite *inf;
	char* input = "4321012345678987654321.9876543212345678901234";
	printf("\nInput is %s\n", input);
	inf = initialize(input);
	

	free부분
	numSet* set = inf->right;
	while(isEndR(set) == 0) {
		numSet* temp = set;
		set = set->right;
		free(temp);
	} free(set);

	set = inf->left;
	while(isEndL(set) == 0) {
		numSet* temp = set;
		set = set->left;
		free(temp);
	} free(set);
	


	printSetL(inf->left);
	printf(".");
	printSetR(inf->right);
	printf("\nfunction test.\n");
	printf("left size:%d right size:%d\n", rtn_sizeL(inf->left), rtn_sizeR(inf->right));
	chg_dataL(&(inf->left), 3, 200000);
	printSetL(inf->left);
	printf(".");
	printSetR(inf->right);
	printf("\n\n%d\n", rtn_topR(inf->right));
	printInfinite(inf);
	return 0;
}
*/
