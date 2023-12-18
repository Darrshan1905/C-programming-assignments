#include<stdio.h>

int main() {
	unsigned x = 29;
	int n = 3;

	int i = 1;

	unsigned v;

	for(v = ~0; (v = v >> 1) > 0; i++);

	unsigned res = (x >> n) | (x << (i - n));

	printf("%u\n", res);
}
