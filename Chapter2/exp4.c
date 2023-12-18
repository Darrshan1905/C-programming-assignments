#include<stdio.h>
#include<string.h>

void squeeze(char s1[], char s2[]) {
	int isPresent[26] = {0};
	
	for(int i = 0; i < strlen(s2); i++) {
		int index;
		if(s2[i] >= 'a' && s2[i] <= 'z')
			index = s2[i] - 'a';
		else if(s2[i] >= 'A' && s2[i] <= 'Z')
			index = s2[i] - 'A';
		isPresent[index]++;
	}

	int j = 0;

	for(int i = 0; i < strlen(s1); i++) {
		int index;
		if(s1[i] >= 'a' && s1[i] <= 'z')
			index = s1[i] - 'a';
		else if(s1[i] >= 'A' && s1[i] <= 'Z')
			index = s1[i] - 'A';

		if(!isPresent[index]) {
			s1[j++] = s1[i];
		}
	}

	s1[j] = '\0'; 

}

int main() {
	char s1[20];
	char s2[20];

	
	printf("Enter string 1:");
	scanf("%s",s1);
	printf("Enter string 2:");
	scanf("%s",s2);

	squeeze(s1, s2);
		
	printf("%s\n",s1);
}
