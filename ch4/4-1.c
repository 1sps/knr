/*K&R 2, Ex 4-2*/
/*C program with function strrindex()*/
/*___: 2016-01-25 Mon 12:23 PM*/

/*Header files*/
#include<stdio.h>
#include<string.h>

/*Constants*/
#define MAXLINE 100

/*For conditional compilation*/
#define SKIP

/*Function protoypes*/
int strrindex(const char s[], const char t[]);
int getline1(char s[], int lim);
void rmnl(char s[]);

/*Program starts*/
int main(void)
{
	/*Variables*/
	int rpos;
	char st[MAXLINE];
	char pattern[] = "peace";

	/*Search for the pattern in each
	  +line, and print the line
	  +if match found
	*/
	while(getline1(st, MAXLINE)>0)
		if((rpos=strrindex(st, pattern))>=0)
			printf("Index: %d -> %s", rpos, st);

	/*Program ends*/
	return 0;
}

/*strindex() function definition*/
int strrindex(const char s[], const char t[])
{
	/*Variables*/
	int i, j, k, rpos = -1;

	/*Search for the pattern in string*/
	for(i=0; s[i]!='\0'; ++i)
	{
		/*Return the index at which pattern found*/
		/*This is the version from K&R 2nd*/
		for(j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if(k>0 && t[k] == '\0')
			rpos = i;
	}
	/*If no match found*/
	return rpos;
}

/*getline1() function definition*/
int getline1(char s[], int lim)
{
	/*Get a line from stdin and
	  +return its length
	*/
	int c, i;
	for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if(c == '\n')
	{
		s[i]='\n';
		++i;
	}
	s[i]='\0';
	return i;
}

/*rmnl() function definition*/
void rmnl(char s[])
{
	/*If last character is
	  +a \n then delete it
	*/
	if(s[strlen(s)-1]=='\n')
		s[strlen(s)-1]='\0';
}

/*___*/
/*EOF*/
