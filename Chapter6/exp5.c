#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define SIZE 100

struct list {
	char *name;
	char *defn;
	struct list *next;
};

struct list *hashtab[SIZE];

unsigned hash(char *s) {
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % SIZE;
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

int main() {
	char *name1 = "IN";
	char *defn1 = "1";

	char *name2 = "OUT";	
	char *defn2 = "2";

	install(name1, defn1);
	install(name2, defn2);

	struct list *np1 = lookup(name1);
	struct list *np2 = lookup(name2);

	printf("Definition for %s is %s\n", name1, np1 -> defn);
	printf("Definition for %s is %s\n", name2, np2 -> defn);
	
	undef(name1);

	if(lookup(name1) == NULL)
		printf("%s and its definition is removed.\n", name1);
}
