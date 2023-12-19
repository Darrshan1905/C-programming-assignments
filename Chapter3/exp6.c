#include<stdio.h>
#include<string.h>

void reverse(char s[]) {
	int i,j;
	char c;

	i = 0;
	j = strlen(s) - 1;

	while(i < j) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
}

void itoa(int n, char s[], int mini) {
	int i = 0, temp;

	if(n < 0)
		n = -n;

	do {
		s[i++] = (n % 10) + '0';  
	} while((n /= 10) > 0);

	if(temp < 0)
		s[i++] = '-';

	
	while(i < mini) {
		s[i++] = ' ';
	}

	s[i] = '\0';

	reverse(s);
}

int main() {
	int n, mini;
	char s[20];
	
	printf("Enter a number: ");
	scanf("%d", &n);

	printf("Enter the minimum field width: ");
	scanf("%d", &mini);
	
	itoa(n, s, mini);

	printf("%s", s);
}
