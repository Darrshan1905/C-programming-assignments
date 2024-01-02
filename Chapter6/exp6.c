#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAXWORD 100
#define BUFSIZE 10000

struct list {
	char *name;
	char *defn;
	struct list *next;
};

struct list *hashtab[BUFSIZE];

char buf[BUFSIZE];
int bufp = 0;

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters.\n");
	buf[bufp++] = c;
}

void ungets(char s[]) {
	int i = strlen(s);

	while(i > 0) {
		ungetch(s[--i]);
	}
}

void error(int c, char *s) {
	printf("error: %s\n", s);

	while(c != EOF && c != '\n')
		c = getch();
}

int getword(char *word, int lim)
{
	int c;
	char *w = word;
	while (isspace(c = getch()));
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

void skipblanks() {
	int c;

	while((c = getch()) == ' ' || c == '\t');

	ungetch(c);
}

unsigned hash(char *s) {
        unsigned hashval;
        for (hashval = 0; *s != '\0'; s++)
                hashval = *s + 31 * hashval;
        return hashval % BUFSIZE;
}

struct list *install(char *s, char *d);

void undef(char *s) {
	struct list *np;
	struct list *prev = NULL;

	for(np = hashtab[hash(s)]; np != NULL; np = np -> next) {
		if(strcmp(np -> name, s) == 0)
			break;
		prev = np;
	}

	if(np != NULL) {
		if(prev == NULL)
			hashtab[hash(s)] = np -> next;
		else
			prev -> next = np -> next;

		free((void*) np -> name);
		free((void*) np -> defn);
		free((void*) np);
	}
}

void getdef() {
	int c, i;
	char def[MAXWORD], name[MAXWORD], dir[MAXWORD];

	skipblanks();

	if(!isalpha(getword(dir, MAXWORD)))
		error(dir[0], "getdef: expecting a directive after #.\n");
	else if(strcmp(dir, "define") == 0) {
		skipblanks();

		if(!isalpha(getword(name, MAXWORD)))
			error(name[0], "getdef: alpha name expected.\n");
		else {
			skipblanks();
			for(i = 0; i < MAXWORD - 1; i++) {
				if((def[i] = getch()) == EOF || def[i] == '\n')
					break;
			}
			def[i] = '\0';

			if(i <= 0)
				error('\n',"getdef: incomplete definition.\n");
			else {
				struct list *np = install(name, def);
				printf("%s - %s\n", np -> name, np -> defn);
			}
		}
	}
	else if(strcmp(dir, "undef") == 0) {
		skipblanks();

		if(!isalpha(getword(name, MAXWORD)))
			error(name[0],"getdef: alpha name expected.\n");
		else {
			undef(name);
			printf("Removed the definition for %s\n", name);
		}
	}
	else {
		error(dir[0], "expecting a directive after #.\n");
	}
}

struct list *lookup(char *s) {
	struct list *np;

	for(np = hashtab[hash(s)]; np != NULL; np = np -> next)
		if(strcmp(s, np -> name) == 0)
			return np;
	return NULL;
}

struct list *install(char *s, char *d) {
	struct list* np;
	unsigned hashvalue;

	if((np = lookup(s)) == NULL) {
		np = (struct list*) malloc (sizeof(struct list));
		if(np == NULL || (np -> name = strdup(s)) == NULL)
			return NULL;
		hashvalue = hash(s);
		np -> next = hashtab[hashvalue];
		hashtab[hashvalue] = np;
	}
	else {
		free ((void*) np -> defn);
	}
	if((np -> defn = strdup(d)) == NULL)
		return NULL;
	return np;
}

int main() {
	char word[MAXWORD];
	struct list *p;

	while(getword(word, MAXWORD) != EOF) {
		if(strcmp(word, "#") == 0)
			getdef();
		else if(!isalpha(word[0]))
			printf("%s", word);
		else if((p = lookup(word)) == NULL)
			printf("%s", word);
		else
			ungets(p -> defn);
	}
}
