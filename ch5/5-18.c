/* K&R2 5-18 */
/* ___: 2016-02-19 Fri 03:03 PM */

/* C program to translate c declaration to eglish words */
/* dcl() recovers from error: It detects errors and returns error as soon as */
/* detected */

/*Header files*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>

/*Constants*/
#define MAXTOKEN 100
#define SKIP

enum {NAME, PARENS, BRACKETS};


/* Function protoypes */

#ifndef SKIP
void dcl(void);
void dirdcl(void);
#endif
int dcl(void);
int dirdcl(void);

int gettoken(void);

/* External variables */

int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name*/
char datatype[MAXTOKEN];  /* data type = int, char, etc. */
char out[1000];           /* output string */

/* Program starts */

int main(void) /* convert declarations to words */
{

	int deb;

	while (gettoken() != EOF)             /* 1st token on line */
	{                                     /* is the data type */
		strcpy(datatype, token); 
		out[0] = '\0';
		if ((deb=dcl()) == -1)         /* parse the rest of line */
			;
		else
		{
			if (tokentype != '\n')
				printf("syntax error\n");
			else
				printf("%s: %s %s\n", name, out, datatype);
		}
	}
	return 0;
}


int dcl(void) /* with error recovery */
{
	int ns;

	for (ns = 0; gettoken() == '*';)
		ns++;
	if(dirdcl() == -1)
		return -1;
	while (ns-- > 0)
		strcat(out, " pointer to");
	return 0;
}

int dirdcl(void) /* with error recovery */
{
	int type;
	int nflag = 0;

	if (tokentype == '(')  /* ( dcl )*/
	{
		if (dcl() == -1)
			return -1;
		if (tokentype != ')')
		{
			printf("error missing )\n");
			return -1;
		}
	}
	else if (tokentype == NAME)
	{
		/* printf("token type 'name' received\n"); */
		strcpy(name, token);
	}
	else
	{
		printf("error: expected name of (dcl)\n");
		return -1;
	}
	while ((type=gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
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

/* This is for getch() and ungetch() */

/*Constants*/
#define BUFSIZE 100

/*External variables*/
/*Buffer fot getch() and ungetch()*/
char buf[BUFSIZE];
/*Next free position in buffer*/
int bufp=0;

/*getch() function definition*/
/*Get a (possibly pushed back) character*/
int getch(void)
{
	return (bufp>0) ? buf[--bufp] : getchar();
}

/*ungetch() function definition*/
/*Push character back on input*/
void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/*EOF*/
