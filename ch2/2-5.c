/*k&r 2nd Ex 2-5*/
/*C program to return the first location in
  +the string s1 where any character from s2 occur
*/
/*___: 2016-01-23 Sat 05:43 AM*/

/*Header files*/
#include<stdio.h>

/*Constants*/
#define TRUE 1
#define FALSE 0
#define MAXLINE 100

/*Function prototype*/
int getline1(char s[], int lim);
int any(const char s1[], const char s2[]);

/*Program starts*/
int main(int argc, char *argv[])
{
	/*Variables*/
	char s1[MAXLINE];
	char s2[MAXLINE];
	int pos, i;

	/*Get the strings from user*/
	printf("String1: ");
	getline1(s1, MAXLINE);
	printf("String2: ");
	getline1(s2, MAXLINE);

	/*Remove the '\n' at the end put by getline1()*/
	i=0;
	while(s1[i++] != '\0')
		if(s1[i-1] == '\n')
			s1[i-1] = '\0';
	i=0;
	while(s2[i++] != '\0')
		if(s2[i-1] == '\n')
			s2[i-1] = '\0';
	
	/*Get the position*/
	pos = any(s1, s2);

	/*Print the result*/
	printf("Position of first occurence: %d\n", pos);

	/*Program ends*/
	return 0;
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
/*any() funciton definition*/
/*ISSUE HERE, NEED TO BE FIXED*/
int any(const char s1[], const char s2[])
{
	/*Variables*/
	int i, j;
	/*Use this temparary array to make 
	  +search linear in worst case*/
	int temp[256];

	/*Fill the temp array*/
	for(i=0; i<256; ++i)
		temp[i]=0;
	i=0;
	while(s2[i++] != '\0')
		++temp[s2[i-1]];

	/*Check for the first occurence, and 
	  +return the position*/
	for(i=0; s1[i] != '\0'; ++i)
			if(temp[s1[i]])
				return i;
	/*Return -1 if no occurences found*/
	return -1;
}
/*___*/
/*EOF*/
