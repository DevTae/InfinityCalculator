/* outputProcess.c */
#include <stdio.h>

void printList(int* expr) {
//	for(int i = 0; *(expr+i) != '\0'; i++) {
	for(int i = 0; i < 5; i++) {
		printf("%c", *(expr+i));
	}
}
