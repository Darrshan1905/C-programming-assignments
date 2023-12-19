#include<stdio.h>
#include<limits.h>
#include<string.h>

#define abs(a) ((a > 0) ? a : -(a))

void reverse(char s[]) {
	int i = 0;
	int j = strlen(s) - 1;

	while(i < j) {
		char temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		i++;
		j--;
	}
}

int main() {
	int n = INT_MIN;
	int temp = n;
	int i = 0;
	char s[100];

	do {
		s[i++] = abs(n % 10) + '0';
	} while((n = abs(n / 10)) > 0);

	if(temp < 0)
		s[i++] = '-';

	s[i] = '\0';

	reverse(s);

	printf("%s", s);
}
