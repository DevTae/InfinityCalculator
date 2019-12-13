/* decryptor.c */
/*#include "calculator.h"

Infinite* (*opts)(infinite*, infinite*) {
	// 함수포인터 복습 및 사용법 취득 ㅇㅋ?
}

Infinite* decrypt(char* postfix) {
	
}*/

int* add(int* a, int* b) {
	printf("add\n");
	int *new;
	*new = *a + *b;
	return new;
}

int subtract(int* a, int* b) {
	printf("subtract\n");
	int *new;
	*new = *a - *b;
	return new;
}

int* (*opts)(int*, int*) {
	// 함수포인터 복습 및 사용법 취득 ㅇㅋ?
}

int* decrypt(char* postfix) {
	
}

int main(void) {
	return 0;
}

