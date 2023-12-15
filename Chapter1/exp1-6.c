#include<stdio.h>

int main() {
	int c = getchar();
	if(c != EOF)
		printf("1");
	else
		printf("0");
	return 0;
}
