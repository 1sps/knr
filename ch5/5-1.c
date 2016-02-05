/*K&R 2nd, Ex 5-1, ___: 2016-02-02 Tue 09:27 PM*/
/*As written, getint() treats + or - not followed by a digit as a valid
  representation of zero. Fix it push such a character back on the input.
*/

/*Header files*/
#include<stdio.h>
#include<ctype.h>
/*Function protoypes*/
int getint(int *n);

/* test getint() */
int main(void)
{
	int n, i;
	/*Get 10 numbers from 
	  stdin and print them
	*/
	for(i=0; i<10; ++i)
		if(getint(&n))
			printf("%d\n", n);
	return 0;
}

/*Function protoypes*/
int getch(void);
void ungetch();

/* getint: get next integer from input to *pn */
int getint(int *pn)
{
	int c, sign;

	while (isspace(c=getch()))  /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
		ungetch(c);  /* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		if(!isdigit(c = getch()))
		{
			ungetch(c); /* push back nondigit char after + or - */
			ungetch((sign==-1) ? '-' : '+'); /* push back + or - */
			return 0;   /* in this case indicate its not a number */
		}
	for (*pn = 0; isdigit(c); c=getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 100  /*Size of the buffer*/
char buf[BUFSIZE];   /*Buffer fot getch() and ungetch()*/
int bufp=0;          /*Next free position in buffer*/

/*Get a (possibly pushed back) character*/
int getch(void)
{
	return (bufp>0) ? buf[--bufp] : getchar();
}
/*Push one character back on input*/
void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
/*EOF*/
