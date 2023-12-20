#include<stdio.h>

#define MAXVAL 100

int sp = 0;
double stack[MAXVAL];

void push(double f) {
	if(sp <  MAXVAL)
		stack[sp++] = f;
        else
		printf("Stack overflow\n");	
}

double pop() {
	double c;
	if(sp > 0)
		return c = stack[--sp];
	else {
		printf("Stack underflow\n");
		return -1;

	}
}

double printTop() {
	if(sp > 0)
		return stack[sp - 1];
	else 
		printf("Stack underflow");
}

void swapTopTwo() {
	if(sp > 1) {
		stack[sp - 1] = stack[sp - 1] + stack[sp - 2];
		stack[sp - 2] = stack[sp - 1] - stack[sp - 2];
		stack[sp - 1] = stack[sp - 1] - stack[sp - 2];	

		printf("\nNow the top 2 elemnets are : %lf %lf\n", stack[sp - 1], stack[sp - 2]);
	}
	else {
		printf("Stack underflow");
	}
}

void duplicate() {
	if(sp < MAXVAL) {
		stack[sp++] = stack[sp - 1];
	}
}

void clearStack() {
	sp = 0;
	printf("\nStack cleared\n");
}

int main() {
	push(4);
	push(3);
	push(2);
	push(1);

	printf("Current stack is 1 2 3 4\n");

	printf("Printing the top element of the stack:");
	printf("%lf\n", printTop());

	printf("Swapping the top 2 elements of the stack:");
	swapTopTwo();

	printf("Duplicating the top elements of the stack: ");
	duplicate();

	printf("Printing the top element of the stack:");
        printf("%lf\n", printTop());

	printf("Clearing the stack:");
	clearStack();
	pop();
}
