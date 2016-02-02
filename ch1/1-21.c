/*___: 2016-01-21 Thu 01:15 AM*/

/*C program to replace blanks with proper tabs*/

/*Header files*/
#include<stdio.h>

/*Constants*/
#define LINE_START 0
#define TRUE       1
#define FALSE      0
#define NO_BLANKS  0
#define TABSTOP    4
#define ONE_TAB    1
#define ONE_BLANK  1

/*Program starts*/
int main(void)
{

	/*Variables*/
	int c, i, pos_count, pos_blanks_start, prev_blank, num_of_blanks;
	int virtual_tot_blanks, num_of_tabs_needed, num_of_blanks_needed;

	/*Start at the first character*/
	prev_blank = FALSE;
	pos_count = LINE_START;
	/*Read each character*/
	while((c = getchar()) != EOF)
	{
		/*For blank characters*/
		if(c == ' ')
		{
			/*If this is the starting of blanks*/
			if(prev_blank == FALSE)
				pos_blanks_start = pos_count;
			num_of_blanks = num_of_blanks + 1;
			prev_blank = TRUE;
			++pos_count;
		}
		/*For non-blank characters*/
		else
		{
			/*If previous blank character(s) is/are blank*/
			/*Replace previous blanks with proper tabs*/
			if(prev_blank == TRUE)
			{
				/*Treat all characters in this tabspace as blank
				  +then calculate number of tabs and blanks needed*/
				virtual_tot_blanks = num_of_blanks + (pos_blanks_start % TABSTOP);
				num_of_tabs_needed = virtual_tot_blanks / TABSTOP;
				num_of_blanks_needed = virtual_tot_blanks % TABSTOP;
				/*If at least one tab needed*/
				if(num_of_tabs_needed >= 1)
				{
					/*Chose a blank between a single tab and single blank*/
					if(num_of_tabs_needed == ONE_TAB && num_of_blanks == ONE_BLANK)
							putchar(' ');
					else
					{
						for(i = 0; i < num_of_tabs_needed; ++i)
							putchar('\t');
						for(i = 0; i < num_of_blanks_needed; ++i)
							putchar(' ');
					}
				}
				/*If no tabs needed, the print all the blanks*/
				else
					for(i = 0; i < num_of_blanks; ++i)
						putchar(' ');
			}
			putchar(c);
			prev_blank = FALSE;
			num_of_blanks = NO_BLANKS;
			/*Start again for the new line*/
			if(c == '\n')
				pos_count = LINE_START;
			/*Increment porper count for tab*/
			else if(c == '\t')
				pos_count = pos_count + TABSTOP - (pos_count % TABSTOP);
			/*Else increment as usual*/
			else
				++pos_count;
		}
	}
	/*Program ends*/
	return 0;
}

/*___*/
/*EOF*/
