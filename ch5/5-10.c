/* K&R2 5-10 */

/*Header files*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Constants*/
/*Max size of operand or operator*/
#define MAXOP 100
/*Signal that number was found*/
#define NUMBER '\0'

/*Function protoypes*/
int getop(char[]);
void push(double);
double pop(void);
void stackop(int command);
int readclarg(char arg[], char s[]);

/*Constants*/
/*Max num of operands in stack*/
#define MAXVAL 100

/*External variables*/
/*Stack to store operands*/
double val[MAXVAL];
/*Stack pointer*/
int sp=0;

/*Program starts*/
/*Reverse polish calculator*/
int main(int argc, char *argv[])
{
	/*Variables*/
	int i, type;
	double op2, op1;
	char s[MAXOP];

	/* For all the command line args */
	for (i=1; i <= argc; ++i)
	{
		switch (type = readclarg(argv[i], s))
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

/* 5-10-> readclarg(): read the input for calc */
int readclarg(char arg[], char s[])
{
	int c;

	if (arg == NULL)
		return '\n';
	if (strlen(arg) == 1)
		if ((c = arg[0]) == '+' || c == '-' || c == '*' || c == '/')
			return c;
	strncpy(s, arg, strlen(arg) + 1);
	return NUMBER;
}

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

/* EOF */
