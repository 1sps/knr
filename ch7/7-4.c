/* Ex 7-4 K&R2 */
/* pscanf.c  */

/* 2016-02-27 Sat 04:14 AM */

#include<stdio.h>
#include<stdarg.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXNLEN 100

/* function prototypes */
void pscanf(char *fmt, ...);
int getint(void);
double getflt(void);
char * getstr(char *);
int getch(void);

/* main: test pscanf */
int main(void) 
{
	int i;
	float f;
	char c, str[100];

	pscanf("%c%d  %f	%s", &c, &i, &f, str);
	printf("c: %c, i: %d, f: %f, str: %s\n", c, i, f, str);
	return 0;
}

/* pscanf: minimal scanf */
void pscanf(char *fmt, ...)
{
	va_list ap;
	int *iptr;
	float *fptr;
	char *cptr, *sptr, *p;

	va_start(ap, fmt);
	for (p=fmt; *p != '\0'; p++)
	{
		if (*p != '%')
			continue;
		switch (*++p)
		{
		case 'c':
			cptr = va_arg(ap, char *);
			*cptr = getch();
			break;
		case 'd':
			iptr = va_arg(ap, int *);
			*iptr = getint();
			break;
		case 'f':
			fptr = va_arg(ap, float *);
			*fptr = getflt();
			break;
		case 's':
			sptr = va_arg(ap, char *);
			sptr = getstr(sptr);
			break;
		default:
			break;
		}
	}
	va_end(ap);
}

/* getc: get a char from input */
int getch(void)
{
	return getchar();
}

/* getint: get an integer from input */
int getint(void)
{
	int c, num;

	num = 0;
	while ((c=getchar()) == ' ' || c == '\t')
		;
	do
		num = 10 * num + (c - '0');
	while (isdigit(c = getchar()) && c != '\n');
	if (c == EOF)
		printf("getint: error: EOF received\n");

	return num;
}

/* getflt: get a float from input */
double getflt(void)
{
	int c;
	double num;
	char fs[MAXNLEN], *pfs = fs;

	while ((c=getchar()) == ' ' || c == '\t')
		;
	do
		*pfs++ = c;
	while (isdigit(c = getchar()));
	if (c == '.')
	{
		*pfs++ = c;
		while(isdigit(c=getchar()))
			*pfs++ = c;
	}
	*pfs = '\0';
    num = atof(fs);
	return num;
}

/* getstr: get a string from input */
char *getstr(char *cptr)
{
	char *p = cptr;
	int c;

	while(!isspace(c=getchar()))
		*p++ = c;
	*p = '\0';

	return cptr;
}

/* EOF */
