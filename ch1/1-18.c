/*___: 2016-01-20 Wed 03:18 AM*/
/*K&R 2nd Ed, Ex 1-17*/

/*C program to remove tailing blanks and tabs from each line of input*/
/*Also delete entirely blank line*/

/*This program is does not work if there are more than 
+100 blanks or tabs*/
/*So this program could be made better*/

/*Header files*/
#include<stdio.h>

/*Constants*/
#define MAX_WHITE_SPACE 100
#define TRUE 1
#define FALSE 0
#define RESET_INDEX -1

/*Function prototypes*/
void truncate_blanks_tabs();

/*Program starts*/
int main(int argc, char *argv[])
{
	truncate_blanks_tabs();
	/*Program ends*/
	return 0;
}

/*Function definition*/
void truncate_blanks_tabs()
{
	/*Variables*/
	int c, index, i, entirely_blank;
	char whiteSpace[MAX_WHITE_SPACE];

	/*Index value -1 suggests nothing in whiteSpace[]*/
	index = RESET_INDEX ;
	/*entire_blank value of TRUE suggests that the line is blank upto now*/
	entirely_blank = TRUE;

	/*Read each character*/
	while((c = getchar()) != EOF)
	{
		/*Store the whitespace in whiteSpace[]*/
		if(c == ' ' || c == '\t')	
		{
			++index;
			whiteSpace[index] = c;
		}
		/*If a non-blank, non-newLine character appears 
		  +print all the whitespace before it(if exist),
		  +reset index,
		  +update entirely_blank flag,
		  +and print the character*/
		else if (c != '\n')
		{
			if(index != RESET_INDEX)	
			{
				for(i=0; i<=index; i++)	
					putchar(whiteSpace[i]);
				index = RESET_INDEX;
			}
			entirely_blank = FALSE;
			putchar(c);
		}
		/*Dont print the preceeding white space before new-line*/
		/*Only print the newline, and reset index*/
		/*If an entirely_blank line then 
		  +DO NOT print the new-line('\n'),
		  +thus deleting the entirely blank line*/
		else if (c == '\n')
		{
			index = RESET_INDEX;
			if(entirely_blank == FALSE)
				putchar(c);
			entirely_blank = TRUE;
		}
	}
	return;
}

/*___*/
/*EOF*/
