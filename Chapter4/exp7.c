#include<stdio.h>
#include<string.h>

#define MAXLEN 100

int bufp = 0;
char buf[MAXLEN];

void getlin(char line[], int lim ) {
	int i, c;

	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		line[i] = c;
	}

	if(c == '\n')
		line[i++] = c;

	line[i] = '\0';
}

void ungetch(char c) {
        if(bufp >= MAXLEN) {
                printf("too many characters for ungetch.\n");
        }
        else {
                buf[bufp++] = c;
        }
}


void ungets(char s[]) {
	int i = strlen(s);

	while(i > 0) {
		ungetch(s[--i]);
	}
}	

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();		
}

int main(){
	char line[MAXLEN], c;

	getlin(line, MAXLEN);
	
	ungets(line);

	while((c = getch()) != EOF)
		putchar(c);
}
