#include<stdio.h>

int main() {
	int c;
	int currTabLen = 0;
	int currBlankLen = 0;
	int i = 1;

	while((c = getchar()) != EOF) {
		if(c == ' ') {
			if(i % 8 != 0)
				currBlankLen++;
			else {
				currBlankLen = 0;
				currTabLen++;
			}
		}
		else {
			for(; currTabLen > 0; currTabLen--)
				putchar('\t');
			if(c == '\t')
				currBlankLen = 0;
			else
				for(; currBlankLen > 0; currBlankLen--)
					putchar(' ');
			putchar(c);
			if(c == '\n')
				i = 0;
			if(c == '\t')
				i = i + (8 - (i - 1) % 8) - 1;
		}
		i++;
	}
}
