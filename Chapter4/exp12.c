#include<stdio.h>

int itoa(int c, char s[]) {
	static int i = 0;

	if(c < 0) {
		c = -c;
		s[i++] = '-';
	}

	if(c / 10 > 0)
		itoa(c / 10, s);
	s[i++] = (c % 10) + '0';

	return i;
}

int main() {
	int c = -123;
	char s[20];

	int i = itoa(c, s);

	s[i] = '\0';

	printf("%s", s);
}
