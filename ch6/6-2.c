/* Ex 6-2 K&R2 */
/* 
   Write a program that reads a c program and prints in alphabetical order each
   group of variable names that are identical in the first 6 characters, but
   different somewhere thereafter. Don't count words within strings and comments.
   Make 6 a parameter that can be set from the command line.
*/
/* ___: 2016-02-23 Tue 09:26 PM */

/* Header files */
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

/* Constants */
#define MAXWORD 100
#define GLEN    6

/* self referential structure */
struct gnode             /* the tree node: */
{
	char *word;          /* points to the text */
	int count;           /* number of occurrences */
	struct gnode *left;  /* left child*/
	struct gnode *right; /* right child */
};

/* Function protoypes */
struct gnode *addgtree(struct gnode *, char *);
void gtreeprint(struct gnode *);
int getword(char *, int);

/* word frequency count */
int main(int argc, char *argv[])
{
	/* struct tnode *root; */
	struct gnode *root;
	char word[MAXWORD];
	char gword[MAXWORD];  /* stores group name */
	int glen = GLEN;

	if (argc == 2)
		if ((glen = atoi(argv[1])) <= 0)
			glen = GLEN;
	
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && strlen(word) >= glen)
		{
			strncpy(gword, word, glen);
			gword[glen] = '\0';
			root = addgtree(root, gword);
		}
	gtreeprint(root);
	return 0;
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

struct gnode *galloc(void);
char *strdup1(char *);

/* gaddtree: add a node in group w, at or below p */
struct gnode *addgtree(struct gnode *p, char *w)
{
	int cond;

	if (p == NULL)
	{                                 /* a new group has arrived */
		p = galloc();                 /* make a new node */
		p->word = strdup1(w);
		p->count = 1;
		p->left = p->right =  NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;   /* repeated word */
	else if (cond < 0) /* less than into left subtree */
		p->left = addgtree(p->left, w);
	else if (cond > 0) /* greater than into tight subtree */
		p->right = addgtree(p->right, w);
	return p;
}

/* gtreeprint: in-order print of gtree p */
void gtreeprint(struct gnode *p)
{
	if (p != NULL)
	{
		gtreeprint(p->left);
		printf("%4d: %s\n", p->count, p->word);
		gtreeprint(p->right);
	}
}

/* galloc: make a gnode */
struct gnode *galloc(void)
{
	return (struct gnode *) malloc(sizeof(struct gnode));
}

char *strdup1(char *s) /* make a duplicate of s */
{
	char *p;
	p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* EOF */
