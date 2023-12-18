#include<stdio.h>

#define MAXLEN 1000
int main() {
	int c, i;
	char s[MAXLEN];

	while((c = getchar()) != EOF) {
		for(i = 0;; i++) {
			if(i < MAXLEN - 1) { 
				if((c = getchar()) != EOF) {
					if(c == '\n')
						break;
				}
				else {
					break;
				}
			}
			else {
				break;
			} 
			s[i] = c;
		}
		if(c == '\n')
			s[i++] = c;
		s[i] = '\0';
	}

	printf("%s", s);
}
