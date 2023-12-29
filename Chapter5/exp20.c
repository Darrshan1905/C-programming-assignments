#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME,PARENS,BRACKETS};
enum { NO,YES };

void dcl(void);
void dirdcl(void);

char buf[BUFSIZE];
int bufp = 0;
char name[MAXTOKEN];
char datatype[MAXTOKEN];
int tokentype;
char token[MAXTOKEN];
char out[100];
int prevtoken = NO;

void errmsg(char *msg)
{
    printf("%s",msg);
    prevtoken = YES;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters \n");
    else
        buf[bufp++] = c;
}

int gettoken(void)
{
        int c;
        char *p = token;

        if (prevtoken == YES) {
                prevtoken = NO;
                return tokentype;
        }

        while ((c = getch()) == ' ' || c == '\t');

        if (c == '(') {
                if ((c = getch()) == ')') {
                        strcpy(token, "()");
                        return tokentype = PARENS;
                }
                else {
                        ungetch(c);
                        return tokentype = '(';
                }
        }
        else if (c == '[') {
                for (*p++ = c; (*p++ = getch()) != ']';);
                *p = '\0';
                return tokentype = BRACKETS;
        }
        else if (isalpha(c)) {
                for (*p++ = c; isalnum(c = getch());)
                        *p++ = c;
                *p = '\0';
                ungetch(c);
                return tokentype = NAME;
        }
        else
                 return tokentype = c;
}

int typespec(void)
{
    static char *type[] =
    {
        "char",
        "int",
        "void"
    };

    char *pt = token;

    if(strcmp(pt, type[0]) == 0 || strcmp(pt, type[1]) == 0)
        return NO;
    else
        return YES;
}

int typequal(void)
{
    static char *typeq[] =
    {
        "const",
        "volatile"
    };

    char *pt = token;

    if(strcmp(pt, typeq[0]) == 0 || strcmp(pt, typeq[1]) == 0)
        return YES;
    else
        return NO;
}

void dclspec(void)
{
    char temp[MAXTOKEN];

    temp[0] = '\0';
    gettoken();

    do
    {
        if(tokentype != NAME)
        {
            prevtoken = YES;
            dcl();
        }
        else if(typespec() == YES)
        {
            strcat(temp," ");
            strcat(temp,token);
            gettoken();
        }
        else if(typequal() == YES)
        {
            strcat(temp," ");
            strcat(temp,token);
            gettoken();
        }
        else
            errmsg("unknown type in parameter list \n");
    }while (tokentype != ',' && tokentype != ')');

    strcat(out,temp);
    if(tokentype == ',')
        strcat(out,",");
}


void parmdcl(void)
{
    do
    {
        dclspec();
    }while ( tokentype == ',');
    
    if(tokentype != ')')
        errmsg("missing ) in parameter declaration \n");
}

void dcl(void)
{
    int ns;

    for(ns = 0; gettoken() == '*'; )
        ns++;
    dirdcl();
    while(ns-- > 0)
        strcat(out,"pointer to");
}

void dirdcl(void)
{
    int type;

    if(tokentype == '(')
    {
        dcl();
        if( tokentype != ')')
            errmsg("error: missing ) \n");
    }
    else if(tokentype == NAME)
    {
        if(name[0] == '\0')
            strcpy(name,token);
    }
    else
        prevtoken = YES;

    while((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if( type == PARENS)
            strcat(out,"function returning");
        else if (type == '(')
        {
            strcat(out,"function expecting");
            parmdcl();
            strcat(out,"and returning");
        }
        else
        {
            strcat(out,"array");
            strcat(out,token);
            strcat(out,"of");
        }
}

int main()
{
	while (gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();

		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
