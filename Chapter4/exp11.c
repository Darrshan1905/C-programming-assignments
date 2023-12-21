#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100
#define NAME 'n'

int sp = 0;
double stack[MAXVAL];

int getop(char[]);
void push(double);
double pop(void);

int main() {
	int type;
	double op2;
	char s[MAXOP];
	double c, d;

	while((type = getop(s)) != EOF) {
		switch(type) {
			case NUMBER:
				push(atof(s));
				printf("Pushed %lf\n", atof(s));
				break;
			case '+':
				c = pop();
			       	d = pop();
				printf("Popped %lf %lf\n", c, d);
				push(c + d);
				break;
			case '*':
                                c = pop();
                                d = pop();
                                printf("Popped %lf %lf\n", c, d);
				push(c * d);
				break;
			case '-':
                                c = pop();
                                d = pop();
                                printf("Popped %lf %lf\n", c, d);
				push(d - c);
                                break;
			case '/':
                                d = pop();
				if(d != 0.0) {
					c = pop();
					push(c / d);
				}
				else
					printf("Error: Division by zero\n");
				printf("Popped %lf %lf", c, d);
				break;
			case '%':
				d = pop();
				if(d != 0.0) {
					c = pop();
					printf("Popped %lf %lf", c, d);
					if(d < 0.0 && c < 0.0) {
                                                c *= -1.0;
                                                d *= -1.0;
                                                push(-1.0 * fmod(c, d));
                                        }
					else if(d < 0.0 || c < 0.0) {
						int f = 0;
						if(c > 0.0) {
							c = c * -1.0;
							d = d * -1.0;
							f = 1;
						}
						while(c < 0.0) {
							c = d + c;
						}
						if(f == 0)
							push(c);
						else
							push(-1.0 * c);
					}
					else {
						push(fmod(c, d));
					}
				}
				else 
					printf("Error: Mod by zero\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("Error: Unknown command \n");
				break;
		}
	}	
}

void push(double f) {
	if(sp < MAXVAL)
		stack[sp++] = f;
	else
		printf("Error: Stack overflow");
}

double pop() {
	if(sp > 0)
		return stack[--sp];
	else {
		printf("Error: Stack underflow");
		return 0.0;
	}
}

int getop(char s[]) {
	int i, c;

	static char prevc = 0;

	if(prevc == 0)
		c = getchar();
	else {
		c = prevc;
		prevc = 0;
	}

	while((s[0] = c) == ' ' || c == '\t')
		c = getchar();
	s[1] = '\0';

	i = 0;

	if(!isdigit(c) && c != '.' && c != '-')
		return c;

	if(c == '-') {
		if(isdigit(c = getchar()) || c == '.')
			s[++i] = c;
		else {
			if(c != EOF)
				prevc = c;
			return '-';
		}
	}
	if(isdigit(c))
		while(isdigit(s[++i] = c = getchar()));

	if(c == '.')
		while(isdigit(s[++i] = c = getchar()));

	s[i] = '\0';

	if(c != EOF)
		prevc = c;

	return NUMBER;
}
