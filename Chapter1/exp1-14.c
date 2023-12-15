#include<stdio.h>

int main() {
	int c;
	int hist[26];

	for(int i = 0; i < 26; i++) {
		hist[i] = 0;
	}
	
	while((c = getchar()) != EOF) {
		if(c == '\t' || c == '\n' || c == ' ')
			continue;
		if(c >= 'A' && c <= 'Z') {
			int index = (int)(c) - 65;
			hist[index]++;
		}
		else if(c >= 'a' && c <= 'z') {
			int index = (int)(c) - 97;
			hist[index]++;
		}
	}

	for(int i = 0; i < 26; i++) {
		printf("%c ----> ",i + 97);
		for(int j = 0; j < hist[i]; j++)
			printf("-");
		printf("\n");
	}
}
