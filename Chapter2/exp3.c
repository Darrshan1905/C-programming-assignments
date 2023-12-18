#include<stdio.h>
#include<string.h>

int main() {
	char s[10];
	int index = 0;
	int num = 0;

	printf("Enter a hex value: ");
	scanf("%s", s);

	

	if(s[index] == '0') {
		index++;
		if(s[index] == 'X' || s[index] == 'x') 
			index++;
	}
	
	for(; index < strlen(s); index++) {
		int digit;
		if(s[index] >= '0' && s[index] <= '9')
			digit = s[index] - '0';
		else if(s[index] >= 'a' && s[index] <= 'z')
			digit = s[index] - 'a' + 10;
		else if(s[index] >= 'A' && s[index] <= 'Z')
			digit = s[index] - 'A' + 10;
		
		num = 16 * num + digit;
	}

	printf("Integer equivalent: %d\n", num);
}
