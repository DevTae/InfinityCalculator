// calculate.c
#include "calculator.h"
#include <string.h>

// 더하기 함수
infinite* add(infinite* a, infinite* b) {
	char* trash = "000000000";
	char* store = "";
	int aSizeL = rtn_sizeL(a->left);
	int bSizeL = rtn_sizeL(b->left);
	int aSizeR = rtn_sizeR(a->right);
	int bSizeR = rtn_sizeR(b->right);
	int sizeL = MAX(aSizeL, bSizeL) + 1;
	int sizeR = MAX(aSizeR, bSizeR);
	int i = 0;
	while(i++ < sizeL) {
		strcat(store, trash);
	}
	strcat(store, ".");
	i = 0;
	while(i++ < sizeR) {
		strcat(store, trash);
	}
	infinite* result = initialize(store);

	// 더하기
	for(int j = 1; j <= sizeL; j++) {
		int data1 = 0, data2 = 0;
		if(j <= aSizeL)
			data1 = rtn_dataL(a->left, j);
		if(j <= bSizeL)
			data2 = rtn_dataL(b->left, j);
		chg_dataL(&(result->left), j, data1 + data2);
	}
	for(int j = 1; j < sizeR; j++) {
		int data1 = 0, data2 = 0;
		if(j <= aSizeR)
			data1 = rtn_dataR(a->right, j);
		if(j <= bSizeR)
			data2 = rtn_dataR(b->right, j);	
		chg_dataR(&(result->right), j, data1 + data2);
	}

	//오버플로우 올림수 올려주기
	for(int n = sizeR; n > 0; n--) {
		if(rtn_dataR(result->right, n) / 1000000000 != 0) {
			if(n == 1) {
				chg_dataL(&(result->left), 1, rtn_dataL(result->left, 1) + 1);
			} else {
				chg_dataR(&(result->right), n, rtn_dataR(result->right, n) % 1000000000);
				chg_dataR(&(result->right), n - 1, rtn_dataR(result->right, n - 1) + 1);
			}
		}
	}
	for(int h = 1; h < sizeL; h++) {
		if(rtn_dataL(result->left, h) / 1000000000 != 0){
			chg_dataL(&(result->left), h, rtn_dataL(result->left, h) % 1000000000);
			chg_dataL(&(result->left), h + 1, rtn_dataL(result->left, h + 1) + 1);
		}
	}

	//더하기 끝난 infinite* 반환하기
	return result;
}


// 빼기 함수

infinite* subtract(infinite* a, infinite* b) {
    char* trash = "000000000";
    char* store = "";
    int aSizeL = rtn_sizeL(a->left);
	int bSizeL = rtn_sizeL(b->left);
	int aSizeR = rtn_sizeR(a->right);
	int bSizeR = rtn_sizeR(b->right);
	int sizeL = MAX(aSizeL, bSizeL);
    int sizeR = MAX(aSizeR, bSizeR);
    int i = 0;
    while(i++ < sizeL) {
        strcat(store, trash);
    }
    strcat(store, ".");
    i = 0;
    while(i++ < sizeR) {
        strcat(store, trash);
    }
    
	infinite* result = initialize(store);
    for(int j = 1; j <= sizeL; j++) {
        int data1 = 0, data2 = 0;
		if(j <= aSizeL)
			data1 = rtn_dataL(a->left, j);
		if(j <= bSizeL)
			data2 = rtn_dataL(b->left, j);	
        chg_dataL(&(result->left), j, data1 - data2);
    }
    for(int j = 1; j <= sizeR; j++) {
        int data1 = 0, data2 = 0;
		if(j <= aSizeL)
			data1 = rtn_dataR(a->right, j);
		if(j <= bSizeL)
			data2 = rtn_dataR(b->right, j);
        chg_dataR(&(result->right), j, data1 - data2);
    }
    // "R"
    for(int n = sizeR; n > 0; n--) {
        //계산값이 음수이고 n이 1이 아니라면 10억과 n에 있는 수를 더하고 n-- 에 있는수에서 1을 뺀다.
        //계산값이 양수면 아무일 X
        if(rtn_dataR(result->right, n) < 0 && n != 1) {
            chg_dataR(&(result->right), n, rtn_dataR(result->right, n) + 1000000000);
            chg_dataR(&(result->right), n-1, rtn_dataR(result->right, n-1) - 1);
        }
        //n이 1일때 음수면 10억 더하고 L의 1번째에서 -1
        //n이 1일때 양수면 아무일 X
        else if (rtn_dataR(result->right, n) < 0 && n == 1) {
            chg_dataR(&(result->right), 1, rtn_dataR(result->right, n) + 1000000000);
            chg_dataL(&(result->left), 1, rtn_dataL(result->left, 1) - 1);
            }
    }
    // "L"
    for(int h = 1; h <= sizeL; h++) {
        //계산값이 음수일때
        if(rtn_dataL(result->left, h) < 0) {
            chg_dataL(&(result->left), h, rtn_dataL(result->left, h) + 1000000000);
            chg_dataL(&(result->left), h + 1, rtn_dataL(result->left, h + 1) - 1);
        }
    }

	// 총 결과값이 음수가 나오는 경우:
	int topData = rtn_dataL(result->left, sizeL);
	if(topData < 0) {
		result->isMinus = 1;
		chg_dataL(&(result->left), sizeL, -topData);
	} else {
		result->isMinus = 0;
	}
	
	return result;
}

// 곱셈에 필요한 부가적인 함수
int intlen(int data) {
	int pow_10[10] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
					100000000, 1000000000 };
	for(int i = 9; i >= 0; i--) {
		if(data >= pow_10[i])
			return i+1;
	}
	return 1; 
}

void put_toArr(infinite* inf, int ***board, int floor, int arr_col, int cardinal) {
	int pow_10[10] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
						100000000, 1000000000 };
	// left of the point will be initialized at board pointer variable.
	int sizeR = cardinal / -9;
	int sizeL = rtn_sizeL(inf->left);
	if(cardinal < 0) {
		int nowIndex = 0;
		if(rtn_sizeR(inf->right) > 0) {
			nowIndex = 9 * sizeR;
			for(int i = 0; i < sizeR; i++) {
				int data = rtn_dataR(inf->right, i);
				for(int j = 8; j >= 0; j--) {
					*(*(*board+floor) + arr_col-1 - 9*i - j) 
						= data / pow_10[j];
					data %= pow_10[j];
				}
			}
		} // 소수점 왼쪽에 숫자가 존재하면? (cardinal < 0 마찬가지)
		if(inf->left == NULL) return;
		for(int i = 0; i < sizeL; i++) {
			int data = rtn_dataL(inf->left, i+1);
			for(int j = 8; j >= 0; j--) {
				*(*(*board+floor) + arr_col-1 - nowIndex - 9*i - j)
					= data / pow_10[j];
				data %= pow_10[j];
			}
		}
	} else { // cardinal == 0
		for(int i = 0; i < sizeL; i++) {
			int data = rtn_dataL(inf->left, i+1);
			for(int j = 8; j >= 0; j--) {
				*(*(*board+floor) + arr_col-1 - 9*i - j) = data / pow_10[j];
				data %= pow_10[j];
			}
		}
	}

}


// 곱셈 함수
infinite* multiply(infinite* a, infinite* b) {
	int aCardinal = -9 * rtn_sizeR(a->right);
	int bCardinal = -9 * rtn_sizeR(b->right);
	int afterCardinal = aCardinal + bCardinal;
	int aNeedIndex = -aCardinal + 9 * rtn_sizeL(a->left);
	int bNeedIndex = -bCardinal + 9 * rtn_sizeL(b->left);
	int arr_row = 2+bNeedIndex+1;
	int arr_col = aNeedIndex+bNeedIndex-1;
	
	// 둘 중에 하나라도 0이면 0 반환
	// 구현 or not 생각.

	// arr have two dimention array is initialized.
	int **board = (int**)malloc(sizeof(int*) * arr_row);
	for(int i = 0; i < arr_row; i++) {
		*(board+i) = (int*)malloc(sizeof(int) * arr_col);
		memset(*(board+i), 0, arr_row);
	} // use malloc and redefine 0, or use calloc.

	put_toArr(a, &board, 0, arr_col, aCardinal);
	put_toArr(b, &board, 1, arr_col, bCardinal);

	for(int i = 0; i < bNeedIndex; i++) {
		for(int j = 0; j < aNeedIndex; j++) {
			if(*(*(board+0) + arr_col-1 - j) == 0
				|| *(*(board+1) + arr_col-1 - i) == 0) {
				continue;
			}
			*(*(board+2 + i) + arr_col-1 - i - j)
				+= *(*(board+0) + arr_col-1 - j)
				* *(*(board+1) + arr_col-1 - i);
		}
	}

	// Sum of the elements that are same column.
	for(int i = 0; i < arr_col; i++) {
		for(int j = 2; j < arr_row-1; j++) {
			*(*(board + arr_row-1) + i) += *(*(board + j) + i);
		}
	}

	// what beyond the 10, delivery upperside.
	for(int i = arr_col-1; i > 0; i--) {
		if(*(*(board + arr_row-1) + i) / 10 == 0) continue;
		*(*(board + arr_row-1) + i-1) += *(*(board + arr_row-1) + i) / 10;
		*(*(board + arr_row-1) + i) %= 10;
	}
	
	for(int i = 0; i < arr_col; i++)
		printf("%d ", *(*(board+0)+i));
	printf(" * 10^(%d)\n", aCardinal);
	for(int i = 0; i < arr_col; i++)
		printf("%d ", *(*(board+1)+i));
	printf(" * 10^(%d)\n", bCardinal);
	
	for(int i = 0; i < arr_col; i++)
		printf("%d ", *(*(board+arr_row-1)+i));
	printf(" * 10^(%d)\n", aCardinal+bCardinal);

	// make a char* with starting not '0'.
	char expr[100000] = "";
	int isFirst = 1;
	int length = 0;	
	for(int i = 0; i < arr_col; i++) {
		int toEnter = *(*(board + arr_row-1) + i);
		char data[100000] = {(char)(toEnter+48)};
		strcat(expr, data);
		length++;
	}
	
	char tmp[100000];
	char result[100000] = "";
	if(afterCardinal < 0) {
		strcat(result, substring(tmp, expr, 0, arr_col - (-afterCardinal)));
		strcat(result, ".");
		strcat(result, substring(tmp, expr, arr_col - (-afterCardinal), -afterCardinal));
	} else if(afterCardinal == 0) {
		strcat(result, substring(tmp, expr, 0, arr_col));
	}
	printf("%s\n\n", result);
	
	// freeing of the memory allocated.
	for(int i = 0; i < arr_row; i++)
		free(*(board+i));
	free(board); //segmentation fault. x

	infinite* newinf = initialize(result);
	//cln_dataL(&(newinf->left));
	//cln_dataR(&(newinf->right));
	return newinf;
}

// test with main function!
int main(void) {
	infinite* a = initialize("101.1122");
	//printInfinite(a);
	infinite* b = initialize("999.8");
	infinite* c = multiply(a, b);
	c = add(a, b);
	c = subtract(a, b);
	//printInfinite(c);
	return 0;
}
