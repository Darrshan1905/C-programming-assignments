#include<stdio.h>

#define MAXLEN 1000

int getlin(char s[], int lim);
int remove_trailing_spaces(char line[]);

int main() {
	int len;
	char line[MAXLEN];
	
	while((len = getlin(line, MAXLEN)) > 0) {
		if(remove_trailing_spaces(line) > 0)
			printf("%s", line);
	}
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

int remove_trailing_spaces(char line[]) {
	int i;

	for(i = 0; line[i] != '\n'; i++);
	
	i--;

	for(i > 0; line[i] == '\t' || line[i] == ' '; i--);

	if(i >= 0){
		line[++i] = '\n';
		line[++i] = '\0';
	}

	return i;
}
