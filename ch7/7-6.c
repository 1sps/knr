/* Ex 7-6 K&R2  */
/*
   Write a program to compare two files , printing the first line where they
   differ.
*/
/* 2016-02-27 Sat 09:54 PM */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXLINE 200

typedef struct finfo /* structure storing filename */
{                    /* and file pointer */
	FILE *fp;
	char *fname;
} Finfo;

int compf(Finfo farr[]);
int printdiff(char *s1, char *s2, int linenum, Finfo farr[]);

/* compare two files */
int main(int argc, char *argv[]) 
{
	int i;
	Finfo farr[2];
	char *prog;

	prog = argv[0];
	if (argc != 3) /* if two filenames not given */
	{
		fprintf(stderr, "%s: error: incorrect call syntax\n", prog);
		exit(1);
	}
	farr[0].fname = argv[1]; /* store the filenames */
	farr[1].fname = argv[2]; /* in structure */

	i = 0;
	while (--argc > 0) 
	{
		if ((farr[i].fp = fopen(*++argv, "r")) == NULL) /* open the files */
		{
			fprintf(stderr, "%s: error: can't open %s\n", prog, argv);
			exit(2);
		}
		i++;
	}

	compf(farr); /* do the comparision */

	/* if any error with processing two files */
	if (ferror(farr[0].fp) || ferror(farr[1].fp))
	{
		for(i=0; i < 2; i++)
			fclose(farr[i].fp);
		exit(3);
	}

	for(i=0; i < 2; i++) /* close files */
		fclose(farr[i].fp);
		
	return 0;
}

/* compf: compare two files line by line */
int compf(Finfo farr[])
{
	int linenum;
	char w1[MAXLINE],w2[MAXLINE];
	char *fr1, *fr2;

	linenum = 1;
	while ((fr1 = fgets(w1, MAXLINE, farr[0].fp)) != NULL &&
	       (fr2 = fgets(w2, MAXLINE, farr[1].fp)) != NULL)
	{
		   if (strcmp(w1, w2) != 0)
				return printdiff(fr1, fr2, linenum, farr);
		   linenum++;
	}
	if ( fr1 == NULL)
	{
		if ((fr2 = fgets(w2, MAXLINE, farr[1].fp)) != NULL)
			return	printdiff(fr1, fr2, linenum, farr);
	}
	else if (fr2 == NULL)
		return printdiff(fr1, fr2, linenum, farr);
    return 0;
}

/* printdiff: print two differing lines */
int  printdiff(char *s1, char *s2, int linenum, Finfo farr[])
{
	printf("%s: %d: %s", farr[0].fname, linenum, s1 ? s1 : "\n");
	printf("%s: %d: %s", farr[1].fname, linenum, s2 ? s2 : "\n");
	return 1;
}

/* EOF */
