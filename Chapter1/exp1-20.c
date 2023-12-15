#include<stdio.h>

#define IN 0
#define OUT 1

int main() {
	int c;
	int currLen = 0;

	while((c = getchar()) != EOF) {
		if(c == '\n')
			putchar(c);
		else if(c == '\t') {
			for(int i = 0; i < 8 - currLen; i++)
				putchar(' ');
			currLen = 0;
		}
		else {
			putchar(c);
			currLen++;
			if(currLen > 8)
				currLen = currLen % 8;
		}
	}
}
