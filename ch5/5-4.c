/* K&R2 Ex 5-4 */
/* Write the function strend(s,t), which returns 1 if the string t occurs at the
   end of the string s, and zero otherwise
*/
/*___: 2016-02-03 Wed 10:00 PM*/

/*Header files*/
#include<stdio.h>
#include<string.h>

/*Constants*/
#define MAXLEN

/*Function protoypes*/
int strend(char *s, char *t);

/* Test strend() */
int main(void)
{
	int n;
	char s[] = "Bayern Munich";
	char t[] = "Munich";
	char u[] = "Barca";
	n = strend(s, t);
	if(n)
		printf("%s occurs at then end of %s\n", t, s);
	else
		printf("%s DOES NOT occur at then end of %s\n", t, s);
	n = strend(s, u);
	if(n)
		printf("%s occurs at then end of %s\n", u, s);
	else
		printf("%s DOES NOT occur at then end of %s\n", u, s);
	return 0;
}

int strend(char *s, char *t)
{
	int i; 
	int slen = strlen(s);
	int tlen = strlen(t);
	/* If s is shorter than t */
	if(slen < tlen)
		return 0;
	s += (slen - 1); /* point to last char of s */
	t += (tlen - 1); /* point to last char of t */
	/* See if all char of t match to s */
	for(i=0;(i < tlen) && (*s-- == *t--); ++i)
		;
	if (i == tlen)
		return 1;

	return 0;
}

/*___*/
/*EOF*/
