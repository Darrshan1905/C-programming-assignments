#include<stdio.h>
#include<string.h>

void reverse(char s[]) {
	int i = 0;
	int j = strlen(s) - 1;
	char temp;

	while(i < j) {
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		i++;
		j--;
	}
}

void itob(int n, char s[], int b) {
	int temp = n;
	int i = 0, d;

	if(n < 0)
		n = -n;
	
	do {
		d = n % b;
		s[i++] = (d <= 9) ? d + '0' : d + 'a' - 10;
	} while((n /= b) > 0);

	if(temp < 0)
		s[i++] = '-';

	s[i] = '\0';

	reverse(s);
	
}

int main() {
	int n, b;
	char s[20];

	printf("Enter a number: ");
	scanf("%d", &n);

	printf("Enter the base: ");
	scanf("%d", &b);

	itob(n,s,b);

	printf("%s", s);
}
