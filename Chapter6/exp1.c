#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAXWORD 100
#define BUFSIZE 10000

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0
	};

char buf[BUFSIZE];
int bufp = 0;

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters");
	else
		buf[bufp++] = c;
}

int getword(char *word, int lim) {
	int c;
	char *w = word;
	
	int t;

	while(isspace(c = getch()));

	if(c != EOF)
		*w++ = c;

	if(!isalpha(c)) {
		if(c == '\"')
			for(c = getch(); c != '\"'; c = getch());
		else if(c == '#')
			for(c = getch(); c != '\n'; c = getch());
		else if(c == '/') {
			if((c = getch()) == '/')
				for(c = getch(); c != '\n'; c = getch());
			else if((c = getch() == '*')) {
				for(c = getch(), t = getch(); c != '*' && t != '/'; c = getch(), t = getch())
					ungetch(t);
			}
			else
				ungetch(c);
		}
		else
			for(; !isspace(c) && c != EOF; c = getch());

		if (c != '\"' && c != '\n' && c != '/')
            		ungetch(c);
        	*w = '\0';
        	return c;
	}	

	 for (; --lim > 0; w++)
        	if (!isalnum(*w = getch())) {
            		if (!isspace(*w)) {
                		ungetch(*w);
                		return (*w);
            		}
		       	else {
                		ungetch(*w);
                		break;
            		}
        	}
    	*w = '\0';
    	return word[0];
}

int bin_search(char *word, struct key tab[], int n) {
	int cond;
	int low = 0;
	int high = n - 1;
	int mid;

	while(low <= high) {
		mid = (low + high) / 2;
		if((cond = strcmp(word, tab[mid].word)) > 0)
			low = mid + 1;
		else if(cond < 0)
			high = mid - 1;
		else{
			printf("%s %d\n",word, mid);
			return mid;
		}
	}

	return -1;
}

int main() {
	int n;
	char word[MAXWORD];

	int NKEYS = sizeof(keytab) / sizeof (struct key);

	printf("%d\n", NKEYS);

	while((getword(word, MAXWORD)) != EOF) {
		if(isalpha(word[0])) {
			if((n = (bin_search(word, keytab, NKEYS))) >= 0){
				keytab[n].count++;
			}
		}
	}

	for(n = 0; n < NKEYS; n++) {
		if(keytab[n].count > 0) {
			printf("word: %s count: %d\n", keytab[n].word, keytab[n].count);
		}
	}

	return 0;
}
