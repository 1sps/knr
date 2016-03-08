/* Ex 6-4 K&R2 */
/* 
   Write a program that prints the distinct words in its input sorted into
   decreasing order of frequency of occurrence. Precede each words by its 
   count.
*/
/* ___: 2016-02-24 Wed 05:40 AM */

/* Header files */
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAXWORD 100      /* maximum length of a word */

/* wnode structure */
struct wnode             /* the wtree node: */
{
	char *word;          /* points to the text */
	int count;           /* number of occurrences */
	struct wnode *left;  
	struct wnode *right; 
};

/* Function protoypes */
struct wnode *addwtree(struct wnode *, char *);
void wtreeprint(struct wnode *);
int getword(char *, int);
struct wnode *walloc(void);
char *strdup1(char *);
struct wnode *fswtree(struct wnode *froot, struct wnode *root);
void fswtreeins(struct wnode *froot, struct wnode *nfnode);
struct wnode *func3(struct wnode *froot, struct wnode *nfnode);
void dwtreeprint(struct wnode *p);

/* word line numbers count */
int main(int argc, char *argv[])
{
	struct wnode *root;
	char word[MAXWORD];

	/* populate and print the word list */
	root = NULL;
	 while (getword(word, MAXWORD) != EOF) 
		if (isalpha(word[0]))
				root = addwtree(root, word);

	/* make a new tree sorted by frequency */
	struct wnode *froot = NULL;
	froot = fswtree(froot, root);
	/* print frequence-wise sorted tree */
	 dwtreeprint(froot); 

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
		p->left = p->right =  NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
	{
		p->count++;    /* repeated word */
	}
	else if (cond < 0) /* less than into left subtree */
		p->left = addwtree(p->left, w);
	else if (cond > 0) /* greater than into tight subtree */
		p->right = addwtree(p->right, w);
	return p;
}

/* fswtree: copy wtree to frequecy sorted wtree */
struct wnode *fswtree(struct wnode *froot, struct wnode *root)
{
	/* make root node of wtree the root node of fswtree */
	if (froot == NULL && root != NULL)
	{
		froot = walloc();
		froot->word = strdup1(root->word);
		froot->count = root->count;
		froot->left = NULL;
		froot->right = NULL;
	}

	/* populate fswtree with contents of wtree */
	fswtreeins(froot, root);

	return froot;
}

/* fswtreeins: insert a node in fswtree */
void fswtreeins(struct wnode *froot, struct wnode *nfnode)
{
	if(nfnode != NULL)
	{
		fswtreeins(froot, nfnode->left);
		  if (strcmp(nfnode->word, froot->word) != 0)  
			func3(froot, nfnode);
		fswtreeins(froot, nfnode->right);
	}
}

/* func3: insert each node from previous tree to freq sorted tree */
struct wnode *func3(struct wnode *froot, struct wnode *nfnode)
{
	struct wnode *p = froot;

	if (p == NULL)
	{
		p = walloc();
		p->word = strdup1(nfnode->word);
		p->count = nfnode->count;
		p->left = NULL;
		p->right = NULL;
	}
	else if (nfnode->count < p->count)
		p->left = func3(p->left, nfnode);
	else if (nfnode->count >= p->count)
		p->right = func3(p->right, nfnode);
	return p;
}


/* wtreeprint: in-order print of wtree p */
void wtreeprint(struct wnode *p)
{
	if (p != NULL)
	{
		wtreeprint(p->left);
		printf("%15s: %d\n", p->word, p->count);
		wtreeprint(p->right);
	}
}

/* dwtreeprint: (decresing) in-order print of wtree p */
void dwtreeprint(struct wnode *p)
{
	if (p != NULL)
	{
		dwtreeprint(p->right);
		printf("%10d: %s\n",p->count, p->word);
		dwtreeprint(p->left);
	}
}

/* walloc: make a wnode */
struct wnode *walloc(void)
{
	return (struct wnode *) malloc(sizeof(struct wnode));
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
