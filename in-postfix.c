/* in-postfix.c */
// we could distinguish operator with expression.
#include "calculator.h"

char* storeExpr(char *elem, const int option, const int size) {
	static Stack *operator;
	static char *result;
	if((option & INSERT_FIRST) == INSERT_FIRST) {
		result = (char*)malloc(sizeof(char) * (size+1));
		*result = '\0';
	}
	if((option & INSERT_END) == INSERT_END) {
		while(isEmpty(operator) == 0) {
			strcat(result, " ");
			char* tmp = (char*)malloc(sizeof(char) * 2);
			*tmp = (char)pop_back(&operator);
			*(tmp+1) = '\0';
			strcat(result, tmp);
			free(tmp);
		}
		return result;
	} // END 옵션 부르고 사용 완료하면, free 해줘야 한다.

	if((option & INSERT_OPERATOR) == INSERT_OPERATOR) {
		switch(*elem) {
			case '+':
				while(operator != NULL
					&&(operator->data == (int)'+'
					|| operator->data == (int)'-'
					|| operator->data == (int)'*')) {
					strcat(result, " ");
					char* tmp = (char*)malloc(sizeof(char) * 2);
					*tmp = (char)operator->data;
					*(tmp+1) = '\0';
					strcat(result, tmp);
					free(tmp);
					pop_back(&operator);
				}
				push_back(&operator, (int)*elem);
				break;
			case '-':
				while(operator != NULL
					&&(operator->data == (int)'+'
					|| operator->data == (int)'-'
					|| operator->data == (int)'*')) {
					strcat(result, " ");
					char* tmp = (char*)malloc(sizeof(char) * 2);
					*tmp = (char)operator->data;
					*(tmp+1) = '\0';
					strcat(result, tmp);
					free(tmp);
					pop_back(&operator);
				}
				push_back(&operator, (int)*elem);
				break;
			case '*':
				while(operator != NULL && operator->data == (int)'*') {
					strcat(result, " ");
					char* tmp = (char*)malloc(sizeof(char) * 2);
					*tmp = (char)operator->data;
					*(tmp+1) = '\0';
					strcat(result, tmp);
					free(tmp);
					pop_back(&operator);
				}
				push_back(&operator, (int)*elem);
				break;
			case '(':
				push_back(&operator, (int)*elem);
				break;
			case ')':
				while(operator->data != '(') {
					strcat(result, " ");
					char* tmp = (char*)malloc(sizeof(char) * 2);
					*tmp = (char)operator->data;
					*(tmp+1) = '\0';
					strcat(result, tmp);
					free(tmp);
					pop_back(&operator);
				}
				pop_back(&operator); // garbage delete
				break;
			default:
				printf("You conveyed incorrect sentence with other operators.\n");
				exit(0);
		}
	} else if((option & INSERT_NUMBER) == INSERT_NUMBER) {
		strcat(result, elem);
	}
}

char* toPostFix(char* expr) {
	int size = 3 * strlen(expr); // 
	char data;
	int isFirstDigit = 1; // 숫자의 첫 자리인지 확인
	int existPoint = 0; // 점 두개 발견할 시 오류 처리
	storeExpr(NULL, INSERT_FIRST, size); // Initialize
	char *tmp = (char*)malloc(sizeof(char) * 2);
	*(tmp+1) = '\0';
	for(int i = 0; *(expr+i) != '\0'; i++) {
		data = *(expr+i);
		if(data == '+' || data == '-' || data == '*'
		|| data == '(' || data == ')') {
			*tmp = ' ';
			storeExpr(tmp, INSERT_NUMBER, size); // strtok delimeter
			*tmp = data;
			storeExpr(tmp, INSERT_OPERATOR, size);
			isFirstDigit = 1;
			existPoint = 0;
		} else if(data >= '0' && data <= '9' || data == '.') {
			if(isFirstDigit) {
				*tmp = ' ';
				storeExpr(tmp, INSERT_NUMBER, size); // strtok delimeter
			}
			if(existPoint == 1 && data == '.') {
				printf("숫자 한 개에 점(.)이 두 번 이상 나왔습니다. 입력에 문제가 생겨 종료합니다.\n");
				exit(0);
			}
			if(data == '.') existPoint = 1;
			*tmp = data;
			storeExpr(tmp, INSERT_NUMBER, size);
			isFirstDigit = 0;
		} else if(data != '\n') {
			printf("+, -, *, (, ), 1~9 이외의 문자를 입력했습니다. 종료합니다.\n");
			exit(0);
		}
	}
	free(tmp);
	return storeExpr(NULL, INSERT_END, size);
}
