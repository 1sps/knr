/*K&R C 2nd edition, Excercise: 1-23*/
/*C program to remove all comments from a C program*/
/*___: 2016-01-21 Thu 03:39 AM*/

/*Header files*/
#include<stdio.h>

/*Constants*/
#define TRUE  1
#define FALSE 0

/*Program starts*/
int main(void)
{
	/*Variables*/
	int c, prev_slash, prev_star, comment, quotes;

	/*Initialize all atributes as FALSE*/
	comment = prev_slash = prev_star = quotes = FALSE;

	/*Read each character*/
	while((c=getchar()) != EOF)
	{
		/*If outside comment section*/
		if (comment == FALSE)
		{
			/*Check if slash recorded in past*/
			if(prev_slash == TRUE)
			{
				prev_slash = FALSE;
				if(c == '*')	
					comment = TRUE;		
				else
					putchar('/');
			}
			/*Print any character other than / 
			*/
			if(comment == FALSE)
				if(c != '/')
					putchar(c);
			/*Rcord slash for future*/
			if(c == '/')
				/*Dont bother if inside quotes*/
				if(quotes == TRUE)
					putchar(c);	
				else if(quotes == FALSE)
					prev_slash = TRUE;	
			/*Record quote start and end*/
			if(quotes == FALSE)
			{
				if(c == '"')
					quotes = TRUE;
			}
			else if(quotes == TRUE)
				if(c == '"')
					quotes = FALSE;
		}
		/*If inside comment section*/
		else if(comment == TRUE)
		{
			/*If previous char was start*/
			if(prev_star == TRUE)
			{
				prev_star = FALSE;	
				/*If actually a comment stop*/
				if(c == '/')
					comment = FALSE;
			}
			/*Record if any star*/
			if(c == '*')
				prev_star = TRUE;
		}
	}
	/*Program ends*/
	return 0;
}

/*___*/
/*EOF*/
