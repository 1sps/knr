/* k&r2 Ex 5-8 */

/*Header files*/
#include<stdio.h>

/*Constants*/
#define LEAPDAYS   366
#define NOLEAPDAYS 365

/* External data */
static char daytab[2][13] = {
								{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,
								31},
								{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30,
								31},
							};
/*Function protoypes*/
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

/*Program starts*/
int main(void)
{
	/* Test month_day() */
	int month, day;
	month_day(1987, 365, &month, &day);
	printf("Year ,  day : 1987, 365\n");
	printf("Month , day : %d, %d\n", month, day);

	/* Test day_of_year() */
	printf("2016 13 16 : Day of the year: %d\n", day_of_year(2016, 2, 30));

	/*Program ends*/
	return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	/* Error checking */

	/* Is year valid? */
	if (year < 0)
		return -1;

	/* Is month valid? */
	if (month < 1 || month > 12)
		return -1;

	/* Is day valid? */
	if (day > daytab[leap][month])
		return -1;

	/* No errors: Calculate the day */
	for (i=1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	/* Check for errors */
	/* Is year valid? */
	if (year < 0)
	{
		*pmonth = *pday = -1;
		return;
	}
		
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	/* Check for errors */
	/* Is yearday valid? */
	if(yearday < 1 || yearday > (leap ? LEAPDAYS : NOLEAPDAYS))
	{
		*pmonth = *pday = -1;
		return;
	}

	/* no errors: calculate month and day */
	for(i=1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}
/*___*/
/*EOF*/
