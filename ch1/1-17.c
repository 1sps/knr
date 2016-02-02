/*___: 2016-01-20 Wed 02:00 AM*/

/*C program to print the length of longest line*/

/*Header files*/
#include<stdio.h>

/*Constants*/
#define MAXLINE 20

/*Function prototype declaration*/
int getline1(char line[], int maxline);
void copy(char to[], char from[]);

/*Program starts*/
int main(int argc, char *argv[])
{
	int len;
	int max;
	char line[MAXLINE];
	/*char longest_st[MAXLINE];*/
	char longest[MAXLINE];

	max = 0;
	while ((len = getline1(line, MAXLINE)) > 0)
	{
		if(len == MAXLINE - 1 && line[MAXLINE-2] != '\n')
		{
			while(getchar() != '\n')
				++len;
			++len;
		}
		if(len > max)	
		{
			max = len;		
			copy(longest, line);
		}
	}
	if(max > 0)
		printf("%s", longest);
		printf("\nLength: %d\n", max);
	/*Program ends*/
	return 0;
}

int getline1(char s[], int lim)
{
	int c, i;
	for(i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n';++i)
		s[i] = c;
	if(c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void  copy(char to[], char from[])
{
	int i;
	i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
}
/*___*/
/*EOF*/

