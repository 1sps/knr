/*K&R Ex 2-1*/
/*C program to calculate the ranges of 
  +char, short, int and long*/
/*___: 2016-01-21 Thu 06:01 AM*/

/*Header files*/
#include<stdio.h>

/*Function prototype*/

/*Program starts*/
int main(void)
{
	/*Variables*/
	
	signed char c;
	signed short s;
	signed int i;
	signed long l;
	unsigned char uc = 0;;
	unsigned short us = 0;
	unsigned int ui = 0;
	unsigned long ul = 0;

	unsigned long u_temp;
	signed long s_temp;

	printf("Data type      Range\n");
	/*________*/
	/*UNSIGNED*/

	/*Calculate the range of unsigned char*/
	--uc;
	printf("Unsigned char  0 - %u\n", uc);

	/*Calculate the range of unsigned short*/
	--us;
	printf("Unsigned short 0 - %u\n", us);

	/*Calculate the range of unsigned int*/
	--ui;
	printf("Unsigned int   0 - %u\n", ui);

	/*Calculate the range of unsigned long*/
	--ul;
	printf("Unsigned long  0 - %lu\n", ul);

	/*________*/
	/*SIGNED*/

	/*Calculate the range of signed char*/
	for(c = 1; c > 0; c = c *2 )
		;
	printf("Signed char    %d - ", c); 
	--c;
	printf("%d\n", c); 
	/*Calculate the range of signed short*/
	for(s = 1; s > 0; s = s *2 )
		;
	printf("Signed short   %d - ", s); 
	--s;
	printf("%d\n", s); 
	/*Calculate the range of signed int*/
	for(i = 1; i > 0; i = i *2 )
		;
	printf("Signed int     %d - ", i); 
	--i;
	printf("%d\n", i); 
	/*Calculate the range of signed long*/
	for(l = 1; l > 0; l = l *2 )
		;
	printf("Signed long    %ld - ", l); 
	--l;
	printf("%ld\n", l); 

	/*Program ends*/
	return 0;
}

/*___*/
/*EOF*/

