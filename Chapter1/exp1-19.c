#include<stdio.h>

#define MAXLEN 1000

int getlin(char s[], int lim);

int main() {
	int len;
	char line[MAXLEN];
	
	while((len = getlin(line, MAXLEN)) > 0) {
		int i = 0;
		int j = len - 2;
		while(i < j) {
			char temp = line[i];
			line[i] = line[j];
			line[j] = temp;
			i++;
			j--;
		}
		printf("%s",line);
	}

	return 0;
}

int getlin(char s[], int lim) {
	int c, i;

	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		s[i] = c;
	}
	if(c == '\n') {
		s[i] = c;
		i++;
	}
	s[i] = '\0';

	return i;
}
