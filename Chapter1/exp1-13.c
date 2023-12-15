#include<stdio.h>
#define IN 0
#define OUT 1

int main() {
	int c;
	int len = 0;
	int state = OUT;
	int hist[11];

	for(int i = 0; i < 11; i++) {
		hist[i] = 0;
	}

	
	while((c = getchar()) != EOF) {
		if(c == ' ' || c == '\t' || c == '\n') {
			if(state == IN && len > 0) {
				if(len <= 10)
					hist[len - 1]++;
				else
					hist[10]++;
				//printf("\n%d\n", hist[len - 1]);
			}
			state = OUT;
			len = 0;
		}
		else {
			len++;
			if(state == OUT)
				state = IN;
		}
		//printf("%d",len);
		
	}
	//printf("%d %d ", hist[2], hist[3]);

	for(int i = 0; i <= 10; i++) {
		if(i != 10) {
			printf("%d ----> ", i + 1);
		}
		else {
			printf(">10 ----> ");
		}
		for(int j = 0; j < hist[i]; j++) {
			//printf("%d", hist[i]);
			printf("-");
		}
		printf("\n");
	}
}
