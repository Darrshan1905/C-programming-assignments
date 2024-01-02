#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXLINE 100
#define OCT 6

int inc(int pos, int len) {
	if(pos + len < MAXLINE)
		return pos + len;
	else {
		putchar('\n');
		return len;
	}	
}

int main() {
	int c, pos;

	pos = 0;

	while((c = getchar()) != EOF) {
		if(iscntrl(c) || c == ' ') {
			pos = inc(pos, OCT);
			printf("%03o", c);

			if(c == '\n') {
				pos = 0;
				putchar(c);
			}
		}
		else {
			pos = inc(pos, 1);
			putchar(c);
		}
	}

	return 0;
}
