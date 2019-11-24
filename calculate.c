#include "calculator.h"

int intlen(int data) {
	int pow_10[10] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
					100000000, 1000000000 };
	for(int i = 9; i >= 0; i--) {
		//if(data >= math_pow(10, i))
		if(data >= pow_10[i])
			return i+1;
	}
	return 1; // 0.00000001 
}

int rtn_cardinal(infinite* inf) { // return cardinality
	int cardinal;
	if(rtn_sizeL(inf->left) == 1 && rtn_dataL(inf->left, 1) == 0) {
		// 어디가 기점인지 확인
		for(int i = 1; ; i++) {
			int data = rtn_dataR(inf->right, i);
			if(data != 0) {
				cardinal = - (9 - intlen(data) + 1) - 9 * (i-1);
				break;
			}
		}
	} else {
		cardinal = 9 * (rtn_sizeL(inf->left) - 1) + intlen(rtn_topL(inf->left));
	}
	return cardinal;
}

infinite* multiply(infinite* a, infinite* b) {
	// move to rtn_cardinal
	int aCardinal = rtn_cardinal(a);
	int bCardinal = rtn_cardinal(b);
	int totalCardinal = aCardinal + bCardinal;
	
	// 기수를 기점, 오른쪽기준 나열 -> aarr barr
	
	// 2차원 배열 생성, calloc 사용, arr[barr+3][aarr+barr-1] 생성 0으로 초기화
	// use malloc and redefine 0, or use calloc.
	
	// for문 사용해서 배열 원소에 접근 Hint. [2+n][n+m-1]
	
	// / 10 or % 10 사용해서 제대로 접근해라 ('+=' 사용)
	
	// 마지막에 같은 열 모두 더해줌.

	// 마지막 행을 char* 으로 만듬. -> result
	
	// substring(result, 0, totalCardinal) + "." substring(result, totalCardinal, strlen(result))

	// initialize 함수에 위의 값을 집어넣어줌.

	// return initialize(newInf);
	
	// 후에, input 메소드 수정 요구. in-postfix에서 한 숫자씩 받는 것이 아닌, 여러 숫자를 동시에 받을 수 있도록 수정해야함. char* 형으로 만들면 될듯. strcat 사용!
}

// test with main function!
int main(void) {
	int a = 224124124;
	printf("intlen : %d\n",intlen(a));
	return 0;
}
