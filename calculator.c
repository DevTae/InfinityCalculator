/* calculator.c */
// System Programming IC-PBL 6조
#include "calculator.h"
#include <time.h>

//Receive expression
char* recv_expr(char *fname) {
	FILE* ifp = fopen(strcat(fname, ".txt"), "r");
	char* expr = NULL;
	char c;
	int size = 0;
	while(fscanf(ifp, "%c", &c) == 1) size++;
	expr = (char*)malloc(sizeof(char) * (size + 1));
	rewind(ifp);
	// 파일 읽었던 기록 지우고 다시 처음으로. 
	int i = 0;
	while(fscanf(ifp, "%c", &c) == 1) {
		*(expr + i++) = c;
	}
	*(expr + i) = '\0';
	return expr;
}

long long getElapsedTime(unsigned int nFlag)
{
	const long long NANOS = 1000000000LL;
	static struct timespec startTS, endTS;
	static long long retDiff = 0;

	if (nFlag == 0) {
		retDiff = 0;
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTS) == -1) {
			printf("Failed to call clock_gettime\n");
		}
	}
	else {
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTS) == -1) {
			printf("Failed to call clock_gettime\n");
		}
		retDiff = NANOS * (endTS.tv_sec - startTS.tv_sec) + (endTS.tv_nsec - startTS.tv_nsec);
 	}

	return retDiff;
}

/**
 * Entry Point
 */
int main(const int argc, char **argv)
{
	getElapsedTime(0);
	
	if(argc != 2) {
		printf("Argument wouldn't reflected. (Reason: Needing of argument count is 2.)\n");
		exit(0);
	}
	
	// Reading expression will be calculated.
	char* expr = recv_expr(argv[1]);
	printf("%s", expr);
	
	// Transform expr to PostFix Expression.
	char* postfix = toPostFix(expr);
	printf("%s\n", postfix);
	
	// Decrpyt the expression transformed to postfix.
//	Infinite* result = decrypt(postfix);
	// printsetL printsetR 구현 및 사용
	
	//cln_dataL, cln_dataR 구현 및 사용
	free(expr);
	free(postfix);

	printf("Elapsed Time: %lld\n", getElapsedTime(1));

	return 0;
}
