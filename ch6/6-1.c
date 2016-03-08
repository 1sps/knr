/* KNR2 Ex 6-1 */
/*
   Our version of getword does not properly handle underscores,
   string constants, comments, or preprocessor control lines. 
   Write a better version 
*/
/* ___: 2016-02-23 Tue 03:09 AM */

/* Header files */
#include<stdio.h>
#include<ctype.h>
#include<string.h>

/* Constants */
#define MAXWORD 100
/* macros */
/* #define NKEYS (sizeof keytab / sizeof(struct key)) */
#define NKEYS (sizeof keytab / sizeof keytab[0])

/* array of structure */
struct key 
{
	char *word;
	int count;
} keytab[] = {
                    "auto", 0,
                    "break", 0,
                    "case", 0,
                    "char", 0,
                    "const", 0,
                    "continue", 0,
                    "default", 0,
                    "do", 0,
                    "double", 0,
                    "else", 0,
                    "enum", 0,
                    "extern", 0,
                    "float", 0,
                    "for", 0,
                    "goto", 0,
                    "if", 0,
                    "int", 0,
                    "long", 0,
                    "register", 0,
                    "return", 0,
                    "short", 0,
                    "signed", 0,
                    "sizeof", 0,
                    "static", 0,
                    "struct", 0,
                    "switch", 0,
                    "typedef", 0,
                    "union", 0,
                    "unsigned", 0,
                    "void", 0,
                    "volatile", 0,
                    "while", 0,
					/* no c99 or c11 keywords */
                  };

/*Function protoypes*/
int getword(char *, int);
int binsearch(char *, struct key *, int);

/* main: count c keywords */
int main(void)
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count,
			    keytab[n].word);
	return 0;
}

/* binsearch: find words in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n-1;
	while (low <= high)
	{
		mid = (low+high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid -1;
		else if (cond  > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, d, getch(void);
	void ungetch(int);
	char *w = word;

	/* Flags */
	int strflag = 0;  /* 1 means inside string */
	int comflag = 0;  /* 1 means inside comment */
	int ppflag = 0;   /* 1 means inside preprocessor control line */
	int sqflag = 0;   /* 1 means inside single quote */

	while (isspace(c=getch()))
		;
	/* if this char starts a comment */
	if (c == '/')
		if ((d = getch()) == '*')
			comflag = 1;
		else
			ungetch(d);
	/* else if this char starts a string */
	else if (c == '"')
		strflag = 1;
	/* else if this char starts a preprocessor command */
	else if (c == '#')
		ppflag = 1;
	/* else if this char starts a character constant */
	else if (c == '\'')
		sqflag = 1;

	/* skip the string */
	if (strflag)
	{
		 while ((c = getch()) != '"' && c != EOF) 
			;
		 /* this cannot happen in a correct c program */
		 /* however implemented for such scenarios (incorrect c program) */
		 if (c == EOF) 
			 return c; 
		strflag = 0;
		c = getch();
	}
	/* skip the comment */
	if (comflag)
	{
		while ((c = getch()) != EOF)
		{
			if (c == '*')
				if ((d = getch()) == '/')
					break;
				else
					ungetch(d);
		}
		 if (c == EOF) 
			 return c; 
		comflag = 0;
		c = getch();
	}
	/* skip the preprocessor command line */
	/* Alse return new line */
	if (ppflag)
	{
		while (c = getch() != '\n' && c != EOF )
			;
		*word = '\n';
		return c;
	}
	/* skip the character constant */
	if (sqflag)
	{
		while (c = getch() != '\'' && c != EOF )
			;
		if (c == EOF)
			return c;
		sqflag = 0;
		c = getch();
	}

	if (c != EOF)
		*w++ = c;
		
	if (!isalpha(c))
	{
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_')
		{
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

/* Constants */
#define BUFSIZE 100

/* Buffer fot getch() and ungetch() */
char buf[BUFSIZE];
/* Next free position in buffer */
int bufp=0;

/* getch: This function gets a (possibly pushed back) character */
int getch(void)
{
	return (bufp>0) ? buf[--bufp] : getchar();
}

/* ungetch: This function pushes character back on input */
void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* EOF */
