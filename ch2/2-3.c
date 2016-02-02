/*K&R 2nd, Ex 2-3*/
/*C program to convert hexadecimal to decimal*/
/*___: 2016-01-23 Sat 12:45 AM*/

/*Header files*/
#include<stdio.h>
#include<ctype.h>

/*Constants*/
#define MAXLINE 30

/*Function prototypes*/
int getline1(char s[], int lim);
signed long htoi(char line[]);

/*Program starts*/
int main(int argc, char *argv[])
{
	/*Variables*/
	char line[MAXLINE];
	signed long num_dec;
	printf("Hex number: ");

	/*Get hex number and convert it*/
	getline1(line, MAXLINE);
	num_dec = htoi(line);

	/*Print answer*/
	printf("Decimal: %ld\n", num_dec);

	/*Program ends*/
	return 0;
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

/*htoi() function definition*/
signed long htoi(char line[])
{
	signed long num = 0;
	unsigned int i = 0;
	/*If an empty string*/
	if(line[i] == '\n')
		return -1;
	/*Ignore leading 0x or 0X*/
	if(line[i] == '0' && (line[i+1] == 'x' || line[i+1] == 'X'))
		i=i+2;
	/*Convert hex to decimal*/
	while((line[i] >= '0' && line[i] <= '9') || 
	      (line[i] >= 'a' && line[i] <='f') || 
		  (line[i] >= 'A' && line[i] <= 'F'))
	{
		if(line[i] >= 'a' && line[i] <='f')
			num = 16 * num + (line[i] - 'a' + 10);
		else if(line[i] >= 'A' && line[i] <='F')
			num = 16 * num + (line[i] - 'A' + 10);
		else
			num = 16 * num + (line[i] - '0');
		++i;
	}
	/*If not a valid hex*/
	if(line[i] != '\n' && line[i] != '\0')
		return -1;

	/*Return answer*/
	return num;
}
/*___*/
/*EOF*/
