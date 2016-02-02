/*Ex 4-5, K&R 2nd*/
/*C program to implement a reverse polish calculator*/
/*Calculator is extended to support access*/
/*+to library functions like sin, exp, pow*/
/*___: 2016-01-28 Thu 02:43 PM*/
/*__________________________________________________*/

/*Header files*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*Constants*/
/*Max size of operand or operator*/
#define MAXOP 100
/*Signal that number was found*/
#define NUMBER '\0'
/*Signal that library math function found*/
#define MATH 1

/*Function protoypes*/
int getop(char[]);
void push(double);
double pop(void);
void stackop(int command);
void lmath(const char s[]);

/*Program starts*/
/*Reverse polish calculator*/
int main(void)
{
	/*Variables*/
	int type;
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
			/*Stack operation commands*/
			case 'p':
			case 'd':
			case 's':
			case 'c':
				stackop(type);
				break;
			/*Math library commands*/
			case MATH:
				lmath(s);
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
	int i, c, d;
	while((s[0]=c=getch()) == ' ' || c == '\t')
		;
	s[1]='\0';

	/*Return if a primitive operator found*/
	if(c=='+' || c=='*' || c=='/' || c=='%')
		return c;

	/*Return if - operator found*/
	/*Also check the special case of negative number*/
	else if(c=='-')
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

	/*Return if stack operation command found*/
	else if(c=='p' || c=='d' || c=='s' || c=='c')
	{
		if(isblank(d=getch()) || d=='\n')
		{
			ungetch(d);
			return c;
		}
		else
		{
			ungetch(d);
			/*ungetch(c);*/
		}
	}

	/*Prepare to store the number or a library math command*/
	i=0;

	/*If a number*/
	if(isdigit(c) || c=='.')
	{
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
	/*If a char, treat the string as library math function*/
	else if(isalpha(c))
	{
		while(!isblank(s[++i] = c = getch()) && c!='\n' && c!=EOF)
			;
		s[i]='\0';
		if(c != EOF)
			ungetch(c);
		return MATH;
	}
	/*If not primitive math operator*/
	/*If not start of a string starting with alpha*/
	/*If not a number*/
	else
		return c;
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

/*stackop() function definition*/
void stackop(int command)
{
	/*Automatic variables*/
	double dupl, temp;
	
	/*Check the command*/
	/*Different cases for different commands*/
	switch(command)
	{
		/*Print top of the stack*/
		case 'p':
			if(sp>0)
				printf("Top of stack: %.8g\n", val[sp-1]);
			else
				printf("error: stack empty\n");
			break;
		/*Duplicate top of the stack*/
		case 'd':
			if(sp>0)
			{
				dupl = val[sp-1];
				push(dupl);
			}
			else
				printf("error: stack empty\n");
			break;
		/*Swap top two elements of stack*/
		case 's':
			if(sp>1)
			{
				temp = val[sp-1];
				val[sp-1] = val[sp-2];
				val[sp-2] = temp;
			}
			else
				printf("error: not enough element to swap\n");
			break;
		/*Clear the stack*/
		case 'c':
			sp = 0;
			break;
		/*Negative case*/
		/*If this prints then there is some bug(s)*/
		default:
			printf("error: unknow stack command %c\n", command);
	}
}
/*lmath() function definition*/
void lmath(const char s[])
{
	/*Automatic variables*/
	double op2;

	/*Differnt math functions from <math.h>*/
	/*Note: strcmp() is not used as it is not introduced*/
	/*      +in K&R upto this point*/

	/*sin*/
	if(s[0]=='s' && s[1]=='i' && s[2]=='n' && s[3]=='\0')
		push(sin(pop()));
	/*cos*/
	else if(s[0]=='c' && s[1]=='o' && s[2]=='s' && s[3]=='\0')
		push(cos(pop()));
	/*tan*/
	else if(s[0]=='t' && s[1]=='a' && s[2]=='n' && s[3]=='\0')
		push(tan(pop()));
	/*asin*/
	else if(s[0]=='a' && s[1]=='s' && s[2]=='i' && s[3]=='n' && s[4]=='\0')
		push(asin(pop()));
	/*acos*/
	else if(s[0]=='a' && s[1]=='c' && s[2]=='o' && s[3]=='s' && s[4]=='\0')
		push(acos(pop()));
	/*atan*/
	else if(s[0]=='a' && s[1]=='t' && s[2]=='a' && s[3]=='n' && s[4]=='\0')
		push(atan(pop()));
	/*atan2*/
	else if(s[0]=='a' && s[1]=='t' && s[2]=='a' && s[3]=='n' && s[4]=='2' &&
	        s[5]=='\0')
	{
		op2=pop();
		push(atan2(pop(),op2));
	}
	/*sinh*/
	if(s[0]=='s' && s[1]=='i' && s[2]=='n' && s[3]=='h' && s[4]=='\0')
		push(sinh(pop()));
	/*cosh*/
	else if(s[0]=='c' && s[1]=='o' && s[2]=='s' && s[3]=='h' && s[4]=='\0')
		push(cosh(pop()));
	/*tanh*/
	else if(s[0]=='t' && s[1]=='a' && s[2]=='n' && s[3]=='h' && s[4]=='\0')
		push(tanh(pop()));
	/*exp*/
	if(s[0]=='e' && s[1]=='x' && s[2]=='p' && s[3]=='\0')
		push(exp(pop()));
	/*log*/
	else if(s[0]=='l' && s[1]=='o' && s[2]=='g' && s[3]=='\0')
		push(log(pop()));
	/*log10*/
	else if(s[0]=='l' && s[1]=='o' && s[2]=='g' && s[3]=='1' && s[4]=='0' &&
	        s[5]=='\0')
		push(log10(pop()));
	/*pow*/
	else if(s[0]=='p' && s[1]=='o' && s[2]=='w' && s[3]=='\0')
	{
		op2=pop();
		push(pow(pop(),op2));
	}
	/*sqrt*/
	else if(s[0]=='s' && s[1]=='q' && s[2]=='t' && s[3]=='t' && s[4]=='\0')
		push(sqrt(pop()));
	/*ceil*/
	else if(s[0]=='c' && s[1]=='e' && s[2]=='i' && s[3]=='l' && s[4]=='\0')
		push(ceil(pop()));
	/*floor*/
	else if(s[0]=='f' && s[1]=='l' && s[2]=='o' && s[3]=='o' && s[4]=='r' &&
	        s[5]=='\0')
		push(floor(pop()));
	/*fabs*/
	else if(s[0]=='f' && s[1]=='a' && s[2]=='b' && s[3]=='s' && s[4]=='\0')
		push(fabs(pop()));
	/*ldexp*/
	else if(s[0]=='l' && s[1]=='d' && s[2]=='e' && s[3]=='x' && s[4]=='p' &&
	        s[5]=='\0')
	{
		op2=pop();
		push(ldexp(pop(), op2));
	}
	/*frexp*/
	else if(s[0]=='f' && s[1]=='r' && s[2]=='e' && s[3]=='x' && s[4]=='p' &&
		    s[5]=='\0')
		/*To be implemented: Issue because a pointer is needed by frexp*/
		;
	/*modf*/
	else if(s[0]=='m' && s[1]=='o' && s[2]=='d' && s[3]=='f' && s[4]=='\0')
		/*To be implemented: Issue because a pointer is needed by frexp*/
		;
	/*fmod*/
	else if(s[0]=='f' && s[1]=='m' && s[2]=='o' && s[3]=='d' && s[4]=='\0')
	{
		op2=pop();
		push(fmod(pop(), op2));
	}
}

/*___*/
/*EOF*/
