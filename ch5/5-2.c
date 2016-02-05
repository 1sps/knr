/*K&R 2nd, Ex 5-2, ___: 2016-02-03 Tue 8:00 PM*/
/*Write getfloat(), the floating-point equivalent of getint(). What type does
  getfloat return as its function value ?
*/

/*Header files*/
#include<stdio.h>
#include<ctype.h>

/*Constants*/
#define TRUE  1
#define FALSE 0

/*Function protoypes*/
int getfloat(float *pn);

/* test getfloat() */
int main(void)
{
	int i;
	float n;
	/* Get 10 numbers from 
	   stdin and print them */
	for(i=0; i<10; ++i)
		if(getfloat(&n))
			printf("%g\n", n);
	return 0;
}

/*Function protoypes*/
int getch(void);
void ungetch();

/* getfloat: get next floating point number from input to *pn */
/* returns int type as its function value */
int getfloat(float *pn)
{
	int c, sign, pow, pm = FALSE;
	/* skip white space */
	while (isspace(c=getch()))  
		;
	/*If it's not a number*/
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
	{
		ungetch(c); 
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	/*If number starts with + or - */
	if (c == '+' || c == '-')
	{
		/*If not a number after + or - */
		if(!isdigit(c = getch()) && c != '.')
		{
			ungetch(c); /* push back */
			/* push back + or - */
			ungetch((sign == -1) ? '-' : '+'); 
			return 0; 
		}
		pm = TRUE; /* flag that + or - was read */
	}
	/*If number starts with a '.'
	  (possibly after + or -) */
	if(c == '.')
	{
		/* If not a number after . */
		if(!isdigit(c = getch()))
		{
			ungetch(c); /* push back */
			ungetch('.'); /* push back */
			/* If + or - was also read*/
			if(pm == TRUE)
				/*push back*/
				ungetch((sign == -1) ? '-' : '+'); 
			return 0;
		}
		ungetch(c); /* push back the digit after '.' */
		c = '.';
	}
	pow = 1;
	/* Before defimal point */
	for (*pn = 0.0; isdigit(c); c=getch())
		*pn = 10.0 * *pn + (c - '0');
	if (c == '.')
		/* After decimal point (if any) */
		for (c = getch(); isdigit(c); c=getch())
		{
			*pn = 10.0 * *pn + (c - '0');
			pow *= 10;
		}
	*pn /= pow;
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
