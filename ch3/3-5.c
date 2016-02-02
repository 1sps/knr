/*3-5 k&r 2*/
/*___: 2016-01-24 Sun 03:05 PM*/

/*Header files*/
#include<stdio.h>
#include<string.h>

/*Constants*/
#define MAXLEN 20
#define MAXLINE 20

/*Function prototype*/
void iotb(int n, char s[], int b);
int atoi1(const char st[]);
int getline1(char s[], int lim);
void reverse1(char s[]);


/*Program starts*/
int main(int argc, char *argv[])
{
	/*Variables*/
	int n, b;
	char st[MAXLINE];

	/*Get the target base and
	  +original number
	*/
	printf("Convert to Base: ");
	getline1(st, MAXLINE/5);
	if(st[strlen(st)-1]=='\n')
		st[strlen(st)-1]=='\0';
	b = atoi1(st);
	printf("Decimal: ");
	getline1(st, MAXLINE);
	if(st[strlen(st)-1]=='\n')
		st[strlen(st)-1]=='\0';
	n = atoi1(st);

	/*Convert to base b*/ iotb(n, st, b);

	/*Print results*/
	printf("Result: %s\n", st);

	/*Program ends*/
	return 0;
}

/*iotb() definition*/
void iotb(int n, char s[], int b)
{
	int i, temp;
	i=0;
	do
		if(n % b > 9)
			s[i++] = n % b - 10 + 'A';
		else
			s[i++] = n % b + '0';
	while((n=n/b) != 0);
	s[i]='\0';
	reverse1(s);
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
