#include<stdio.h>

int main() {
	unsigned x;
	printf("Enter a number: ");
	scanf("%u", &x);
	int b = 0;

	while(x) {
		b++;
		x &= x - 1;	
	}	

	printf("No. of set bits: %d\n",b);
}
