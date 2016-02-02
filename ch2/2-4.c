/*k&r 2nd Ex 2-4*/
/*Delete each character in string s1 that 
  +matches any character in string s2
*/
/*___: 2016-01-23 Sat 05:02 AM*/

/*Constants*/
#define TRUE 1
#define FALSE 0
#define MAXLINE 100

/*Header files*/
#include<stdio.h>

/*Function prototype*/
void squeeze(char s1[], const char s2[]);
int ins2(char c, const char st[]);
int getline1(char s[], int lim);

/*Program starts*/
int main(int argc, char *argv[])
{
	/*Variables*/
	char s1[MAXLINE];
	char s2[MAXLINE];

	/*Get the strings from user*/
	printf("String1: ");
	getline1(s1, MAXLINE);
	printf("String2: ");
	getline1(s2, MAXLINE);

	/*Call squeeze()*/
	squeeze(s1, s2);

	/*Print string1 after squeezing*/
	printf("String1: %s\n", s1);

	/*Program ends*/
	return 0;
}
/*squeeze() function definition*/
void squeeze(char s1[], const char s2[])
{
	int i, j;
	for(i=j=0; s1[i] != '\0'; ++i)
		if(!ins2(s1[i], s2))
			s1[j++] = s1[i];
	s1[j]='\0';
}
/*ins2() function definition*/
int ins2(char c, const char st[])
{
	int i = 0;
	while(st[i] != '\0')
		if(st[i++] == c)
			return TRUE;
	return FALSE;
}
/*getline1() function definition*/
int getline1(char s[], int lim)
{
	int c, i;
	for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if(i != lim-1)
		s[i++]='\n';
	s[i]='\0';
	return i;
}
/*___*/
/*EOF*/
