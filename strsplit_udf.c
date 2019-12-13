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
	// ���⼭ �ٸ� ���ڵ����� ���ϴ� ����ó�� 
	/*static char* store; // ������ postFix �� ��ȯ�� �� ���� �������� 
	// postfix �����Ұ� �޸��Ҵ�
	if(store == NULL) store = (char*)malloc(sizeof(char) * size);
	// ������ ���� 
	static Stack *operator = NULL;
	if (elem�� �������̸�)
		// ������ �켱������ ���� �۵��� �޶���. 
		1. operator�� (int)elem �߰�
		2. store �� elem ���� �߰� 
	else
		store�� ���ڹ��ڿ� �߰� (concat ���)*/
}



// add subject minus function ���� isMinus ������ ������ ���� ��� ������ �� �ְ� �ؾ��Ѵ�. 

// split string (user define function)
// expr = ���� Array 
// cpyArr = ������ ����, strtok �Ǵ� ����
// strtok Ư¡
// 1. ù char�� delimeter �� ��� ���� ���ڿ��� ����ϴµ�, ���� ���ڿ����� delimeter�� �ִ� ��� ����� ����.
// 1.1 �� ��쿡�� strtok�� ���� ��, �׻� delimeter ������ char*�� ��ȯ��. ���� ���. 
// 2. char�� ù ��°�� ���� �ʴ� ��쿡,  delimeter ���������� string�� �����.
// -> strchr�� pin�� �ּڰ��� ��ġ�ϴ� ��쿡�� continue�� �ؾ� �Ѵ�. 
void strsplit_udf(char* expr, int arrSize) {
	char* cpyArr = (char*)malloc(sizeof(char)*(arrSize+1));
	strcpy(cpyArr, expr);
	char* pin = expr;
	char* startPin = pin;
	// expr�� strchr �Լ� �������� pin �̶�� ������.
	char* add = strchr(pin, '+');
	char* subtract = strchr(pin, '-');
	char* multiply = strchr(pin, '*');
	char* parentheseL = strchr(pin, '(');
	char* parentheseR = strchr(pin, ')');
	// ���� ����� ������ ã�� 
	char* minP = rtn_minP(add, subtract, multiply, parentheseL, parentheseR);
	if(minP == NULL) { // �����ڰ� ���� ��� 
		toPostFix(expr);
		free(cpyArr);
		return;
	} else { // �����ڰ� �ּ� �� �� �̻��� ��� 
		if (pin == minP) { // ù ��° �ε����������� �����ڰ� ������ ��� 
			int index = 0;
			if(*pin == '+' || *pin == '-' || *pin == '(') {
				if(*pin != '(') printf("0");
				printf("%c", *pin); // ���, ������ �ɼ� ���� toPostFix �����ֱ�.
				pin += (size_t) 1;
				add = strchr(pin, '+');
				subtract = strchr(pin, '-');
				multiply = strchr(pin, '*');
				parentheseL = strchr(pin, '(');
				parentheseR = strchr(pin, ')');
				// ���� ����� ������ ã�� 
				minP = rtn_minP(add, subtract, multiply, parentheseL, parentheseR); //.
				if(pin != minP) {
					char oper = *minP;
					char* operP = &oper;
					cpyArr = strtok(expr + ++index, operP);
					toPostFix(cpyArr);
					printf("%c", oper);
				}
			} else {
				printf("�Է� ����!");
				return;
			}
			while(minP == pin) {
				printf("%c", *minP); // ( ���, ������ �ɼ� ���� toPostFix �����ֱ�. 
				index++;
				pin += (size_t) 1;
				add = strchr(pin, '+');
				subtract = strchr(pin, '-');
				multiply = strchr(pin, '*');
				parentheseL = strchr(pin, '(');
				parentheseR = strchr(pin, ')');
				// ���� ����� ������ ã�� 
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
		while(1) { // ������ ������ array�� ��� �����.. 
			pin += (size_t)(minP - pin + 1);
			if(((size_t)pin - (size_t)startPin) / sizeof(char) > arrSize) break;
			add = strchr(pin, '+');
			subtract = strchr(pin, '-');
			multiply = strchr(pin, '*');
			parentheseL = strchr(pin, '(');
			parentheseR = strchr(pin, ')');
			minP = rtn_minP(add, subtract, multiply, parentheseL, parentheseR);
			// �ڸ��� ���� ������ ������
			if(pin == minP) {
				if(*pin == '+' || *pin == '-' || *pin == '*' ||
						*pin == '(') {
					printf("%c", *pin); // *pin ���, ������ �ɼ� ���� toPostFix �����ֱ�.
					continue;
				} else  {
					printf("�Է� ����!");
					return;
				}
			}
			char oper;
			if(minP != NULL) oper = *minP;
			else oper = '=';
			char* operP = &oper;
			cpyArr = strtok(NULL, operP);
			toPostFix(cpyArr); // isdigit �ʿ�. 
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
	// ����� �κ� ã�Ƽ� �� ������ �������� ���Ʒ� ������ ��
	printf("strlen(expr) = %d\n", (int)strlen(expr));
	printf("\n\n\nresult : strsplit_udf(%0.5fs)\nstrsplit_udf2(%0.5fs)\n"
			,(float)(middle-start)/CLOCKS_PER_SEC, (float)(end-middle2)/CLOCKS_PER_SEC);
	//printf("%s", expr);
	//free(expr);
	return 0;
}
