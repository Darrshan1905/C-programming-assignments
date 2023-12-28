#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define NUMERIC 1
#define DECR 2
#define FOLD 4
#define MDIR 8
#define LINES 100
#define MAXLEN 1000
#define MAXSTR 100
#define ALLOCSIZE 10000

int  option = 0;
int pos1 = 0;
int pos2 = 0;
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

void readargs(int argc, char *argv[]) {
	int c;
	
	while(--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+') {
		if(c == '-' && !isdigit(*(argv[0] + 1)))
			while(c = *++argv[0]) {
				switch(c) {
					case 'd':
						option |= MDIR;
						break;
					case 'f':
						option |= FOLD;
						break;
					case 'n':
						option |= NUMERIC;
						break;
					case 'r':
						option |= DECR;
						break;
					default:
						printf("Usage: sort -dfnr [+pos1] [-pos2]");
						exit(1);
						break;
				}
			}
		else if(c == '-') {
			pos2 = atoi(argv[0] + 1);
		}
		else if ((pos1 = atoi(argv[0] + 1)) < 0) {
			printf("Usage: sort -dfnr [+pos1] [-pos2]");
			exit(1);
		}
	}
}

int getline1(char *line, int lim) {
	int c,i = 0;

	for(;i < lim -1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;
	if(c == '\n')
		line[i++] = c;

	line[i] = '\0';

	return i;
}

char *alloc(int n) {
	if(allocbuf + ALLOCSIZE - allocp >= n){
		allocp += n;
		return allocp - n;
	}
	else {
		return 0;
	}
}

int readlines(char *lineptr[], int lim) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;

	while((len = getline1(line, MAXLEN)) > 0) {
		if(nlines >= lim || (p = alloc(len)) == NULL) {
			return -1;
		}
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			//printf("%s  nlines: %d", lineptr[nlines - 1], nlines);	
		}
	}

	return nlines;
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void substr(char *s1, char *str) {
	int i, j, len;

	len = strlen(s1);

	if(pos2 > 0 && len > pos2)
		len = pos2;
	else if(pos2 > 0 && len < pos2) {
		printf("String is too short");
		exit(1);
	}
	for(j = 0, i = pos1; i < len; i++, j++) {
		str[j] = s1[i];
	}	
	str[j] = '\0';
}

int numcmp(char *s1, char *s2) {
	double v1, v2;
	char str[MAXSTR];

	substr(s1, str);
	v1 = atof(str);

	substr(s2, str);
	v2 = atof(str);

	if(v1 > v2)
		return 1;
	else if(v1 < v2)
		return -1;
	else 
		return 0;

}

int charcmp(char *s1, char *s2) {
	char a,b;
	int i, j, endpos;

	i = j = pos1;

	int fold = option & FOLD ? 1 : 0;
	int dir = option & MDIR ? 1 : 0;

	do {
		if(dir) {
			while(i < endpos && !isalnum(s1[i]) && s1[i] != ' ' && s1[i] != '\0')
				i++;
			while(j < endpos && !isalnum(s2[j]) && s2[j] != ' ' && s2[j] != '\0')
				j++;
		}

		if(i < endpos && j < endpos) {
			a = fold ? tolower(s1[i]) : s1[i];
			i++;
			b = fold ? tolower(s2[j]) : s2[j];
			j++;
		}

		if(a == '\0' && b == '\0') {
			return 0;
		}
	} while(a == b && i < endpos && j < endpos);

	return a - b;
}

void myqsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;

	if(left >= right) {
		return;
	}

	swap(v, left, (left + right) / 2);

	last = left;

	for(i = left + 1; i <= right; i++) {
		if((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	}

	swap(v, left, last);

	myqsort(v, left, last - 1, comp);
	myqsort(v, last + 1, right, comp);
}

void writelines(char *lineptr[], int nlines) {
	int i = 0;

	for(; i < nlines; i++) {
		printf("%s\n", lineptr[i]);
	}
}

int main(int argc, char *argv[]) {
	char *lineptr[LINES];
	int nlines;
	int rc = 0;

	readargs(argc, argv);

	if((nlines = readlines(lineptr, LINES)) > 0) {
		if(option & NUMERIC)
			myqsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
		else
			myqsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) charcmp);
		writelines(lineptr, nlines);
	}
	else {
		printf("input is too big...");
		rc = -1;
	}

	return rc;
}
