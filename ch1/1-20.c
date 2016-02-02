/*___: 2016-01-20 Wed 06:28 AM*/

/*C program to replaces tab in the input
  +with the proper number of blanks to space the 
  +next tab-stop*/

/*Header files*/
#include<stdio.h>

/*Constants*/
#define TABSTOP 4
#define LINE_START 0
#define BLANK_START 0

/*Program starts*/
int main(int argc, char *argv[])
{
	/*Variables*/
	int c, count, i, blank_count;

	/*Begin a new line*/
	count = LINE_START;
	while((c=getchar()) != EOF)
	{
		/*Replace a tab with proper number of blanks*/
		if(c == '\t')
		{
			blank_count = TABSTOP - (count % TABSTOP);

			for(i = BLANK_START; i < blank_count; ++i)	
			{
				putchar(' ');
				++count;
			}
		}
		/*Else print the character, 
		  +and check if it is a newLine*/
		else
		{
			putchar(c);
			if(c == '\n')
				count = LINE_START;
			else
				++count;
		}
	}
	/*Program ends*/
	return 0;
}

/*___*/
/*EOF*/
