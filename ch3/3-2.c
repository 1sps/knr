/*K&R 2nd, Ex 3-2*/
/*C program to convert tabs and newlines to \t and \n*/
/*___: 2016-01-24 Sun 06:20 AM*/

/*Header files*/
#include<stdio.h>

/*Constants*/
#define MAXLINE 100

/*Function prototypes*/
void escape(char s[], const char t[]);
int getline1(char line[], int maxline);

/*Program starts*/
int main(int argc, char *argv[])
{
	/*Variables*/
	char st1[MAXLINE];
	char st2[MAXLINE];

	/*Get string*/
	printf("Enter a string: ");
	getline1(st1, MAXLINE);

	/*Escape tabs and newlines*/
	escape(st2, st1);

	/*Print both strings*/
	printf("%s\n", st1);
	printf("%s\n", st2);

	/*Program ends*/
	return 0;
}

/*escape() function definition*/
void escape(char s[], const char t[])
{
	int i=0;
	int j=0;
	char c;
	while((c=t[i]) != '\0')
	{
		switch(c)
		{
			case '\t':
				s[j++]='\\';
				s[j]='t';
				break;
			case '\n':
				s[j++]='\\';
				s[j]='n';
				break;
			default:
				s[j]=t[i];
				break;
		}
		++i;
		++j;
	}
	s[j]='\0';
}
/*getline1() function definition*/
int getline1(char s[], int lim)
{
	int c, i;
	for(i=0; (i<lim-1) * ((c=getchar()) != EOF) * (c != '\n');++i)
		s[i] = c;
	if(c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
/*___*/
/*EOF*/

