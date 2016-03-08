/* Ex 7-1 K&R2  */
/*
   Write a program that converts upper case to lower or lower case to upper,
   depending on the name it is invoked with, as found in argv[0].
*/
/* ___: 2016-02-25 Thu 01:12 AM */

#include<stdio.h>
#include<ctype.h>
#include<string.h>

/* constants */
#define LOWER 1
#define UPPER 2
#define INVALID 3

int main(int argc, char *argv[]) /* convert case */
{
	int choice = INVALID, c;

	if (argc != 2)
		return printf("error: specifiy case conversion\n");
	
	/* find out the user choise */
	if (!strcmp(argv[1], "lower"))
		choice = LOWER;
	else if (!strcmp(argv[1], "upper"))
		choice = UPPER;
	else
		return printf("error: invalid option : %s\n\n", argv[1]);
	
	/* print according to user choice */
	if(choice == LOWER)
		while ((c = getchar()) != EOF)
			putchar(tolower(c));
	else if (choice == UPPER)
		while ((c = getchar()) != EOF)
			putchar(toupper(c));
	else
		return printf("error while processing\n");
		
	return 0;
}

/* EOF */
