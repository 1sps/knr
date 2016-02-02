/*3-6 k&r 2*/
/*___: 2016-01-24 Sun 03:05 PM*/

/*Header files*/
#include<stdio.h>
#include<string.h>

/*Constants*/
#define MAXLINE 20

/*Function prototype*/
void iota1(int n, char s[], int min);
int atoi1(const char st[]);
int getline1(char s[], int lim);
void reverse1(char s[]);

/*Program starts*/
int main(int argc, char *argv[])
{
	/*Variables*/
	int n, min;
	char st[MAXLINE];

	/*Get the minimum width and
	  +original number */
	printf("Minimum width: ");
	getline1(st, MAXLINE/5);
	if(st[strlen(st)-1]=='\n')
		st[strlen(st)-1]=='\0';
	min = atoi1(st);
	printf("Numer: ");
	getline1(st, MAXLINE);
	if(st[strlen(st)-1]=='\n')
		st[strlen(st)-1]=='\0';
	n = atoi1(st);

	/*Convert number to string 
	  +with minimum width*/ 
	iota1(n, st, min); 

	/*Print results*/
	printf("Result: %s\n", st);

	/*Program ends*/
	return 0;
}

/*iota() definition*/
void iota1(int n, char s[], int min)
{
	/*Variables*/
	int i, j, sign, temp;

	/*Convert number to string*/
	if((sign = n) < 0)
		n = -n;
	i=0;
	do
		s[i++] = n % 10 + '0';
	while((n/=10) > 0);
	if(sign<0)
		s[i++] = '-';
	s[i] = '\0';
	reverse1(s);

	/*If less than minimum width*/
	if((temp = strlen(s)) < min)
	{
		for(i=temp-1, j=1; i>=0; --i, ++j)
			s[min-j] = s[i];
		s[min] = '\0';
		for(i=0; i < min - temp; ++i)
			s[i] = ' ';
	}
}

/*getline() function definition*/
int getline1(char s[], int lim)
{
	int c, i;
	for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if(i != lim-1)
	{
		s[i]='\n';
		++i;
	}
	s[i]='\0';
	return i;
}

/*atoi1() function definition*/
int atoi1(const char st[])
{
	int n;
	int i;

	n=0;
	for(i=0; st[i] >= '0' && st[i] <= '9'; ++i)
		n = 10*n + (st[i] - '0');
	/*If string doesnt start with a digit*/
	if (i==0)
		return -1;
	return n;
}
/*reverse1() definition*/
void reverse1(char s[])
{
	int i, n, temp;
	n=strlen(s)-1;
	for(i=0; i<=n/2; ++i)
	{
		temp = s[i];
		s[i] = s[n-i];
		s[n-i]=temp;
	}
}

/*___*/
/*EOF*/
