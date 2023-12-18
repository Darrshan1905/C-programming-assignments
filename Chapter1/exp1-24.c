#include<stdio.h>
#include<stdlib.h>

#define MAX 100

int top = -1;
char stack[MAX];

void push(char c) {
	if(top + 1 > 100) {
		printf("Stack overflow");
	}
	else {
		stack[++top] = c;
	}
}

void pop() {
	if(top <= -1) {
		printf("Stack underflow");
	}
	else {
		top--;
	}
}

int main() {
	int c;

	while((c = getchar()) != EOF) {
		if(c == '(' || c == '[' || c == '{') {
			push(c);
		}
		else if(c == ')') {
			if(stack[top] != '(') {
				printf("[Error]:Parantheses mismatch\n");
				exit(0);
			}
			else {
				pop();
			}
		}
		else if(c == ']') {
			if(stack[top] != '[') {
				printf("[Error]:Brackets mismatch\n");
				exit(0);
			}
			else {
				pop();
			}
		}
		else if(c == '}') {
			if(stack[top] != '{') {
				printf("[Error]:Brackets mismatch\n");
				exit(0);
			}
			else {
				pop();
			}
		}
		else if(c == '\'' || c == '"') {
			int d;
			while((d = getchar()) != EOF && d != c) {
				continue;
			}
			if(d == EOF) {
				printf("No closing quotes\n");
				exit(0);
			}
		}
	}
	if(top == -1)
		printf("Valid...\n");
	else
		printf("Invalid!!!\n");
}
