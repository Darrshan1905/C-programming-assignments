#include<stdio.h>

static int daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 100 || year % 400 == 0;

	if (year < 1 || month < 1 || month > 12 || day < 1 || day > *(*(daytab + leap) + month))
        	return -1;

    	for (i = 1; i < month; i++)
        	day += *(*(daytab + leap) + i);

    	return day;
}

void month_day(int year, int yearday, int *month, int *day) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (year < 1 || yearday < 1 || yearday > (leap ? 366 : 365)) {
        *month = -1;
        *day = -1;
        return;
    }

    for (i = 1; yearday > *(*(daytab + leap) + i); i++)
        yearday -= *(*(daytab + leap) + i);

    *month = i;
    *day = yearday;
}

int main() {
	int day = 29;
	int month = 2;
	int year = 2000;

	printf("Day in month day representation: day - %d month - %d\n",day, month);
	int year_day = day_of_year(year, month, day);
	printf("Equivalent year day representation: %d", year_day);


	int m,d;
	printf("\n\nDay in year day representation: %d\n", year_day);
	month_day(year, year_day, &m, &d);
	printf("Equivalent month day represntation: month - %d day - %d", m, d);
}
