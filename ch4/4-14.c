/*K&R 2nd, Ex 4-14*/
/*Define a macro swap(t,x,y) that interchanges two arguments
  of type t
*/
/*___: 2016-02-02 Tue 01:01 PM*/

/*Header files*/
#include<stdio.h>
/*Constants*/
/*Macros*/
#define swap(t, x, y) {t temp; temp = x; x = y; y = temp;}
/*Function protoypes*/
/*Program starts*/
int main(void)
{
	int a = 10;
	int b = -20;
	printf("a = %d b = %d\n", a, b);
	swap(int, a, b);  /*Test swap() with int type*/
	printf("a = %d b = %d\n", a, b);
	double c = 100.5;       
	double d = -200.5;
	printf("c = %g d = %g\n", c, d);
	swap(int, c, d);  /*Test swap() with int type*/
	printf("c = %g d = %g\n", c, d);
	return 0;         /*Program ends*/
}
/*___*/
/*EOF*/
