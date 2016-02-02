/*Ex 4-3, K&R 2nd*/
/*C program to implement a reverse polish calculator*/
/*Calculator is extended to support mudulus division*/
/*+and negative numbers*/
/*___: 2016-01-27 Wed 08:27 PM*/
/*__________________________________________________*/

/*Header files*/
#include<stdio.h>
#include<stdlib.h>

/*Constants*/
/*Max size of operand or operator*/
#define MAXOP 100
/*Signal that number was found*/
#define NUMBER '\0'

/*Function protoypes*/
int getop(char[]);
void push(double);
double pop(void);

/*Program starts*/
/*Reverse polish calculator*/
int main(void)
{
	/*Variables*/
	int type;
	/*op1 added for 4-3 extension*/
	double op2, op1;
	char s[MAXOP];

	/*Get input untill user quits*/
	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			/*Operand*/
			case NUMBER:
				push(atof(s));
				break;
			/*Addition*/
			case '+':
				push(pop() + pop());
				break;
			/*Multiplication*/
			case '*':
				push(pop() * pop());
				break;
			/*Subtraction*/
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			/*Division*/
			case '/':
				op2 = pop();
				if(op2!=0)
					push(pop() / op2);
				else
					printf("error: division by zero\n");
				break;
			/*Ex 4-3 extension, upto END OF 4-3 EXTENSION*/
			/*Modulus division*/
			case '%':
				op2 = pop();
				op1 = pop();
				if(op2!=0)
						/*Not a good way to check if the number is int*/
						/*However used - to move on for now*/
						if(op1==(int)op1 && op2==(int)op2)
							push((int) op1 % (int) op2);
						else
							printf("error: %% has non integer operand\n");
				else
					printf("error: modulus division by zero\n");
				break;
			/*END OF 4-3 EXTENSION*/
			/*Print result*/
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			/*Unknown operator*/
			default:
				printf("error: unknown command: %s\n", s);
				break;
		}
	}
	/*Program ends*/
	return 0;
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
	if(!isdigit(c) && c!='.' && c!='-')
		return c;

	/*ex 4-3 extension, upto END OF EX 4-3 EXTENSION*/
	/*Check if a negative number starts*/
	if(c=='-')
		if(!isdigit(c=getch()) && c!='.')
		{
			ungetch(c);
			return '-';
		}
		else
		{
			/*If a negative number, store the sign*/
			s[0] = '-';
			ungetch(c);
		}
	/*END OF EX 4-3 EXTENSION*/

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
