/*Ex 4-13 K&R 2nd*/
/*___: 2016-02-01 Mon 09:24 PM*/

/*Header files*/
#include<stdio.h>
#include<string.h>
/*Constants*/
#define MAXLINE 100
/*Function protoypes*/
void reverse(char s[]);
void swap(char s[], int i, int j);
int getline1(char line[], int maxline);
/*Program starts - Test reverse()*/
int main(void)
{
	char s[MAXLINE];
	while(getline1(s, MAXLINE)>0)
	{
		s[strlen(s)-1] = '\0';
		reverse(s);
		printf("%s\n", s);
	}
	return 0;
}
/*Recursively Reverse a string*/
void reverse(char s[])
{
	int len = strlen(s);    /*Length of the string*/
	static int pos=0;       /*Indicates current position in string*/
	/*If one length string*/
	if(len == 1)
		return;
	/*Base case*/
	if(pos == ((len/2) - 1))
	{
		swap(s, pos, len-1-pos);
		return;
	}
	++pos;					 /*For next level of recursion*/
	reverse(s);				 /*Call next level of recursion*/
	--pos;					 /*Bring back pos to current level of recursion*/
	swap(s, pos, len-1-pos); /*swap appropriate elements*/
}
/*interchange s[i] & s[j]*/
void swap(char s[], int i, int j)
{
	char temp;
	temp = s[i];
	s[i] = s[j];
	s[j] = temp;
}
/*Get a line from stdin*/
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
/*___*/
/*EOF*/
