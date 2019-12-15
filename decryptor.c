/* decryptor.c */
#include "calculator.h"

// stackInf : as like stack, but have infinite* data but no int value.
stackInf* new_node_sInf(infinite* data) { // strtok 원리때문에 malloc x
	stackInf *stack = (stackInf*)malloc(sizeof(stackInf));
	stack->data = data;
	stack->next = NULL;
	return stack;
}

void push_back_sInf(stackInf **stack, infinite* data) {
	stackInf* new = new_node_sInf(data);
	new->next = *stack;
	(*stack) = new;
}

infinite* pop_back_sInf(stackInf **stack) {
	infinite* data = (*stack)->data;
	stackInf* temp = *stack;
	(*stack) = (*stack)->next;
	//free(temp); 그냥 free해버리면 안되는 구조라서 이렇게 함.
	return data;
}

int isEmpty_sInf(stackInf *stack) {
	if(stack == NULL)
		return 1;
	else return 0;
}

int getSize_sInf(stackInf *stack) {
	int c = 0;
	while(!isEmpty_sInf(stack)) {
		c++;
		stack = stack->next;
	}
	return c;
}

void print_sInf(stackInf *stack) { // test function
	while(isEmpty_sInf(stack) == 0) {
		printInfinite(stack->data);
		stack = stack-> next;
	}
	printf("\n");
}
// stackInf //

/*
infinite* (*getPtr(const char opCode))(infinite*, infinite*) {
	if(opCode == '+') {
		return &add;
	} else if(opCode == '-') {
		return &subtract;
	} else if(opCode == '*') {
		return &multiply;
	}
}*/

infinite* calculateManager(infinite* first, 
		infinite* second, char opCode) {
	infinite* newinf = NULL;
	int fminus = first->isMinus;
	int sminus = second->isMinus;
	int value_of_cmp = infcmp(first, second);
	if(opCode == '+') {
		if(fminus == sminus) { // 부호 같다면
			newinf = add(first, second);
			newinf->isMinus = fminus; // fminus == sminus
		} else if(value_of_cmp == 1) { // first > second
			newinf = subtract(first, second);
			if(fminus == 1) {
				newinf->isMinus = 1;
			} else if(sminus == 1) {
				newinf->isMinus = 0;
			}
		} else if(value_of_cmp == -1) { // first < second
			newinf = subtract(second, first);
			if(sminus == 1) {
				newinf->isMinus = 1;
			} else if(fminus == 1) {
				newinf->isMinus = 0;
			}
		} else {
			newinf = initialize("0"); // 부호 다르고 값 같으면 0
		}
	} else if(opCode == '-') {
		if(second->isMinus == 1)
			second->isMinus = 0;
		else second->isMinus = 1;
		newinf = calculateManager(first, second, '+');
	} else if(opCode == '*') {
		newinf = multiply(first, second);
		if(fminus == sminus)
			newinf->isMinus = 0;
		else newinf->isMinus = 1;
	} else {
		printf("invalid operator.\n");
		exit(0);
	}
	// freeing two garbage.
	return newinf;
}


// decrypt 함수에서 분해된 원소들을 하나씩 보내서 계산해주는 함수
// naming -> calculating box
infinite* calcul_box(char* elem, int option) {
	static stackInf* numbers; // free
	char operator;
	// format : first operator second
	infinite* first = NULL;
	infinite* second = NULL;
	if((option & INSERT_FIRST) == INSERT_FIRST) {
		numbers = NULL; // null define.
	} else if((option & INSERT_END) == INSERT_END) {
		infinite* final_data = numbers->data;
		free(numbers);
		return final_data;
	} else if((option & INSERT_NUMBER) == INSERT_NUMBER) {
		push_back_sInf(&numbers, initialize(elem));
	} else if((option & INSERT_OPERATOR) == INSERT_OPERATOR) {
		operator = *elem;
		second = pop_back_sInf(&numbers);
		first = pop_back_sInf(&numbers);
		push_back_sInf(&numbers, 
				calculateManager(first, second, operator));
		freeInfinite(&first);
		freeInfinite(&second);
	} else if((option & INSERT_0REVERSE) == INSERT_0REVERSE) {
		// 0을 집어넣고 top 과 top->next 의 값을 변경한다.
		infinite* top = numbers->data;
		infinite* zero = initialize("0");
		numbers->data = zero;
		push_back_sInf(&numbers, top);
	}
}

infinite* decrypt(char* postfix) {
	calcul_box(NULL, INSERT_FIRST);
	char* elem = strtok(postfix, " ");
	int isMinus = 1; // 음수인지 확인 (음수를 단순 연산으로 처리)
	// unary +, -
	// binary +, -, *
		// 음수 '-'가 연산되는 방법
		// 1. 원소 한 개 있을 때
		// 2. 바로 옆에 ( 와 숫자 하나 있을 때.	
	// isMinus 상황 : binary unary 판단 (infinite의 isMinus랑 다름)
	// isMinus = 2 : Unary 표현 대기 중, 연산자 안오면 0으로 초기화
	// isMinus = 1 : 식 맨 처음이거나 괄호 시작할 때. 숫자 나오면 2로 변환
	// isMinus = 0 : 평소
	while(elem != NULL) {
		if(*elem == '+' || *elem == '-') {
			if(isMinus == 2)
				calcul_box(NULL, INSERT_0REVERSE);
			calcul_box(elem, INSERT_OPERATOR);
		} else if(*elem == '(') isMinus = 1;
		else if(*elem == '*') {
			isMinus = 0;
			calcul_box(elem, INSERT_OPERATOR);
		} else if(*elem != ')') { // number
			if(isMinus == 1) isMinus = 2;
			else isMinus = 0;
			calcul_box(elem, INSERT_NUMBER);
		}
		elem = strtok(NULL, " ");
	}
	return calcul_box(NULL, INSERT_END);
}

// test function of stackInf
/*
int main(void) {
	stackInf* a = NULL;
	printf("a = NULL\n");
	push_back_inf(&a, initialize("9.6"));
	push_back_inf(&a, initialize("66.3"));
	push_back_inf(&a, initialize("656"));
	print_inf(a);
	printf("\nsize: %d\n", getSize_inf(a));
	pop_back_inf(&a);
	printf("\nsize: %d\n", getSize_inf(a));
	print_inf(a);
	return 0;
}*/
