#include<stdio.h>
#include<stdlib.h>

#define MAXBOT 4
#define MAXHDR 6
#define MAXLINE 100
#define MAXPAGE 50

int heading(char *fname, int page) {
	int line = 3;

	fprintf(stdout,"\n\n");
	fprintf(stdout, "%s - page %d", fname, page);

	while(line++ < MAXHDR) {
		fprintf(stdout, "\n");
	}

	return line;
}

void fileprint(FILE *fp, char *fname) {
	int lineno, page = 1;
	char line[MAXLINE];

	lineno = heading(fname, page++);

	while((fgets(line, MAXLINE, fp)) != NULL) {
		if(lineno == 1) {
			fprintf(stdout, "\f");
			lineno = heading(fname, page++);
		}
		fputs(line, stdout);
		if(++lineno > MAXPAGE - MAXBOT)
			lineno = 1;
	}

	fprintf(stdout,"\f");
}

int main(int argc, char *argv[]) {
	FILE *fp;

	if(argc == 1)
		fileprint(stdin, "");
	else
		while(--argc > 0) {
			if((fp = fopen(*++argv, "r")) == NULL) {
				printf("can't open file %s\n", *argv);
				exit(1);
			}
			else {
				fileprint(fp, *argv);
				fclose(fp);
			}
		}
	return 0;
}
