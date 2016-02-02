/*Source file for getop*/
/*___: 2016-01-30 Sat 05:56 PM*/

/*Header files*/
#include<stdio.h>
#include<ctype.h>
#include"calc.h"

/*getop() function definition*/
int getop(char s[])
{
	/*Automatic variables*/
	int i, c=-1;
	/*Static internal variables*/
	static int ugtc=EOF; /*Stores the ungetted c*/

	/*Ex 4-11 : Not a good way to solve*/
	/*but meets the conditions*/
	if(ugtc != EOF)
	{
		c = ugtc;
		ugtc = EOF;
	}
	/*if added before while modified for 4-11*/
	if(c == -1 || c == ' ' || c == '\t')
		while((s[0]=c= getch()) == ' ' || c == '\t')
			;
	s[1]='\0';
	/*Return the char if not a number*/
	/*This maybe an operator (+,-,*,/)*/
	if(!isdigit(c) && c!='.')
		return c;

	/*Else if a number starts,*/
	/*+store the number*/
	i=0;
	/*Collect the number*/
	if(isdigit(c))
		/*Collect the integer part*/
		while(isdigit(s[++i] = c = getch()))
			;
	if(c=='.')
	/*Collect the fraction part*/
	while(isdigit(s[++i] = c = getch()))
		;
	s[i]='\0';
	if(c != EOF)
		/*ungetch(c);*/
		ugtc = c; //4-11
	/*Indicate a number in return*/
	return NUMBER;
}

/*___*/
/*EOF*/
