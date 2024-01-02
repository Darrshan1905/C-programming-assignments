#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXWORD 100
#define N 1000
#define BUFSIZE 10000

struct node {
	char *word;
	int count;
	struct node* left;
	struct node* right;
};

struct node *list[N];
int n;
char buf[BUFSIZE];
int bufp = 0;

struct node *talloc() {
	return (struct node*) malloc(sizeof(struct node));
}

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters.\n");
	buf[bufp++] = c;
}

int getword(char *word, int lim) {
	int c;
	char *w = word;

	while(isspace(c = getch()));

	if(c != EOF) {
		*w++ = c;
	}

	if(!isalpha(c)) {
		*w = '\0';
		return c;
	}

	for(; --lim > 0; w++) {
		if(!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	}

	*w = '\0';

	return word[0];
}

struct node *addtree(struct node *p, char *w) {
	int cond;

	if(p == NULL) {
		p = talloc();
		p -> word = strdup(w);
		p -> count = 1;
		p -> left = p -> right = NULL;
	}
	else if ((cond = strcmp(w, p -> word)) == 0)
		p -> count++;
	else if(cond < 0)
		p -> left = addtree(p -> left, w);
	else
		p -> right = addtree(p -> right, w);
	
	return p;
}

void treestore(struct node* root) {
	if(root != NULL) {
		treestore(root -> left);
		if(n < N)
			list[n++] = root;
		treestore(root -> right);
	}	
}

void sortlist() {
	int gap, i, j;
	struct node* t;

	for(gap = n / 2; gap > 0; gap /= 2) {
		for(i = gap; i < n; i++) {
			for(j = gap - 1; j >= 0; j--) {
				if(list[j] -> count >= list[j + gap] -> count)
					break;
				t = list[j];
				list[j] = list[j + gap];
				list[j + gap] = t;
			}
		}
	}
}	

int main() {
	struct node *root;
	char word[MAXWORD];
	int i;
	root = NULL;

	while((getword(word, MAXWORD)) != EOF)
		if(isalpha(word[0]))
			root = addtree(root,word);

	treestore(root);
	sortlist();
	for(i = 0; i < n; i++)
		printf("%d: %s\n", list[i] -> count, list[i] -> word);

	return 0;
}
