#include<stdio.h>

void expand(char s1[], char s2[]) {
	int i = 0;
	int j = 0;

	int state = 0;
	int start;

	while(s1[i] != '\0') {
		if(s1[i] == '\n' || s1[i] == '\t' || s1[i] == ' ')
			s2[j++] = s1[i];
		else if(s1[i] == '-')
                        state = 1;
		else {
			if(state == 0) {
				start = s1[i];
				s2[j++] = start;
			}
			else {
				state = 0;
				for(int k = start + 1; k <= s1[i]; k++) {
					s2[j++] = k;
				}
				start = s1[i];
			}	
		}
		i++;
	}
	s2[j] = '\0';
}

int main() {
	int c;
	char s1[100], s2[100];
	int i = 0;

	while((c = getchar()) != EOF) {
		s1[i++] = c;	
	}

	s1[i] = '\0';

	expand(s1, s2);

	printf("%s", s2);
}
