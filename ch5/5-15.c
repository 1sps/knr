/* K&R2 5-15:  Add -f option to fold upper and lower case  */
/* ___: 2016-02-17 Wed 10:45 PM */

/*Header files*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Constants*/
#define MAXLINES 5000  /* Max #lines to read */
#define MAXLEN   1000  /* max length of any input line */

/* External data */
char *lineptr[MAXLINES]; /* pointers to text lines */

/*Function protoypes*/
int readlines(char *lineptr[], char linebuf[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *lineptr[], int left, int right,
            int (*comp)(void *, void *), int reverse);
int getline1(char s[], int lim);
int numcmp(char *, char *);
void getopt(char *argv[], int *numeric, int *reverse, int *foldul);

/*Program starts*/
int main(int argc, char *argv[])
{
	int nlines; /* number of input lines read */
	int numeric = 0; /* 1 if numeric sort */
	int reverse = 0; /* 1 if reverse sort */
	int foldul = 0; /* 1 if folding upper and lower */

	/* storage supplied by main */
	char linebuf[MAXLEN * MAXLINES];

	/* check options */
	if (argc > 1)
		getopt(argv, &numeric, &reverse, &foldul);

	/* read - sort - write */
	if ((nlines = readlines(lineptr, linebuf, MAXLINES)) > 0)
	{
		qsort1((void **) lineptr, 0, nlines -1, 
		       (int (*)(void *, void *))(numeric ? numcmp : (foldul ? strcasecmp
			   : strcmp)), reverse);
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
void getopt(char *argv[], int *numeric, int *reverse, int *foldul)
{
	int i;
	
	for (i= 1; argv[i] != NULL; ++i)
	{
		if (strcmp(argv[i], "-n") == 0)
			*numeric = 1;
		else if (strcmp(argv[i], "-r") == 0)
			*reverse = 1;
		else if (strcmp(argv[i], "-f") == 0)
			*foldul = 1;
	}
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
            int (*comp)(void *, void *), int reverse)
{
	int i, last;
	void swap(void *v[], int i, int j);
	
	if (left >= right)  /* do nothing if array contains */
		return;         /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	if(reverse == 1)
	{
		for (i = left + 1; i <= right; i++) 
			if ((*comp)(v[i], v[left]) > 0)
				swap(v, ++last, i);
	}
	else if(reverse == 0)
	{
		for (i = left + 1; i <= right; i++) 
			if ((*comp)(v[i], v[left]) < 0)
				swap(v, ++last, i);
	}
	swap(v, left, last);
	qsort1(v, left, last, comp, reverse);
	qsort1(v, last+1, right, comp, reverse);
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

/*___*/
/*EOF*/
