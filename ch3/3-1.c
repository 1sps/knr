/*Ex3-1 K&R 2nd*/
/*C program to Binary search
  +for an integer in an array
*/
/*___: 2016-01-24 Sun 03:17 AM*/

/*Header files*/
#include<stdio.h>
#include<stdlib.h>

/*Constatnts*/
#define MAXLEN 5

/*Function prototypes*/
int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

/*Program starts*/
int main(void)
{
	/*Variables*/
	int arr[]={5,4,3,8,9,23,-23,43};
	char st[MAXLEN];
	int num, index;

	/*Get the number from user*/
	printf("Number to search: ");
	scanf("%s", st);
	num = atoi(st);
	/*Do the binary search*/
	index = binsearch2(num, arr, 8);
	printf("Index: %d\n", index);

	/*Program ends*/
	return 0;
}

/*binsearch() function definition*/
/*Given in K&R 2nd, Ch3*/
int binsearch(int x, int v[], int n)
{
	int mid;
	int low = 0;
	int high = n-1;
	while(low <= high)
	{
		mid = (low+high)/2;
		/*If match not found, look in the other half*/
		if(x<v[mid])
			high = mid-1;
		else if(x>v[mid])
			low = mid +1;
		else
			/*Return match*/
			return mid;
	}
	/*No match*/
	return -1;
}
/*binsearch2() function definition*/
/*Ex3-1 K&R 2nd*/
int binsearch2(int x, int v[], int n)
{
	int low = 0;
	int high = n-1;
	int mid = (low+high)/2;
	while(low < high-1)
	{
		if(x<v[mid])
			high = mid;
		else
			low = mid;
		mid = (low+high)/2;
	}
	if(x==v[low])
		return low;
	else if(x==v[high])
		return high;
	else
		return -1;
}

/*___*/
/*EOF*/

