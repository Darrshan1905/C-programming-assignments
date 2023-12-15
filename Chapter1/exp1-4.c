#include <stdio.h>

int main()
{
	float fahr, celsius;
	int lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;
	celsius = lower;
	printf("Temperature conversion\n");
	printf("Fahrenheit\tCelsius\n");
	while (celsius <= upper) {
		fahr = 9.0/5.0 * (celsius)+32;
		printf("%.2f\t\t%.2f\n", celsius, fahr);
		celsius = celsius + step;
	}
}
