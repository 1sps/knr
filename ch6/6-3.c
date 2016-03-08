/* Ex 6-3 K&R2 */
/* 
   Write a cross-referencer that prints a list of all words in a document, and,
   for each word, a list of line numbers on which it occurs. Remove noise words
   like "the", "and", and so on.
*/
/* ___: 2016-02-23 Tue 11:26 PM */

/* Header files */
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAXWORD 100      /* maximum length of a word */

/* ln structure */
struct ln                /* the lntree node: */
{
	int linenum;         /* contains the line number */
	struct ln *left;     /* left child */
	struct ln *right;    /* right child */
};
/* wnode structure */
struct wnode             /* the wtree node: */
{
	char *word;          /* points to the text */
	int count;           /* number of occurrences */
	struct ln *pln;      /* points to the line number structure */
	struct wnode *left;  
	struct wnode *right; 
};
/* noise word structure */
struct noiseword
{
	char *nword;         /* points to noise a word */
	struct noiseword *left;  
	struct noiseword *right;
};

int lnum = 1;            /* track line number */

/* Function protoypes */
struct wnode *addwtree(struct wnode *, char *);
void wtreeprint(struct wnode *);
int lntreeprint(struct ln *);
int getword(char *, int);
struct ln *waddline(struct ln *);
struct ln *lnalloc(void);
struct wnode *walloc(void);
char *strdup1(char *);
struct noiseword *mknwtree(struct noiseword *, char *[]);
struct noiseword *nwtreeadd(struct noiseword *, char **);
struct noiseword *nwalloc(void);
int isnoise(struct noiseword *, char *);
void printnwtree(struct noiseword *nwroot);

/* word line numbers count */
int main(int argc, char *argv[])
{
	struct wnode *root;
	char word[MAXWORD];

	/* noise words array */
	/*this array can have more words
	  however only few are chosen for brevity */
	char *nw[] = {
	               "the",
	               "and",
	               "or",
	               "in",
	               "at",
	               "on",
				   NULL };

	struct noiseword *nwroot = NULL;
	/* make a tree of noise words - searching will be faster */
	nwroot = mknwtree(nwroot, nw); 

	/* populate and print the word list */
	root = NULL;
	 while (getword(word, MAXWORD) != EOF) 
		if (isalpha(word[0]))
		{
			if (!isnoise(nwroot, word))
				root = addwtree(root, word);
		}
		 else if (word[0] == '\n') 
			lnum++;  /* increment the line number */
	wtreeprint(root);

	return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c=getch()) && c != '\n')
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c))
	{
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch()))
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

/* addwtree: add a word node, at or below p */
struct wnode *addwtree(struct wnode *p, char *w)
{
	int cond;

	if (p == NULL)
	{                                 /* a new word has arrived */
		p = walloc();                 /* make a new node */
		p->word = strdup1(w);
		p->count = 1;
		p->pln = NULL;
		p->pln = waddline(p->pln);    /* add line number of occurrence */
		p->left = p->right =  NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
	{
		p->count++;    /* repeated word */
		waddline(p->pln);
	}
	else if (cond < 0) /* less than into left subtree */
		p->left = addwtree(p->left, w);
	else if (cond > 0) /* greater than into tight subtree */
		p->right = addwtree(p->right, w);
	return p;
}

/* wtreeprint: in-order print of wtree p */
void wtreeprint(struct wnode *p)
{
	if (p != NULL)
	{
		wtreeprint(p->left);
		printf("%15s:    ", p->word);
		lntreeprint(p->pln);
		putchar('\n');
		wtreeprint(p->right);
	}
}

/* walloc: make a wnode */
struct wnode *walloc(void)
{
	return (struct wnode *) malloc(sizeof(struct wnode));
}

/* waddline: add a line number for the word */
struct ln *waddline(struct ln *p)
{
	struct ln *lnp;

	lnp = p;
	if (lnp == NULL)
	{
		lnp = lnalloc();
		lnp->linenum = lnum;
		lnp->left = lnp->right =  NULL;
	}
	else if (lnp->linenum == lnum)
		;
	else if (lnum < lnp->linenum)
		lnp->left = waddline(lnp->left);
	else if (lnum > lnp->linenum)
		lnp->right = waddline(lnp->right);
	return lnp;
}

/* lnalloc: make a ln node */
struct ln *lnalloc(void)
{
	return (struct ln *) malloc(sizeof(struct ln));
}

/* lntreeprint: in-order print of lntree p */
int lntreeprint(struct ln *p)
{
	int flag;
	if (p != NULL)
	{
		if ((flag = lntreeprint(p->left)) == 1)
			printf(", ");
		printf("%d", p->linenum);
		if (p->right)
			printf(", ");
		lntreeprint(p->right);
		return 1;
	}
	else
		return -1;
}

/* mknwtree: populate/make the noise word tree */
struct noiseword *mknwtree(struct noiseword *nwroot, char *nwa[])
{
	struct noiseword *nwp;
	if (*nwa != NULL)
		nwp = nwtreeadd(nwroot, nwa++);
	while (*nwa != NULL)
		nwtreeadd(nwp, nwa++);
	return nwp;
}

/* nwtreeadd: add a word to noiseword tree */
struct noiseword *nwtreeadd(struct noiseword *nwroot, char **nwa)
{
	int cond;
	struct noiseword *nwp = nwroot;

	/* new noise word arrived */
	if (nwp == NULL)
	{
		nwp = nwalloc();
		nwp->nword = strdup1(*nwa);
		nwp->left = nwp->right = NULL;
	}
	/* nothing to do if noiseword already in tree */
	else if ((cond = strcmp(*nwa, nwp->nword)) == 0)
		;
	else if (cond < 0)
		nwp->left = nwtreeadd(nwp->left, nwa);
	else if (cond > 0)
		nwp->right = nwtreeadd(nwp->right, nwa);
	return nwp;
}

/* nwalloc: make a noise word node */
struct noiseword *nwalloc(void)
{
	return (struct noiseword *) malloc(sizeof(struct noiseword));
}

/* isnoise: check if word is a noise word */
int isnoise(struct noiseword *nwroot, char *word)
{
	int res, cond;
	struct noiseword *nwp = nwroot;

	if (nwp == NULL)
		return 0;
	else if ((cond = strcmp(word, nwp->nword)) == 0)
		return 1;
	else if (cond < 0)
		res = isnoise(nwp->left, word);
	else if (cond > 0)
		res = isnoise(nwp->right, word);
	return res;
}

/* printnwtree: in order print of noise word tree */
void printnwtree(struct noiseword *nwroot)
{
	if (nwroot != NULL)
	{
		printnwtree(nwroot->left);
		printf("%s\n", nwroot->nword);
		printnwtree(nwroot->right);
	}
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

/* EOF */
