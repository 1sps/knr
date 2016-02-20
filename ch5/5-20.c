/* K&R2 5-20 */
/* ___: 2016-02-19 Fri 03:03 PM */

/* Expand dcl to handle declarations with function argument types, qualifiers like
   const, and so on. */

/* THIS CODE IS TOO MINIMAL- HANDLES ONLY SIMPLEST CASES */

/*Header files*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>
/*Constants*/
#define MAXTOKEN 100
#define SKIP

enum {NAME, PARENS, BRACKETS, QUAL, IGNORE};


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

char tqtoken[MAXTOKEN];
int tqflag = 0;
int tqtype = IGNORE;

/* Program starts */

int main(void) /* convert declarations to words */
{
	int ttype;
	while (gettoken() != EOF)             /* 1st token on line */
	{                                     /* is the data type */
		strcpy(datatype, token); 
		while ((ttype = gettoken()) == QUAL)
		{
			strcat(datatype, " "); 
			strcat(datatype, token); 
		}
		printf("tot qual: %s\n", datatype);
		/* Flag, tokentype, and token for extra token read */
		tqflag = 1;
		strcpy(tqtoken, token);
		tqtype = ttype;

		out[0] = '\0';
		if (dcl() == -1)                  /* parse the rest of line */
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
	int ns=0;

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
	else if (tokentype == QUAL)
	{
		strcat(datatype, " "); 
		strcat(datatype, token); 
		return 0;
	}
	else
	{
		printf("error: expected name of (dcl)\n");
		return -1;
	}
	while ((type=gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
		{
			strcat(out, " function");
			strcat(out, token);
			strcat(out, " returning");
		}
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
	char temptoken[MAXTOKEN];
	int i;

	/* Added to compensate for qual code */
	if (tqflag == 1)
	{
		tqflag = 0;
		strcpy(token, tqtoken);
		tokentype = tqtype;
		return tokentype;
	}
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(')
	{
		if ((c = getch()) == ')' || isalpha(c))
		{
			if (c == ')')
			{
				strcpy(token, "()");
				return tokentype = PARENS;
			}
			else /* argument list present for function */
			{
				ungetch(c);
				temptoken[0] = '(';
				i = 1;
				while ((temptoken[i++] = c = getch()) != ')')
					;	
				temptoken[i] = '\0';
				strcpy(token, temptoken);
				return tokentype = PARENS;
			}
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
		if ((strcmp(token, "static")) == 0)
			return tokentype = QUAL;
		else if ((strcmp(token, "const")) == 0) 
			return tokentype = QUAL;
		else if ((strcmp(token, "int")) == 0) 
			return tokentype = QUAL;
		else if ((strcmp(token, "char")) == 0) 
			return tokentype = QUAL;
		else if ((strcmp(token, "double")) == 0) 
			return tokentype = QUAL;
		printf("token: %s\n", token);
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
