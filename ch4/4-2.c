/*K&R Ch5 4, Example 2*/
/*C function atof1() to convert string to double */
/*This atof1() is an extended version of +atof1() given
  +in the first example of Ch4 K&R 2nd*/
/*___: 2016-01-27 Wed 5:02 PM*/

/*_______________________________________________*/

/*Header files*/
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

/*Constants*/
#define MAXLINE 100
#define PLUS 1
#define MINUS -1

/*Function protoypes*/
double atof1(const char s[]);
int getline1(char s[], int lim);

/*Program starts*/
int main(void)
{
	/*Variables*/
	char st[MAXLINE];
	double num;

	while(1)
	{
		/*Get a string*/
		printf("String: ");
		getline1(st, MAXLINE);
		num = atof1(st);

		/*Print results*/
		printf("Double: %f\n", num);
	}

	/*Program ends*/
	return 0;
}

/*atof1() function definiton*/
double atof1(const char s[])
{
	/*Variables*/
	int i, j;
	int sign, exp_sign;
	double val, power;
	int exp;
	char exp_str[MAXLINE];

	/*Skip white space*/
	for(i=0; isspace(s[i]); ++i)
		;

	/*Record the sign*/
	sign = s[i] == '-' ? MINUS : PLUS;
	if(s[i]=='-' || s[i]=='+')
		++i;

	/*Convert before decimal point*/
	val=0;
	for(; isdigit(s[i]); ++i)
		val = 10 * val + s[i] - '0';
	/*See if decimal point present*/
	if(s[i]=='.')
		++i;
	/*Convert after decimal point*/
	power=1;
	for(; isdigit(s[i]); ++i)
	{
		val = 10 * val + s[i] - '0';
		power *= 10;
	}
	
	/*Extension here, 
	  +upto END_OF_EXTENSION*/
	val /= power;

	/*See if exponent part is there*/
	if(s[i]=='e' || s[i]=='E')
		++i;

	/*Get the sign of exponent*/
	exp_sign = s[i] == '-' ? MINUS : PLUS;
	if(s[i]=='-' || s[i]=='+')
		++i;

	/*Get the exponent in a string*/
	j=0;
	for(; isdigit(s[i]); ++i)
		exp_str[j++] = s[i];
	exp_str[j] = '\0';

	/*Convert exponent to integer*/
	exp = atoi(exp_str);

	/*Apply the exponent effect*/
	if(exp_sign == PLUS)
		for(j=0; j<exp; ++j)
			val *= 10;
	else if(exp_sign == MINUS)
		for(j=0; j<exp; ++j)
			val /= 10;
	else
		printf("Error occured, answer is garbage.\n");

	/*Return the double*/
	return sign * val;

	/*END_OF_EXTENSION*/
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

/*___*/
/*EOF*/
