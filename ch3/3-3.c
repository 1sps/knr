/*K&R 2nd Ex 3-3*/
/*Expand shorthand notation like a-z to abc...xyz*/

/*Header files*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>

/*Constants*/
#define MAXLINE 100
#define TRUE 1
#define FALSE 0
#define DIGIT 10
#define LOWER 11
#define UPPER 12
#define EXITLOOP -1
#define UNDEF 0

/*Function prototypes*/
void expand(const char s1[], char s2[]);
int getline1(char line[], int maxline);

/*Program starts*/
int main(void)
{
	/*Automatic Variables*/
	char st1[MAXLINE];
	char st2[MAXLINE*10];

	while(TRUE)
	{
		/*Get string*/
		getline1(st1, MAXLINE);
		if( st1[strlen(st1)-1] == '\n')
			st1[strlen(st1)-1] = '\0';

		/*Expand st1[] to st2[]*/
		expand(st1, st2); 
		/*Print results*/
		printf("%s\n", st2); }
	/*Program ends*/
	return 0;
}

/*expand() function definition*/
void expand(const char s1[], char s2[])
{
	/*Automatic Variables*/
	int c, d, e, n;
	int i, j, k, l, flag=FALSE;
	int type1=UNDEF, type2=UNDEF;

	/*Get st1[] length*/
	n = strlen(s1);

	/*Go through each character in s1[]*/
	for(i=0,j=0; i<n; ++i, ++j)
	{
		/*If '-' is found within the string*/
		if(s1[i]=='-' && i!=0 && i!=n-1)
		{
			d=s1[i-1];
			e=s1[i+1];
			/*If both sides of '-' are of same type
			  +then only perform expansion*/
			if(
			   (isdigit(d) && isdigit(e)) ||
			   (islower(d) && islower(e)) ||
			   (isupper(d) && isupper(e))
			  )
			{
				/*Handle the case like a-b-c*/
				if(isdigit(d))
					type1=DIGIT;
				else if(islower(d))
					type1=LOWER;
				else if(isupper(d))
					type1=UPPER;

				for(k=i, l=0; k < n; ++k, ++l)
				{
					/*Look for contiguous '-'*/
					if(l%2==0)
					{
						if(s1[k] != '-')
							k=n;
					}
					/*Look if same character type 
					  +on the other side of '-'
					*/
					else
					{
						if(isdigit(s1[k]))
							type2=DIGIT;
						else if(islower(s1[k]))
							type2=LOWER;
						else if(isupper(s1[k]))
							type2=UPPER;
						else
							type2=UNDEF;

						if(type1 == type2)
						{
							e=s1[k];
							i=k;
						}
						else
							k=n;
					}
				}
				/*Expansion*/
				--j;
				for(k=0; k<=e-d; ++k)
				{
					flag=TRUE;
					s2[j++]=d+k;
				}
				if(flag==TRUE)
				{
					flag=FALSE;
					--j;
				}
			}
			/*If not same types around '-' 
			  +then just copy as usual*/
			else
				s2[j]=s1[i];
		}
		/*Just copy as usual*/
		else
			s2[j]=s1[i];
	}
	/*Make s2[] a string*/
	s2[j]='\0';
}

/*getline1() function definition*/
int getline1(char s[], int lim)
{
	/*Automatic Variables*/
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
