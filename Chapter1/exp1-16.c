#include <stdio.h>
#define MAXLINE 10
int getlin(char line[], int maxline);
void copy(char to[], char from[]);
int main()
{
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];
	max = 0;
	while ((len = getlin(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0) 
	printf("Line: %s Max Length: %d", longest, max);
	return 0;
}
int getlin(char s[],int lim) {
	int c, i;
	for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if(i == lim - 1) {
		while((c = getchar()) != EOF) {
			i++;
		}
	}
	int temp = i;
	i = (i < MAXLINE - 1) ? i : MAXLINE - 1; 
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return temp;
}
void copy(char to[], char from[]) {
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
	++i;
}
