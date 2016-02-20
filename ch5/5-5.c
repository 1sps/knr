/* Ex 5-5 K&R2 */
/* Write versions of strncpy, strncat and strncmp functions */

/*Header files*/
#include<stdio.h>

/*Constants*/
#define MAXLEN 10

/*Function protoypes*/
char* strncpy1(char *dest, const char *src, size_t n);
char* strncat1(char *dest, const char *src, size_t n);
int strncmp1(const char *s1, const char *s2, size_t n);

/*Test str functions*/
int main(void)
{
	/* Test strncpy1 */
	char src1[MAXLEN] = "Munich";
	char src12[] = "Munich1234";
	char dest1[MAXLEN] = "Bayern";
	strncpy1(dest1, src1, 10);
	printf("%s\n", dest1);
	strncpy1(dest1, src12, 10);
	printf("%s\n", dest1);
	printf("\n");

	/* Test strncat1 */
	char src2[MAXLEN] = "Mun";
	char src22[] = "Munich123456";
	char dest2[MAXLEN] = "Bayern";
	strncat1(dest2, src2, 2);
	printf("%s\n", dest2);
	strncat1(dest2, src22, 10);
	printf("%s\n", dest2);
	printf("\n");

	/* Test strncmp1 */
	char st3[] = "Bayern1234";
	char st4[] = "Bayern125";
	char st5[] = "Bayern";
	char st6[] = "Bayern";

	printf("Below should be 0, -1, 1, 0\n");
	printf("%d\n", strncmp1(st3, st4, 8));
	printf("%d\n", strncmp1(st3, st4, 9));
	printf("%d\n", strncmp1(st4, st3, 10));
	printf("%d\n", strncmp1(st5, st6, 10));

	/*Program ends*/
	return 0;
}

/* Copy string soure to dest */
char *strncpy1(char *dest, const char *src, size_t n)
{
	/* Copy the original dest pointer */
	char *dest_original;
	dest_original = dest;

	/* Copy the characters */
	while (*src != '\0' && n > 0)
	{
		*dest++ = *src++;
		--n;
	}
	/* If src was smaller than n bytes */
	if (n>0)
		while (n-- > 0)
			*dest++ = '\0';
	
	return dest_original;
}

/* Concatenate src to dest - at most n characters */
char *strncat1(char *dest, const char *src, size_t n)
{
	size_t i;

	/* Copy the original dest pointer */
	char *dest_original;
	dest_original = dest;

	/* Skip the initial characters of dest */
	while (*dest != '\0')
		dest++;

	/* Copy the characters */
	for (i=0; *src != '\0' && i < n; ++i)
		*dest++ = *src++;
	*dest = '\0';

	return dest_original;
}

/* Compare two strings */
int strncmp1(const char *s1, const char *s2, size_t n)
{
	size_t i;

	/* Compare char by char, return if mismatch */
	for(i=0; *s1 != '\0' && *s2 != '\0' && i<n; ++i)
	{
		if (*s1 < *s2)
			return -1;
		else if (*s1 > *s2)
			return 1;
		++s1;
		++s2;
	}

	/* If either one (or both) string has/have less than n chars */
	if (i < n)
		if (*s1 < *s2)
			return -1;
		else if (*s1 > *s2)
			return 1;

	/* If program continues to this point, */
	/* +then the two strings are equal */
	return 0;
}
/*___*/
/*EOF*/
