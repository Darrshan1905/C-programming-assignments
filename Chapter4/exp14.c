#include<stdio.h>

#define swap(t, x, y) {t z; \
			z = x; \
			x = y;\
			y = z;	}

int main() {
	int x = 4;
	int y = 5;
	printf("Before swapping: x = %d y = %d\n",x,y);
	swap(int, x, y);
	printf("After swapping: x = %d y = %d\n",x,y);
}
