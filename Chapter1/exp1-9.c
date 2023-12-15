#include<stdio.h>
#include<string.h>

int main() {
	int i = 0;
	int j = 0;
	int f = 0;
	char s[50];
	scanf("%[^\n]s",s);
	printf("%s\n",s);
	int c;
	while(s[i] != '\0') {
		if(s[i] == ' ' || s[i] == '\t') {
			f++;
		}
		if(s[i] != ' ' && s[i] != '\t'){
			if(f > 0) {
				f = 0;
				s[j++] = ' ';	
			}
			s[j++] = s[i];
		}
		i++;
	}
	s[j] = '\0';
	printf("%s",s);
}
