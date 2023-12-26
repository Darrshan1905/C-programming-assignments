#include<stdio.h>

void strcat1(char *s, char *t) {
	while(*s++);
	s--;
	while(*s++ = *t++);
}

int main() {
	char s[100] = "abcd";
	char t[100] = "efgh";

	strcat1(s,t);

	printf("%s", s);
}
