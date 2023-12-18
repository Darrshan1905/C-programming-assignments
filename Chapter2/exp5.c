#include<stdio.h>
#include<string.h>

int main() {
	char s1[20];
	char s2[20];

	printf("Enter string 1: ");
	scanf("%s", s1);
	printf("Enter string 2: ");
	scanf("%s", s2);

	int isPresent[26] = {0};
	int f = 0;

        for(int i = 0; i < strlen(s2); i++) {
                int index;
                if(s2[i] >= 'a' && s2[i] <= 'z')
                        index = s2[i] - 'a';
                else if(s2[i] >= 'A' && s2[i] <= 'Z')
                        index = s2[i] - 'A';
                isPresent[index]++;
        }

	for(int i = 0; i < strlen(s1); i++) {
		int index;
                if(s1[i] >= 'a' && s1[i] <= 'z')
                        index = s1[i] - 'a';
                else if(s1[i] >= 'A' && s1[i] <= 'Z')
                        index = s1[i] - 'A';
		
		if(isPresent[index]) {
			printf("At position %d\n", i);
			f = 1;
			break;
		}
	}

	if(f == 0)
		printf("-1\n");
	
}
