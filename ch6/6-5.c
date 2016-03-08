/* K&R2 Ex 6-5 */
/*
   Write a function undef that will remove a name and definition from the table
   maintained by lookup and install.
*/
/* ___: 2016-02-24 Wed 07:57 AM */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

int main(void)  /* test table functions */
{
	int i;
	char line[MAXLINE];
	char word[MAXWORD], defnword[MAXDEFN], 
	     *name, *defn, *p;
	struct nlist *plist;
	char uchoice[MAXLINE];

	int c;
	while (1)  /* run untill user quits by Ctrl-C */
	{
		printf("(insert/lookup/undef) ? (1/2/3) : ");

		fgets(uchoice, MAXLINE, stdin);
		uchoice[strlen(uchoice)-1] = '\0';

		if ((strlen(uchoice)) != 1)
		{
			printf("invalid choice\n");
			continue;
		}
		c = uchoice[0];
		if(c=='1')
			printf("enter name defn: ");
		else if(c=='2')
			printf("enter name to lookup: ");
		else if(c=='3')
			printf("enter name to undef: ");
		else
		{
			printf("invalid choice\n");
			continue;
		}

		if (getline1(line, MAXLINE) > 0)
		{
			p = line;
			while (*p == ' ' || *p == '\t')  /* skip blanks */
				p++;
			for (i = 0; *p != ' ' && *p != '\t' && *p != '\n'; p++, i++) /*get name */
				word[i] = *p;
			word[i] = '\0';
			name = strdup1(word);
		}
		else /* if input not got properly */
			continue;
		if (c == '1') /* install */
		{
			while(*p == ' ' || *p == '\t')  /* skip blanks before defn */
				p++;
			for (i = 0; *p != '\n' && *p != EOF; p++, i++)  /* get defn */
				defnword[i] = *p;
			defnword[i] = '\0';
			defn = strdup1(defnword);
			install(name, defn);
		}
		else if (c == '2')  /* lookup */
		{
			printf("searching the table for '%s' ...\n");
			if ((plist = lookup(name)) != NULL)
			{
				printf("lookup succesfull ...\n");
				printf("name: %s\ndefn: %s\n", plist->name, plist->defn);
			}
			else
				printf("no defn for '%s'\n", name);
		}
		else if (c == '3')  /* undef */
			undef(name);
	}
	return 0;
}

/*___*/
/*EOF*/
