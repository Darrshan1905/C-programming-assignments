#include<stdio.h>

int main() {
	int c;

	while((c = getchar()) != EOF) {
		(c >= 'A' && c <= 'Z') ? putchar(c - 'A' + 'a') : putchar(c);
	}
}
