#include<stdio.h>

int strindex(char s[], char t[]) {
	int i, j, k, res;

	for(i = 0; s[i] != '\0'; i++) {
		for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++);
		
		if(k > 0 && t[k] == '\0')
			res = i;
	}	

	return res;
}

int main() {
	char s[20], t[20];

	printf("Enter string 1: ");
	scanf("%s", s);

	printf("Enter string 2:");
	scanf("%s", t);

	int index = strindex(s, t);

	printf("%d", index);
}
