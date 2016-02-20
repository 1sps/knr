/* K&R2 5-7*/

/*Header files*/
#include<stdio.h>
#include<string.h>

/*Constants*/
#define MAXLINES 5000  /* Max #lines to read */
#define MAXLEN   1000  /* max length of any input line */

/* External data */
char *linptr[MAXLINES]; /* pointers to text lines */

/*Function protoypes*/
int readlines(char *lineptr[], char linebuf[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(char *lineptr[], int left, int right);

/*Program starts*/
int main(void)
{
	int nlines; /* number of input lines read */
	char linebuf[MAXLEN * MAXLINES];
	char *lineptr[MAXLINES];

	if ((nlines = readlines(lineptr, linebuf, MAXLINES)) > 0)
	{
		qsort1(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("error: input too big to sort\n");
		return 1;
	}
}

int getline1(char *, int);

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
void qsort1(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);
	
	if (left >= right)  /* do nothing if array contains */
		return;         /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) 
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort1(v, left, last);
	qsort1(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/*___*/
/*EOF*/
