#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#define INSERT_NUMBER 1
#define INSERT_OPERATOR 2

// return smaller pointer
char* rtn_smlP(char* a, char* b) {
	if(a == NULL) {
		if(b == NULL) {
			return NULL;
		} else {
			return b;
		}
	} else {
		if(b == NULL) {
			return a;
		} else {
			if(a < b) {
				return a;
			} else {
				return b;
			}
		}
	}
}

// return minimum of pointer
char* rtn_minP(char* a, char* b, char* c, char* d, char* e) {
	return rtn_smlP(a, rtn_smlP(rtn_smlP(b, c), rtn_smlP(d, e)));
}

char* toPostFix(char *elem) {
	//, char oper, int arrSize, int mode) {
	/*static char* store;
	static int index;
	if(mode == 1) { // First Initialize Mode
		store = (char*)malloc(sizeof(char)*(arrSize+1));
		index = 0;
	} else if(mode == 0) { // Return char* mode
		return store;
	} else if(mode == 2) { 
	}
	for(int i = 0; i < size; i++) {
		*(store + index++) = *(elem + i);
	}*/
	printf("input:%s\n", elem);
	// 여기서 다른 문자들어오면 ㅗ하는 예외처리 
	/*static char* store; // 연산자 postFix 로 변환한 식 저장 받을거임 
	// postfix 저장할거 메모리할당
	if(store == NULL) store = (char*)malloc(sizeof(char) * size);
	// 연산자 스택 
	static Stack *operator = NULL;
	if (elem이 연산자이면)
		// 연산자 우선순위에 따라 작동이 달라짐. 
		1. operator에 (int)elem 추가
		2. store 에 elem 문자 추가 
	else
		store에 숫자문자열 추가 (concat 사용)*/
}



// add subject minus function 에서 isMinus 변수의 설정에 따라 계산 유도할 수 있게 해야한다. 

// split string (user define function)
// expr = 원본 Array 
// cpyArr = 원본을 복사, strtok 되는 변수
// strtok 특징
// 1. 첫 char가 delimeter 인 경우 뒤의 문자열을 출력하는데, 뒤의 문자열에서 delimeter가 있는 경우 출력을 멈춤.
// 1.1 이 경우에는 strtok를 했을 때, 항상 delimeter 이후의 char*를 반환함. 주의 요망. 
// 2. char가 첫 번째에 있지 않는 경우에,  delimeter 이전까지의 string을 출력함.
// -> strchr와 pin의 주솟값이 일치하는 경우에는 continue를 해야 한다. 
void strsplit_udf(char* expr, int arrSize) {
	char* cpyArr = (char*)malloc(sizeof(char)*(arrSize+1));
	strcpy(cpyArr, expr);
	char* pin = expr;
	char* startPin = pin;
	// expr의 strchr 함수 시작점을 pin 이라고 지정함.
	char* add = strchr(pin, '+');
	char* subtract = strchr(pin, '-');
	char* multiply = strchr(pin, '*');
	char* parentheseL = strchr(pin, '(');
	char* parentheseR = strchr(pin, ')');
	// 가장 가까운 연산자 찾기 
	char* minP = rtn_minP(add, subtract, multiply, parentheseL, parentheseR);
	if(minP == NULL) { // 연산자가 없는 경우 
		toPostFix(expr);
		free(cpyArr);
		return;
	} else { // 연산자가 최소 한 개 이상일 경우 
		if (pin == minP) { // 첫 번째 인덱스에서부터 연산자가 나오는 경우 
			int index = 0;
			if(*pin == '+' || *pin == '-' || *pin == '(') {
				if(*pin != '(') printf("0");
				printf("%c", *pin); // 출력, 연산자 옵션 만들어서 toPostFix 보내주기.
				pin += (size_t) 1;
				add = strchr(pin, '+');
				subtract = strchr(pin, '-');
				multiply = strchr(pin, '*');
				parentheseL = strchr(pin, '(');
				parentheseR = strchr(pin, ')');
				// 가장 가까운 연산자 찾기 
				minP = rtn_minP(add, subtract, multiply, parentheseL, parentheseR); //.
				if(pin != minP) {
					char oper = *minP;
					char* operP = &oper;
					cpyArr = strtok(expr + ++index, operP);
					toPostFix(cpyArr);
					printf("%c", oper);
				}
			} else {
				printf("입력 오류!");
				return;
			}
			while(minP == pin) {
				printf("%c", *minP); // ( 출력, 연산자 옵션 만들어서 toPostFix 보내주기. 
				index++;
				pin += (size_t) 1;
				add = strchr(pin, '+');
				subtract = strchr(pin, '-');
				multiply = strchr(pin, '*');
				parentheseL = strchr(pin, '(');
				parentheseR = strchr(pin, ')');
				// 가장 가까운 연산자 찾기 
				minP = rtn_minP(add, subtract, multiply, parentheseL, parentheseR);
				if(pin != minP) {
					char oper = *minP;
					char* operP = &oper;
					cpyArr = strtok(expr+index, operP);
					toPostFix(cpyArr);
					printf("%c", oper);
					break;
				}
			}

		} else { 
			char oper = *minP;
			char* operP = &oper;
			cpyArr = strtok(expr, operP);
			toPostFix(cpyArr);
			printf("%c", oper);
		}
		while(1) { // 포인터 변수를 array에 담는 방법은.. 
			pin += (size_t)(minP - pin + 1);
			if(((size_t)pin - (size_t)startPin) / sizeof(char) > arrSize) break;
			add = strchr(pin, '+');
			subtract = strchr(pin, '-');
			multiply = strchr(pin, '*');
			parentheseL = strchr(pin, '(');
			parentheseR = strchr(pin, ')');
			minP = rtn_minP(add, subtract, multiply, parentheseL, parentheseR);
			// 자르기 전에 연산자 빼놓기
			if(pin == minP) {
				if(*pin == '+' || *pin == '-' || *pin == '*' ||
						*pin == '(') {
					printf("%c", *pin); // *pin 출력, 연산자 옵션 만들어서 toPostFix 보내주기.
					continue;
				} else  {
					printf("입력 오류!");
					return;
				}
			}
			char oper;
			if(minP != NULL) oper = *minP;
			else oper = '=';
			char* operP = &oper;
			cpyArr = strtok(NULL, operP);
			toPostFix(cpyArr); // isdigit 필요. 
			printf("%c", oper);
		}
		free(startPin);
	}
	
}

void strsplit_udf2(char* expr) {
	int arrSize = strlen(expr);
	char* newNum = (char*)malloc(sizeof(char)*(arrSize+1));
	newNum[0] = '\0';
	int isFirstOfNum = 1, index;
	for(int i = 0; i < arrSize; i++) {
		if(expr[i] == '+' || expr[i] == '-' ||
				expr[i] == '*' || expr[i] == '(' || expr[i] == ')') {
			if(newNum[0] == '\0') isFirstOfNum = 1;
			else {
				newNum[index] = '\0';
				toPostFix(newNum);
				index = 0;
			}
			char oper = expr[i];
			char* toTransfer = &oper;
			toPostFix(toTransfer);
		} else if(isFirstOfNum == 1) {
			index = 0;
			isFirstOfNum = 0;
			newNum[index++] = expr[i];
		} else {
			newNum[index++] = expr[i];
		}
	}
	newNum[index] = '\0';
	toPostFix(newNum);
}

// entry point
int main(void) {
	char* expr = recv_expr();
	printf("%s\n", recv_expr());
	clock_t start = clock();
	strsplit_udf(expr, strlen(expr));
	clock_t middle = clock();
	expr = recv_expr();
	clock_t middle2 = clock();
	strsplit_udf2(expr);
	clock_t end = clock();
	// 비슷한 부분 찾아서 그 순간을 기점으로 위아래 나누자 ㅋ
	printf("strlen(expr) = %d\n", (int)strlen(expr));
	printf("\n\n\nresult : strsplit_udf(%0.5fs)\nstrsplit_udf2(%0.5fs)\n"
			,(float)(middle-start)/CLOCKS_PER_SEC, (float)(end-middle2)/CLOCKS_PER_SEC);
	//printf("%s", expr);
	//free(expr);
	return 0;
}
