#include<stdio.h>
#include<ctype.h>

#define SIZE 1000
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;


int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}


void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch()));

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return -1; 
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();

    if (!isdigit(c))
        return 0;
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

int main(void) {
    int n = 0, i, arr[SIZE], getint(int *);

    while (n < SIZE && getint(&arr[n]) != EOF) {
	if(arr[n])
		n++;
     }

    for (i = 0; i <= n; i++)
        printf("%d ", arr[i]);

    return 0;
}
