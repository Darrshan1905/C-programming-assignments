#include<stdio.h>

int buf = 0;

void ungetch(char c) {
	if(buf != 0)
		printf("too many character for ungetch.\n");
	else
		buf = c;
}

int getch() {
	int c = (buf != 0) ? buf : getchar();
	buf = 0;
}

int main() {
	char c = '@';
	
	ungetch(c);

	while((c = getch()) != EOF)
		putchar(c);
}
