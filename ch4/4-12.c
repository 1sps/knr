/*Ex 4-12 K&R 2nd*/
/*___: 2016-02-01 Mon 12:31 PM*/

/*Header files*/
#include<stdio.h>
/*Constants*/
#define MAXVAL 100
/*Function protoypes*/
int itoa1(int d, char s[]);
/*Program starts*/
/*Test itoa()*/
int main(void)
{
	char s[MAXVAL];    /*Result string*/
	itoa1(-2334, s);    /*Convert int to string*/
	printf("%s\n", s); /*Print result*/
	return 0;          /*terminate program*/
}
/*Convert int to string*/
int itoa1(int d, char s[])
{
	int i;             /*position in string*/
	i = 0;             /*for first character*/
	/*Base case*/
	if(d/10==0)
	{
		s[i] = d%10;
		if(s[i] < 0)
		{
			s[i+1] = s[i++];
			s[i-1] = '-';
			s[i] *= -1;
		}
		s[i] = s[i] + '0';  /*store the character*/
		s[i+1] = '\0';
		return ++i;
	}
	/*Base case ends*/
	i = itoa1(d/10, s);     /*get the position*/
	s[i] = d%10;
	if(s[i] < 0)
		s[i] *= -1;
	s[i] = s[i] + '0';      /*store the character*/
	s[i+1] = '\0';
	return ++i;
}
/*___*/
/*EOF*/
