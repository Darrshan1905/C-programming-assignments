#include<stdio.h>
#include<ctype.h>
#include<stdarg.h>

#define LOCALFMT 100

void minscanf(char *fmt, ...) {
	va_list ap;
	char *p, *sval;
	char localfmt[LOCALFMT];

	int i, *ival;
	unsigned *uval;
	float *dval;

	va_start(ap, fmt);

	for(p = fmt; *p; p++) {
		if(*p != '%') {
			putchar(*p);
			continue;
		}

		i = 0;
		localfmt[i++] = '%';

		while(*(p + 1) && !isalpha(*(p + 1)))
			localfmt[i++] = *++p;

		localfmt[i++] = *(p + 1);
		localfmt[i] = '\0';

		switch(*++p) {
			case 'd':
			case 'i':
				ival = va_arg(ap, int *);
				scanf(localfmt, ival);
				break;
			case 'x':
			case 'X':
			case 'o':
			case 'u':
				uval = va_arg(ap, unsigned *);
				scanf(localfmt, uval);
				break;
			case 'f':
				dval = va_arg(ap, float *);
			        scanf(localfmt, dval);
				break;
			case 's':
				sval = va_arg(ap, char *);
				scanf(localfmt, sval);
				break;
			default:
				scanf(localfmt);
				break;	
		}
	}
	va_end(ap);
}

int main() {
	float f;
	char *s;
	minscanf("%f %s", &f, s);
	printf("%.2f %s", f, s);
}
