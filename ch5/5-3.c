/* K&R2 Ex 5-3*/
/* Write a pointer version of function strcat that we showed in Chapter 2:
   strcat(s,t) copies t to the end of s. 
*/

/*Header files*/
#include<stdio.h>

/*Constants*/
#define MAXLEN 100

/*Function protoypes*/
void strcat1(char *s, char *t);

/* Test strcat1() */
int main(void)
{

	char s[MAXLEN] = "Bayern ";
	char t[MAXLEN] = "Munich";

	printf("%s\n", s);
	strcat1(s, t);
	printf("%s\n", s);

	return 0;
}

/* Copy string t to the end of string s */
void strcat1(char *s, char *t)
{
	while(*s != '\0')
		++s;
	while(*s++ = *t++)
		;
}

/*___*/
/*EOF*/
