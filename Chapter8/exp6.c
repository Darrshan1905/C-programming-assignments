#include<stdio.h>
#include<stdlib.h>

int *mcalloc(unsigned n, unsigned size) {
	unsigned i, nb;
	char *p, *q;

	nb = n * size;

	if((p = q = malloc(nb)) != NULL)
		for(i = 0; i < nb; i++)
			*p++ = 0;

	return q;
}

int main() {
	int *p = NULL;
	int i = 0;
	p = mcalloc(100, sizeof *p);
	if(p == NULL)
		printf("calloc: returned NULL");
	else {
		for(i = 0; i <= 100; i++) {
			printf("%08X\n", p[i]);
			if(i % 8 == 7)
				printf("\n");
		}
		printf("\n");
		free(p);
	}

	return 0;
}
