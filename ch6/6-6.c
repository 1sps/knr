/* K&R2 Ex 6-6 */
/*
   Implement a simple version of the #define processor (i.e., no arguments)
   suitable for use with C programs, based on the routines of this section. You
   may dinf getch and ungetch helpful.
*/
/* ___: 2016-02-24 Wed 02:25 PM */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define HASHSIZE 101
#define MAXLINE  200
#define MAXWORD  50
#define MAXDEFN  195

struct nlist         /* table entry*/
{
	struct nlist *next;  /* next entry in chain */
	char *name;          /* defined name */
	char *defn;          /* replacement text */
};

static struct nlist *hashtab[HASHSIZE];  /* pointer table */

/*Function protoypes*/
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *, char *);
int getline1(char s[], int lim);
char *strdup1(char *);
int undef(char *);
int getword(char *word, int lim);
void ungetch(int c);
int getch(void);

int main(void)  /* #define processor */
{
	int i, res, c;
	struct nlist *plist, *temp;
	char line[MAXLINE], word[MAXWORD], defnword[MAXDEFN], 
	     *name, *defn, *p, uchoice[MAXLINE];

	while ((res = getword(word, MAXWORD)) != EOF)
	{
	   if (res == '#')  /* # received */
	   { 
		if (getline1(line, MAXLINE) > 0) 
		{
			p = line; 
			while (*p == ' ' || *p == '\t')  /* skip blanks */
				p++;
			for (i = 0; *p != ' ' && *p != '\t' && *p != '\n'; p++, i++) /*see if 'define' */
				word[i] = *p;
			word[i] = '\0';
			if (strcmp(word, "define"))
			{
				putchar('#');
				printf("%s", line);
				continue;
			}
			while (*p == ' ' || *p == '\t')  /* skip blanks */
				p++;
			for (i = 0; *p != ' ' && *p != '\t' && *p != '\n'; p++, i++) /*get name */
				word[i] = *p;
			word[i] = '\0';
			name = strdup1(word);
		}
		else /* if input not got properly */
			return printf("error while processing...\n");
		/* install */
		{
			while(*p == ' ' || *p == '\t')  /* skip blanks before defn */
				p++;
			for (i = 0; *p != '\n' && *p != EOF; p++, i++)  /* get defn */
				defnword[i] = *p;
			defnword[i] = '\0';
			defn = strdup1(defnword);
			install(name, defn);
		}
	  }
	  else if (isalpha(word[0]))
	  	if ((temp = lookup(word)) != NULL)
			printf("%s", temp->defn);
		else
			printf("%s", word);
	}
	return 0;
}
/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for(np = hashtab[hash(s)]; np != NULL; np=np->next)
		if (strcmp(s, np->name) == 0)
			return np;  /* found */
	return NULL;        /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL)    /* not found */
	{
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup1(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else        /* already there */
		free((void *) np->defn);  /* free previous defn */
	if ((np->defn = strdup1(defn)) == NULL)
		return NULL;
	return np;
}
/* undef: remove name and defn */
int undef(char *name)
{
	struct nlist *p, *q;
	int hashval;

	if ((p = lookup(name)) != NULL)  /* there in table */
	{
		hashval = hash(name);
		p = q = hashtab[hashval];
		for (;strcmp(q->name, name); p = q, q = q->next)
			;
		if (p == q)
			hashtab[hashval] = q->next;
		else if (q = p->next)
			p->next = q->next;

		free((void *) q->name);
		free((void *) q->defn);
		free((void *) q);
	}
	else  /* not there in table */
		return 0;
	return 1;
}

/* getline1: get a line from input */
int getline1(char s[], int lim)
{
	int c, i;
	for(i=0; (i<lim-1) * ((c=getchar()) != EOF) * (c != '\n');++i)
		s[i] = c;
	if(c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* strdup1: make a duplicate of s */
char *strdup1(char *s) 
{
	char *p;
	p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
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
		putchar(c);
	/* if this char starts a comment */
	if (c == '/')
	{
		putchar(c);
		if ((d = getch()) == '*')
		{
			putchar(d);
			comflag = 1;
		}
		else
			ungetch(d);
	}
	/* else if this char starts a string */
	else if (c == '"')
	{
		putchar(c);
		strflag = 1;
	}
	/* else if this char starts a preprocessor command */
	else if (c == '#')
		ppflag = 1;
	/* else if this char starts a character constant */
	else if (c == '\'')
	{
		putchar(c);
		sqflag = 1;
	}

	/* skip the string */
	if (strflag)
	{
		 while ((c = getch()) != '"' && c != EOF) 
			putchar(c);
		putchar(c);
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
				{
					putchar(c);
					putchar(d);
					break;
				}
				else
				{
					putchar(c);
					ungetch(d);
				}
			else
				putchar(c);
		}
		 if (c == EOF) 
			 return c; 
		comflag = 0;
		c = getch();
	}
	/* return '#' */
	if (ppflag)
	{
		*word = '\n';
		return '#';
	}
	/* skip the character constant */
	if (sqflag)
	{
		while (c = getch() != '\'' && c != EOF )
			putchar('T');
		if (c == EOF)
			return c;
		putchar('X');
		sqflag = 0;
		c = getch();
	}

	if (c != EOF)
		*w++ = c;
		
	if (!isalpha(c))
	{
		putchar(c);
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

#define BUFSIZE 100 /* size of the buffer */
char buf[BUFSIZE];  /* Buffer fot getch() and ungetch() */
int bufp=0;         /* Next free position in buffer */

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


/*___*/
/*EOF*/
