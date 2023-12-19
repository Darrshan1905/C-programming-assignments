#include<stdio.h>

void escape(char s[], char t[]) {
	int i = 0;
	int j = 0;

	while(s[i] != '\0') {
		switch(s[i]) {
			case '\n':
				t[j++] = '\\';
				t[j++] = 'n';
				break;
			case '\t':
				t[j++] = '\\';
				t[j++] = 't';
				break;
			default:
				t[j++] = s[i];
				break;
		}
		i++;
	}

	t[j] = '\0';
}

void escape1(char t[], char s[]) {
	int i = 0;
	int j = 0;

	while(t[i] != '\0') {
		if(t[i] == '\\') {
			i++;
			switch(t[i]) {
				case 'n':
					s[j++] = '\n';
					break;
				case 't':
					s[j++] = '\t';
					break;
				default:
					s[j++] = '\\';
					s[j++] = t[i];
					break;
			}	
		}
		else {
			s[j++] = t[i];
		}
		i++;
	}
}

int main() {
	int c;
	char s[100], t[200], u[100];
	int i = 0;

	while((c = getchar()) != EOF) {
		s[i++] = c;
	}

	s[i] = '\0';

	printf("\n%s",s);

	escape(s, t);

	printf("\n%s", t);

	escape1(t, u);

	printf("\n%s",u);
}
