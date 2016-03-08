/* Ex 7-5 K&R2 */

/* C program to implement a reverse polish calculator */
/* using getline and sscanf */

/* 2016-02-27 Sat 06:06 PM */

/*Header files*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Constants*/
/*Max size of operand or operator*/
#define MAXOP 100
/*Signal that number was found*/
#define NUMBER '\0'
#define MAXLINE 100
#define MAXWORD 50

/*Function protoypes*/
int getop(char[]);
int getop1(char[]);
void push(double);
double pop(void);

/*Reverse polish calculator*/
int main(void)
{
	/*Variables*/
	int type;
	double op2;
	char s[MAXOP], word[MAXWORD], line[MAXLINE];

	/*Get input untill user quits*/
	while (scanf("%s", word) == 1) 
	{
		type = getop1(word);
		switch(type)
		{
			case NUMBER: /*Operand*/
				push(atof(word));
				break;
			case '+': /*Addition*/
				push(pop() + pop());
				break;
			case '*': /*Multiplication*/
				push(pop() * pop());
				break;
			case '-': /*Subtraction*/
				op2 = pop();
				push(pop() - op2);
				break;
			case '/': /*Division*/
				op2 = pop();
				if(op2!=0)
					push(pop() / op2);
				else
					printf("error: division by zero\n");
				break;
			case '\n': /*Print result*/
				printf("\t%.8g\n", pop());
				break;
			case 'P': /*Print result*/
				printf("\t%.8g\n", pop());
				break;
			default: /*Unknown operator*/
				printf("error: unknown command: %s\n", word);
				break;
		}
	}
	return 0;
}

int getop1(char word[])
{
	double num;
	char s[MAXWORD];

	if ((sscanf(word, "%lf", &num)) == 1)
		return NUMBER;
	switch (word[0])
	{
	case '+': case '-':
	case '*': case '/':
	case 'p':
		 if (strlen(word) == 1) 
			return word[0];
		 else 
			 return 'E'; 
	default:
		return word[0];
	}
}

/*Constants*/
/*Max num of operands in stack*/
#define MAXVAL 100

/*External variables*/
/*Stack to store operands*/
double val[MAXVAL];
/*Stack pointer*/
int sp=0;

/*push() function definition*/
void push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/*pop() function definition*/
double pop(void)
{
	if(sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

/*Header files*/
#include<ctype.h>

/*Function prototypes*/
int getch(void);
void ungetch(int);

/*getop() function definition*/
int getop(char s[])
{
	/*Variables*/
	int i, c;
	while((s[0]=c=getch()) == ' ' || c == '\t')
		;
	s[1]='\0';
	/*Return the char if not a number*/
	/*This maybe an operator (+,-,*,/)*/
	if(!isdigit(c) && c!='.')
		return c;

	/*Else if a number starts,*/
	/*+store the number*/
	i=0;
	/*Collect the number*/
	if(isdigit(c))
		/*Collect the integer part*/
		while(isdigit(s[++i] = c = getch()))
			;
	if(c=='.')
	/*Collect the fraction part*/
	while(isdigit(s[++i] = c = getch()))
		;
	s[i]='\0';
	if(c != EOF)
		ungetch(c);
	/*Indicate a number in return*/
	return NUMBER;
}

/*Constants*/
#define BUFSIZE 100

/*External variables*/
/*Buffer fot getch() and ungetch()*/
char buf[BUFSIZE];
/*Next free position in buffer*/
int bufp=0;

/*getch() function definition*/
/*Get a (possibly pushed back) character*/
int getch(void)
{
	return (bufp>0) ? buf[--bufp] : getchar();
}

/*ungetch() function definition*/
/*Push character back on input*/
void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/*___*/
/*EOF*/
