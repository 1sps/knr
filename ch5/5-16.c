/* K&R2 5-16:  Add the -d ("directory order") option, which makes comparisions only
 * on letters numbers and blanks. Make sure it works in conjunction with -f */
/* ___: 2016-02-17 Wed 10:45 PM */

/*Header files*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

/*Constants*/
#define MAXLINES 5000  /* Max #lines to read */
#define MAXLEN   1000  /* max length of any input line */

/* External data */
char *lineptr[MAXLINES]; /* pointers to text lines */

/*Function protoypes*/
int readlines(char *lineptr[], char linebuf[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *lineptr[], int left, int right,
            int (*comp)(void *, void *), int reverse, int dirorder);
int getline1(char s[], int lim);
int numcmp(char *, char *);
int getopt(char *argv[], int *numeric, int *reverse,
            int *foldcase, int *diroder);
/* void strfcpy(char dest[], char src[]); */
void strfcpy(char[], char src[]);

/*Program starts*/
int main(int argc, char *argv[])
{
	int nlines; /* number of input lines read */
	int numeric = 0;  /* 1 if numeric sort */
	int reverse = 0;  /* 1 if reverse sort */
	int foldcase = 0; /* 1 if folding case */
	int dirorder = 0; /* 1 if "directory order" comparision */

	/* storage supplied by main */
	char linebuf[MAXLEN * MAXLINES];

	/* check options */
	if (argc > 1)
		if (getopt(argv, &numeric, &reverse, &foldcase, &dirorder) == -1)
			return 2;

	/* read - sort - write */
	if ((nlines = readlines(lineptr, linebuf, MAXLINES)) > 0)
	{
		qsort1((void **) lineptr, 0, nlines -1, 
		       (int (*)(void *, void *))(numeric ? numcmp : (foldcase ? strcasecmp
			   : strcmp)), reverse, dirorder);
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("error: input too big to sort\n");
		return 1;
	}
	return 0;
}

/* getopt(): read command line options */
int getopt(char *argv[], int *numeric, int *reverse,
           int *foldcase, int *dirorder)
{
	int i;
	
	for (i= 1; argv[i] != NULL; ++i)
	{
		if (strcmp(argv[i], "-n") == 0)
			*numeric = 1;
		else if (strcmp(argv[i], "-r") == 0)
			*reverse = 1;
		else if (strcmp(argv[i], "-f") == 0)
			*foldcase = 1;
		else if (strcmp(argv[i], "-d") == 0)
			*dirorder = 1;
		else
		{
			printf("error: invalid option: %s\n", argv[i]);
			return -1;
		}
	}
	return 0;
}


/* readlines: read input lines */
int readlines(char *lineptr[], char linebuf[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	p = linebuf; /* point to first char of storage provided by main */

	nlines = 0;
	while ((len = getline1(line, MAXLEN)) > 0)
		if (nlines >= maxlines)
			return -1;
		else
		{
			line[len-1] = '\0';  /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += strlen(p) + 1;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/*getline1() function definition*/
int getline1(char s[], int lim)
{
	/*Get a line from stdin and
	  +return its length
	*/
	int c, i;
	for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if(c == '\n')
	{
		s[i]='\n';
		++i;
	}
	s[i]='\0';
	return i;
}

/* qsort: sort v[left] ... v[right] into increasing order */
void qsort1(void *v[], int left, int right, 
            int (*comp)(void *, void *), int reverse, int dirorder)
{
	int i, last;
	void swap(void *v[], int i, int j);
	char tvi[MAXLEN], tvleft[MAXLEN];
	
	if (left >= right)  /* do nothing if array contains */
		return;         /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;

	/* If dirorder then copy the original string
	   to a temporary string with correct filtering */
	if (dirorder == 1)
		strfcpy(tvleft, v[left]);
	/* Else copy verbatim */
	else
		strncpy(tvleft, v[left], strlen(v[left]) + 1);
	for (i = left + 1; i <= right; i++) 
	{
		/* for dirorder */
		if (dirorder == 1)
			strfcpy(tvi, v[i]);
		/* else copy verbatim */
		else
			strncpy(tvi, v[i], strlen(v[i]) + 1);

		if (reverse == 1)	
		{
			if ((*comp)(tvi, tvleft) > 0) 
				swap(v, ++last, i);
		}
		else if (reverse == 0)	
			if ((*comp)(tvi, tvleft) < 0) 
				swap(v, ++last, i);
	}

	swap(v, left, last);
	qsort1(v, left, last, comp, reverse, dirorder);
	qsort1(v, last+1, right, comp, reverse, dirorder);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* strfcpy(): copy src to dest filtering only letters, numbers, and blanks */
void strfcpy(char dest[], char src[])
{
		static int count = 1;
	char c, *dest1 = dest, *src1=src;

	while ((c = *src1++) != '\0')
		if (isalpha(c) || isdigit(c) || isblank(c))
			*dest1++ = c;
	*dest1 = '\0'; /* null terminate */
}

/*___*/
/*EOF*/
