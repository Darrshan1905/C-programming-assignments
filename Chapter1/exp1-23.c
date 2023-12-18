#include<stdio.h>

int main() {
	int c;
	
	while((c = getchar()) != EOF) {
		if(c == '/') {
			int d;
			if((d = getchar()) == '*') {
				int i = getchar();
				int j = getchar();
				
				while(i != '*' || j != '/') {
					i = j;
					j = getchar();				
				}
			}
			else if(d == '/') {
				int i = getchar();
				
				while(i != EOF && i != '\n') {
					i = getchar();

				}
			}
			else {
				putchar(c);
				putchar(d);
			}	
		}
		else if(c == '"' || c == '\'') {
			putchar(c);
			int d;
			
			while((d = getchar()) != c) {
				putchar(d);
			}

			putchar(d);
 		}
		else {
			putchar(c);
		}	
	}
}
