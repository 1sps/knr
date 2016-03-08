/* Ex 7-3 K&R2 */
/* 
   Revise minprintf to handle more of the other facilities of printf
*/
/* 2016-02-25 Thu 05:06 AM */

/*
   Facilities added: 

   1. Length can be specified: ex %10d :  right aligned
   2. Length can be specified: ex %-10d : left aligned
   3. Decimal length can be specified: ex %10.5f
   4: String length can be specified : ex %-10.5%s
*/

#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAXDPLEN 100
#define MAXFSLEN 20

typedef enum 
{
	NONE, INT, FLT, STR
} Type;

typedef struct formatsp  /* format specifier struct */
{
	int tlen;   /* totel length */
	int rlen;   /* length of decimal part */
	int slen;   /* length of the string */
	Type  type; /* data type to print */
	char fs[MAXFSLEN]; /* format specifier string */
} Formatsp;

/* Function prototypes */
void minprintf(char *fmt, ...);
void dpbuffill(char *, char *, ...);
void adjdpbuf(char *dpbuf);
char *getfsp(char *);

Formatsp f;     /* format specifier variable */

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
	va_list ap; /* points to each argument in turn */
	char *p, *sval, dpbuf[MAXDPLEN];
	int ival, k;
	double dval;
	f.fs[0] = '\0';

	va_start(ap, fmt);  /* make ap point to first unnamed arh */
	for (p = fmt; *p; p++)
	{
		if (*p != '%')
		{
			putchar(*p);
			continue;
		}
		p = getfsp(++p);
		switch (*p)
		{
		 case 'd':
			f.type = INT;
			ival = va_arg(ap, int);
			dpbuffill(dpbuf, "@d",  ival);
			printf("%s", dpbuf);
			 break; 
		 case 'f':
			 dval = va_arg(ap, double); 
			f.type = FLT;
			dpbuffill(dpbuf, "@f",  dval);
			printf("%s", dpbuf);
			 break; 
		 case 's':
			sval = va_arg(ap, char *);
			f.type = STR;
			dpbuffill(dpbuf, "@s",  sval);
			printf("%s", dpbuf);
			break;
		 default:
		 	putchar(*p);
			break;
		}
		f.fs[0] = '\0';
		f.type = NONE;
	}
	va_end(ap);  /* clean up when done */
}

/* getfsp: get the format specifier */
char *getfsp(char *pfmt)
{
	char *pfmtbak = pfmt, temp[MAXFSLEN], *pfs = temp;
	int tlen, rlen, slen,  mflag = 0;

	tlen = rlen = slen = 0;
	if (*pfmt == '-' && (mflag = 1)) /* set '-' flag */
		if (isdigit(*(pfmt+1)))
			*pfs++ = *pfmt++;
		else
			return pfmtbak;

	while (isdigit(*pfmt)) 
		*pfs++ = *pfmt++; 
	*pfs = '\0';
	f.tlen = atoi(temp);  /* get the total wished len */
	if (mflag)
		f.tlen = -f.tlen;
	strncpy(f.fs, temp, strlen(temp) + 1);
	temp[0] = '\0';
	pfs = temp;

	if (*pfmt == '.')
	{
		strncat(f.fs, ".", 2);
		pfmt++;
		*pfs++ = *pfmt++;
		while (isdigit(*pfmt))
			*pfs++ = *pfmt++;
	}
	*pfs = '\0';
	f.rlen = atoi(temp); /* get the right side wished len */
	strncat(f.fs, temp, strlen(temp) + 1);
	f.slen = f.rlen;     /* because slen same as rlen */

	switch(*pfmt)
	{
		case 'd': case 'f': case 's':
			break;
		default:
			pfmt = pfmtbak; /* Ignore if not correct*/
			break;          /* type after % */
	}
	return pfmt;
}

/* dpbuffill: fill dpbuf */
void dpbuffill(char *dpbuf, char *dtstr, ...)
{
	va_list ap; int ival, k; double dval; char *sval;

	va_start(ap, dtstr);
	if(*dtstr == '@')
	{
		switch(*(dtstr+1))
		{
		case 'd':
			ival = va_arg(ap, int);
			snprintf(dpbuf, MAXDPLEN, "%d\0", ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			snprintf(dpbuf, MAXDPLEN, "%f\0", dval);
			break;
		case 's':
			for (sval = va_arg(ap, char *), k=0; *sval; sval++, k++) 
				dpbuf[k] = *sval;
			dpbuf[k] = '\0';
			break;
		default:
			printf("dpbuffill: error: invalid type\n");
			break;
		}
		 adjdpbuf(dpbuf);  /* adjust the dpbuf (according to lenghts specified
		                      in format sp)*/
	}
	else
		printf("dpbuffill: error: invalid call\n");
	va_end(ap);
}

/* adjdpbuf: adjust dpbuf */
void adjdpbuf(char *dpbuf)
{
	int fstlen, fsrlen, arlen = 0, i, lendiff, mflag = 0;
	char temp[MAXDPLEN], *p, *fsp;

	fsp = f.fs; /* pointer to format sp string */
	if (*fsp == '-' && fsp++) /* set '-' flag */
		mflag = 1;

	if (((lendiff = f.tlen - strlen(dpbuf)) <= 0)) /* Return if requested len */
		return;                                    /* too small */

	while (isdigit(*fsp))
		fsp++;
	if (*fsp == '.') /* if right side len also given */
		if (f.type == FLT)
		{
			for (p = strstr(dpbuf, ".") + 1; isdigit(*p); p++)
				arlen++;        /* actual len of right part */
			if (arlen > f.rlen) /* if actcual rlen is more than wished rlen */
				dpbuf[strlen(dpbuf) - (arlen - f.rlen)] = '\0';
		}
		else if (f.type == STR) /* remove extra chars for string */
			dpbuf[f.rlen] = '\0'; 
	lendiff = f.tlen - strlen(dpbuf); /* diff b/w wished len & actual len*/
	if (mflag)
		for(i = 0; i < lendiff; i++)
			strncat(dpbuf, " ", 2);  /* is this expensive? */
	else
	{
		strncpy(temp, dpbuf, strlen(dpbuf) + 1); /* copy dpbuf to (t)emp-dpbuf */
		for(i = 0, p = dpbuf; i < lendiff; i++)
			*p++ = ' ';
		*p = '\0';
		strncat(dpbuf, temp, strlen(temp) + 1);
	}
}

int main(void) /* test minprintf() */
{
	char c = 'B';
	int i = 19999;
	double d = 5.555555;
	double e = 1.666666;
	char s1[] = "Test";
	  minprintf("012345678901234567890123\n");
	      minprintf("%-11d%10.3f%10.2s\n", i, e, s1);    
	     minprintf("%-10d%-10.3fAND\n", i, e);   
	     minprintf("%10.2s%-10.2s\n", s1, s1);   
	     minprintf("%s  %f\n", s1, e);   

	return 0;
}

/* EOF */
