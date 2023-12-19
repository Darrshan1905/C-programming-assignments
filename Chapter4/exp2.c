#include<stdio.h>
#include<ctype.h>

double atof(char s[]) {
	int i, sign;
	double val = 0.0, power = 1.0;

	for(i = 0; isspace(s[i]); i++);

	sign = (s[i] == '-') ? -1 : 1;

	if(s[i] == '-' || s[i] == '+')
		i++;

	while(isdigit(s[i])) {
		val = 10.0 * val + (s[i] - '0');
		i++;
	}

	if(s[i] == '.') {
		i++;
		while(isdigit(s[i])) {
			val = 10.0 * val + (s[i] - '0');
			i++;
			power *= 10.0;
		}
	}

	val = sign * val / power;

	if(s[i] == 'e') {
		float exp = 0.0;
		int expsign;
		float pow = 1.0;

		i++;
		expsign = (s[i] == '-' ) ? -1 : 1;

	        if(s[i] == '+' || s[i] == '-')
			i++;

		while(isdigit(s[i])) {
			exp = 10.0 * exp + (s[i] - '0');
			i++;
		}

		while(exp > 0) {
			pow *= 10.0;
			exp--;
		}

		if(expsign == -1) {
			val /= pow;
		}
		else {
			val *= pow;
		}
	}
	
	return val;
}

int main() {
	char s[20];
	double res;

	printf("Enter a string in floating point notation: ");
	scanf("%s", s);

	res = atof(s);

	printf("%lf", res);
}
