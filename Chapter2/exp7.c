#include<stdio.h>

int main() {
	unsigned x = 26;
	int p = 3;
	int n = 3;

	unsigned res = x ^ (~(~0 << n) << (p + 1 -n));

	printf("%u\n", res);
}
