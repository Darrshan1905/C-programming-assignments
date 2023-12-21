#include<stdio.h>
#include<string.h>

void reverse(char s[], int i, int j) {
	if(i < j)
		reverse(s, i+1, j-1);
	char temp;
	temp = s[i];
	s[i] = s[j];
	s[j] = temp;
}

int main() {
	char s[100] = "abcd";
	reverse(s, 0, strlen(s) - 1);
	printf("%s\n", s);
}
