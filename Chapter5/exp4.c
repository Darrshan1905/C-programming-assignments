#include<stdio.h>
#include<string.h>

int strend(char *s, char *t) {
	if(strlen(s) < strlen(t))
		return 0;

	char *p = s;
	while(*s++);
	s -= 2;

	char *q = t;
	while(*t++);
	t-=2;

	for(;t >= q && *s == *t; s--, t--);
	t++;
	if(t == q)
		return 1;
	return 0;
}

int main() {
	char *s = "trend";
	char *t = "end";
	printf("%d",strend(s, t));


}
