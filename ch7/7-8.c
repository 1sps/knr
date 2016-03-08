/* Ex 7-8 K&R2  */
/*
   Write a program to print a set of files, starting each one on a new page,
   with a title and running page count for each file.
*/

#include<stdio.h>
#include<stdlib.h>

#define PAGEHEIGHT 50
#define MAXLINE 250

/* fileinfo structure */
typedef struct fileinfo
{
	FILE *fp;
	char *fname;
} Finfo;

int lcount = 0; /* line count */
int pcount = 0; /* page count */

/* function prototypes */
void fdisp(Finfo finfo);
void newpage(void);
void tpcdisp(char *name);

/* main: dislay files */
int main(int argc, char *argv[])
{
	char *prog;
	FILE *fp;
	Finfo finfo;

	prog = argv[0];
	if (argc < 2) /* if filnames not given */
	{
		fprintf(stderr, "%s: error: incorrect call\n",
		    prog);
		exit(1);
	}

	while (--argc > 0)  /* for each file */
	{
		if ((finfo.fp = fopen(*++argv, "r")) == NULL)
		{
			fprintf(stderr, "%s: error: can't open %s\n", 
			    prog, *argv);
			continue;
		}
		finfo.fname = *argv;
		fdisp(finfo);  /* display file */
		if (ferror(finfo.fp))
			fprintf(stderr, "%s: error: processing error\n");
		fclose(finfo.fp);
	}
	return 0;
}

/* fdisp: display file */
void fdisp(Finfo finfo)
{
	char p[MAXLINE];

	/* start new page if needed */
	if (lcount % PAGEHEIGHT != 0)
		newpage();
	pcount = 0; /* restart page count */

	while (fgets(p, MAXLINE, finfo.fp) != NULL) /* display contents */
	{
		if (lcount % PAGEHEIGHT == 0) /* if new page starts, then */
			tpcdisp(finfo.fname);      /* display title and page count */
		printf("%s", p);
		lcount++;
	}
}

/* newpage: start a new page */
void newpage(void)
{
	while (lcount % PAGEHEIGHT != 0) /* skip lines untill new page */
	{
		printf("\n");
		lcount++;
	}
}

/* void tpcdisp: display title and page count */
void tpcdisp(char *name)
{
	pcount ++;
	printf("Filename: %s\tPage num: %d\nx===x\n\n", name, pcount);
	lcount += 3;
}

/* EOF */
