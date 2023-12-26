#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void strncpy1(char *s, char *t, int n) {
	int slen = (int)strlen(s);
	int tlen = (int)strlen(t);

	while(*t && n-- > 0) {
		*s++ = *t++;
		//printf("%c\n", *(s - 1));	
	}
	if(n > slen && tlen > slen)
		*s = '\0';
}

void strncat1(char *s, char *t, char *target, int n) {
	while(*s) {
		*target++ = *s++;
	}

	while(n-- > 0) {
		*target++ = *t++;
	}
	
	*target = '\0';

}

int strncmp1(char *s, char *t, int n) {
    for (; *s == *t; s++, t++)
        if (*s == '\0' || --n <= 0)
            return 0;
    return *s - *t;
}


int main() {
	char s[] = "abcdf";
	char t[] = "endh";
	char *target;
	int n = 3;

	printf("strncpy:\n");
	printf("s at start: %s  t at start: %s\n", s, t);
	strncpy1(s, t, n);
	printf("s after copying %d characters: %s\n\n", n, s);

        if ((target = (char *) malloc(sizeof(char) * (strlen(s) + +4 + 1))) == NULL) {
                printf("unable to allocate memory \n");
                return -1;
        }
	printf("strncat:\n");
	printf("s at start: %s t at start: %s\n", s, t);
	strncat1(s,t,target,n);
	printf("Target string after concatenating s and t: %s\n\n",target);

	printf("strncmp:\n");
	printf("s at start: %s t at start: %s\n", s, t);
	int ret = strncmp1(s, t, 4);
	printf("Strncmp return value: %d\n", ret);
}
