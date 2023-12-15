#include <stdio.h>

int main()
{
	int fahr, celsius;
	int lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;
	fahr = upper;
	printf("Temperature conversion\n");
	printf("Celcius\tFahrenheit\n");
	while (fahr >= lower) {
		celsius = 5 * (fahr-32) / 9;
		printf("%d\t%d\n", fahr, celsius);
		fahr = fahr - step;
	}
}
