#include<stdio.h>

int main() {
	int b, t, n;
	b = 0;
	t = 0;
	n = 0;
	int c;
	while((c = getchar()) != EOF) {
		if(c == ' ')
			b++;
		if(c == '\t')
			t++;
		if(c == '\n')
			n++; 
	}

	printf("Blanks: %d\n, Tabs: %d\n, Newlines: %d\n", b, t, n);
}
