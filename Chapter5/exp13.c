#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 10000 

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *lineptr[MAXLINES];

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	}
       	else
		return 0;
}


int getline1(char s[],int lim)
{
	int c, i;

	for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}



int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = getline1(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines, int argc, char *argv[])
{
	int i;
	if(--argc > 0) {
		if(atoi(&argv[1][1]) < 0) {
			printf("error: invalid number for lines.");
		}
		else {
			int lastlines = nlines - atoi(&argv[1][1]);
			if(lastlines > 0)
				for(i = lastlines; i < nlines; i++) {
					printf("%s\n", lineptr[i]);
				}
			else
				for (i = 0; i < nlines; i++)
                			printf("%s\n", lineptr[i]);
		}
	}
	else {
		if(nlines < 10)
			for (i = 0; i < nlines; i++)
		                printf("%s\n", lineptr[i]);
		else
			for (i = nlines - 10; i < nlines; i++)
		                printf("%s\n", lineptr[i]);

	}
}

int main(int argc, char *argv[])
{
	int nlines;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		writelines(lineptr, nlines, argc, argv);
		return 0;
	} 
	else {
		printf("error: input too big\n");
		return 1;
	}
}
