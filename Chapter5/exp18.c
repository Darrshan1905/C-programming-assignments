#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum {NAME, PARENS, BRACKETS};
enum {NO, YES};

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char out[1000];
int prevtoken = NO;
char datatype[MAXTOKEN];

char buff[BUFSIZE];
int bufp = 0;

void dcl(void);
void dirdcl(void);

int getch() {
	return (bufp > 0) ? buff[--bufp] : getchar();
}

void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	buff[bufp++] = c;
}

int gettoken(void) {
	int c;
	char *p = token;

	if(prevtoken == YES) {
		prevtoken = NO;
		return tokentype;
	}

	while((c = getch()) == ' ' || c == '\t');

	if(c == '(') {
		if((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else {
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if(c == '[') {
		for(*p++ = c; (*p++ = getch()) != ']';);
		*p = '\0';

		return tokentype = BRACKETS;
	}
	else if(isalpha(c)) {
		for(*p++ = c; isalnum(c = getch());)
			*p++= c;
		ungetch(c);
		*p = '\0';

		return tokentype = NAME;
	}
	else {
		return tokentype = c;
	}
}

void errmsg(char *s) {
	printf("%s", s);
	prevtoken = YES;
}

void dirdcl(void) {
        int type;

        if(tokentype == '(') {
                dcl();

                if(tokentype != ')')
			errmsg("error: missing )\n");
        }
	else if(tokentype == NAME)
		strcpy(name,token);
	else
		errmsg("error: expected (dcl) or name\n");

	while((type = gettoken()) == PARENS || type == BRACKETS) {
		if(type == PARENS)
			strcat(out,"function returning ");
		else {
			strcat(out,"array ");
			strcat(out,token);
			strcat(out,"of ");
		}
	}
}


void dcl(void) {
	int ns;
	for(ns = 0; gettoken() == '*';)
		ns++;
	dirdcl();

	while(ns-- > 0) {
		strcat(out, "pointer to ");
	}
}

int main() {
	while(gettoken() != EOF) {
		strcpy(datatype, token);
		//out[0] = '\0';
		dcl();	
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}

	return 0;
}
