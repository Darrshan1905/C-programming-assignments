#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define MAXSTORE 5000

char *lineptr[MAXLINES];
char linestore[MAXLINES];

int getline1(char *, int);
int readlines(char *lineptr[], char * linestore,int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
char *alloc(int);

/* sort input lines */
int main()
{
	int nlines;
	/* number of input lines read */
	if ((nlines = readlines(lineptr, linestore, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}


/* readlines: read input lines */
int readlines(char *lineptr[], char* linestore, int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	p = linestore;
	
	char *linestop = linestore + MAXSTORE;

	nlines = 0;
	while ((len = getline1(line, MAXLEN)) > 0)
		if (nlines >= maxlines || p + len > linestop)
			return -1;
		else {
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);
	if (left >= right) /* do nothing if array contains */
		return;
	/* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int getline1(char *s, int lim) {
    int c;
    char *t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;

    *s = '\0';

    return s - t;
}
