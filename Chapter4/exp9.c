#include<stdio.h>
#include<string.h>

#define MAXLEN 100

int bufp = 0;
int buf[MAXLEN];

void ungetch(char c) {
        if(bufp >= MAXLEN) {
                printf("too many characters for ungetch.\n");
        }
        else {
                buf[bufp++] = c;
        }
}	

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();		
}



int main(){
	int c = '@';

	ungetch(c);	

	while((c = getch()) != EOF)
		putchar(c);
}
