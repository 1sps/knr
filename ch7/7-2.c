/* Ex 7-2 K&R2  */
/*
   Write a program that will print arbitrary input in a sensible way. As a
   minimum, it should print non-graphic characters in octal or hexadecimal
   according to local custom, and break long test lines.
*/
/* ___: 2016-02-25 Thu 02:35 AM */

/* Note: This is a minimal solution */

/*Header files*/
#include<stdio.h>
#include<ctype.h>

/*Constants*/
#define MAXLEN 80

/*Function protoypes*/

/*Program starts*/
int main(void)
{
	int c, poscount = 0;

	while ((c = getchar()) != EOF)
	{
		poscount++;
		if (poscount > MAXLEN)    /* break long lines */
		{
			poscount = 0;
			putchar('\n');
		}
		if (!isgraph(c) && !isspace(c)) /* print hex for non-printable */
		    printf("%X", c);            /* characters */
			
		else    /* printable character */
			putchar(c);
	}

	return 0;
}

/* EOF */
