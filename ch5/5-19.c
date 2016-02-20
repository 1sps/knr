/* KNR2 5-19 */
/* ___: 2016-02-19 Fri 07:14 PM */
/* C program to convert human description to C declaration, without adding
   redundant parenthesis  */

/*Header files*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>

/*Constants*/
#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};

/* Function protoypes */

void dcl(void);
void dirdcl(void);

int gettoken(void);

/* External variables */

int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name*/
char datatype[MAXTOKEN];  /* data type = int, char, etc. */
char out[1000];           /* output string */

/* Program starts */

/* undcl: c to words */
/* undcl: words to c */
int main(void)
{
	int type;
	char temp[MAXTOKEN];
	int typeextraflag = 0; /* 1 indicates one extra token has been read */
	int typeextra;         /* type of extra token read */

	while (gettoken() != EOF)
	{
		strcpy(out, token);
		while ((type = (typeextraflag ? typeextra : gettoken())) != '\n')
		{
			if(typeextraflag == 1)
				typeextraflag = 0;
			if (type == PARENS || type == BRACKETS)
			{
				strcat(out, token);
			}
			else if (type == '*')
			{
				typeextra = gettoken(); /* read an extra token everytime after */
				typeextraflag = 1;      /* a pointer to see if next token  is a parens or
				                           a brackets */
				/* if needed put parenthesis around the pointer*/
				if (typeextra == PARENS || typeextra == BRACKETS) 
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			}
			else if (type == NAME)
			{
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else
				printf("invalid input at %s\n", token);
		}
		printf("%s\n", out);
	}
	return 0;
}

int gettoken(void) /* return next token */
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(')
	{
		if ((c = getch()) == ')')
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else
		{
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[')
	{
		for (*p++ = c; (*p++ = getch()) != ']';)
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c))
	{
		for (*p++ = c; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
		return tokentype = c;
}

/*Constants*/
#define BUFSIZE 100

/*Buffer fot getch() and ungetch()*/
char buf[BUFSIZE];
/*Next free position in buffer*/
int bufp=0;

/*Get a (possibly pushed back) character*/
int getch(void)
{
	return (bufp>0) ? buf[--bufp] : getchar();
}

/*Push character back on input*/
void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/*___*/
/*EOF*/
