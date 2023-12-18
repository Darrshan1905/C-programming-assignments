#include<stdio.h>

int main() {
	unsigned x = 255;
	unsigned y = 0;
	int n = 4;
	int p = 3;

	unsigned res = x & ~(~(~0 << n) << (p + 1 - n)) | (y & (~(~0 << n) << (p + 1 - n)));

	printf("%u", res);
}
