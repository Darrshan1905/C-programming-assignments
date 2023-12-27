#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAXLINE 100

void settab(int argc, char *argv[], char *tab) {
	int i;
	if(argc <= 1) {
		for(i = 1; i <= MAXLINE; i++) {
			if(i % 8 == 0)
				tab[i] = 1;
			else
				tab[i] = 0;
		}
	}

	else {
		for(i = 1; i <= MAXLINE; i++)
			tab[i] = 0;
		while(--argc > 0) {
			int pos = atoi(*++argv);
			if(pos > 0 && pos <= MAXLINE)
				tab[pos] = 1;
		}
	}
}

int istabpos(int i, char *tab) {
	if(i > MAXLINE) {
		return 1;
	}
	return tab[i];
}

void entab(char *tab) {
	int c;
	int currTabLen = 0;
	int currBlankLen = 0;
	int i = 1;

	while((c = getchar()) != EOF) {
		if(c == ' ') {
			if(istabpos(i, tab) == 0)
				currBlankLen++;
			else {
				currBlankLen = 0;
				currTabLen++;
			}
		}
		else {
			for(; currTabLen > 0; currTabLen--)
				putchar('\t');
			if(c == '\t')
				currBlankLen = 0;
			else
				for(; currBlankLen > 0; currBlankLen--)
					putchar(' ');
			putchar(c);
			if(c == '\n')
				i = 0;
			if(c == '\t')
				while(istabpos(i, tab) == 0)
					i++;
		}
		i++;
	}
}

void detab(char *tab) {
	int i = 1,c;

	while((c = getchar()) != EOF) {
		if(c == '\n') {
			putchar(c);
			i = 1;
		}
		else if(c == '\t') {
			do {
				putchar(' ');
			} while(istabpos(i++, tab) == 0);
		}
		else {
			putchar(c);
			i++;
		}
	}
}

int main(int argc, char *argv[]) {
	char tab[MAXLINE + 1];
	settab(argc, argv, tab);
	entab(tab);
	detab(tab);
}
