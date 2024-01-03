#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINE 100

void filecomp(FILE *fp1, FILE *fp2) {
	char line1[MAXLINE], line2[MAXLINE];
	char *lp1, *lp2;

	do {
		lp1 = fgets(line1, MAXLINE, fp1);
		lp2 = fgets(line2, MAXLINE, fp2);

		if(lp1 == line1 && lp2 == line2) {
			if(strcmp(line1, line2) != 0) {
				printf("first difference at line %s\n", line1);
				lp1 = lp2 = NULL;
			}
			else if(line1 != lp1 && line2 == lp2) {
				printf("end of first file at line %s", line1);
			}
			else if(line1 == lp1 && line2 != lp2) {
				printf("end of second line at line %s", line2);
			}
		}
	} while(line1 == lp1 && line2 == lp2);
}

int main(int argc, char *argv[]) {
	FILE *fp1, *fp2;
	
	if(argc != 3) {
		fprintf(stderr, "two file names needed.\n");
		exit(1);
	}
	else {
		if((fp1 = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "can't open %s\n", *argv);
			exit(1);
		}
		else if ((fp2 = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "can't open %s\n", *argv);
                        exit(1);
		}
		else {
			filecomp(fp1, fp2);
			fclose(fp1);
			fclose(fp2);
		}
	}
}
