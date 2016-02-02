/*****************************************************
			
*****************************************************/
/*Ex 4-10, K&R 2nd, :___:  2016-01-29 Fri 11:55 PM*/
/*C program to implement a reverse polish calculator*/
/*Extensions in this Excercise:
  1. Uses getline() to get the line, so getch()
     and ungetch() are not required
*/
/*___________________________________________________*/

/*Header files*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*Constants*/
/*Max size of operand or operator*/
#define MAXOP 100
/*Signal that number was found*/
#define NUMBER 500
/*Signal that library math function found*/
#define MATH 200
/*Signal that VARIABLE found*/
#define VARIABLE 300
/*Signal that variable assignment performed*/
#define YES_ASSIGN 301
/*Signal that variable assignment NOT performed*/
#define NO_ASSIGN 302
/*Signal that error occured*/
#define ERROR 401
/*Signal that NO error occured*/
#define NO_ERROR 402
/*For using getline()*/
#define NEWLINE 600
/*For printing decision*/
#define NO_PRINT 701
#define YES_PRINT 701
/*For debugging*/
#define SKIP

/*Function protoypes*/
int getop(char[], char *);
void push(double);
double pop(void);
void stackop(int command);
void lmath(const char s[]);
int varop(const char s[]);

/*External variables*/
/*Variable that holds 
  recently printed value
*/
double recent_print=0.0;
/*Variable to indicate if any
  error occured
*/
int error=NO_ERROR;

/*Program starts*/
/*Reverse polish calculator*/
int main(void)
{
	/*Automatic Variables*/
	int type;
	double op2, op1;
	char s[MAXOP];
	/*This variable indicates if the recent variable
	  operation was a variable assignment or not:
	  NO_ASSIGN -> normal variable operation
	  YES_ASSIGN -> variable assignment operation
	*/
	int varopType=NO_ASSIGN;
	/*This variable indicates if printing has to 
	  be done or not:
	  NO_PRINT -> Printing NOT needed
	  YES_PRINT -> Printing IS needed
	*/
	int doprint=YES_PRINT;
	/*Holds the result*/
	double result;
	/*Pointer to the input line*/
	char *line=NULL;
	/*Holds length of the input line*/
	int linelen;
	/*For getline() syntax*/
	size_t len;
	/****Line position counter*/
	int pos;

	/*Get lines until user quits*/
	while((linelen=getline(&line, &len, stdin)) > 0)
	{
		/*Process the line*/
		while((type = getop(s, line)) != NEWLINE)
		{
			switch(type)
			{
				/*Operand*/
				case NUMBER:
					push(atof(s));
					break;

					/*Addition*/
				case '+':
					/*printf("Add\n");*/
					push(pop() + pop());
					break;

					/*Multiplication*/
				case '*':
					/*printf("mult\n");*/
					push(pop() * pop());
					break;

					/*Subtraction*/
				case '-':
					/*printf("sub\n");*/
					op2 = pop();
					push(pop() - op2);
					break;

					/*Division*/
				case '/':
					op2 = pop();
					if(op2!=0)
						push(pop() / op2);
					else
					{
						printf("error: division by zero\n");
						error = ERROR;
					}
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
						{
							printf("error: %% has non integer operand\n");
							error = ERROR;
						}
					else
					{
						printf("error: modulus division by zero\n");
						error = ERROR;
					}
					break;

					/*Stack operation commands*/
				case '!':
				case '@':
				case '#':
				case '$':
					stackop(type);
					break;

					/*Math library commands*/
				case MATH:
					lmath(s);
					break;

					/*Variable command*/
				case VARIABLE:
					varopType=varop(s);
					break;

					/*Unknown operator*/
				default:
					printf("error: unknown command: %s\n", s);
					error = ERROR;
					break;
			}
		}
		/*Once the line has been completely processed*/
		/*Ideally should print the result now, however, double
		  check if it is appropriate to print the result
	    */
		if(type == NEWLINE)
		{
			if((error==NO_ERROR) && (varopType==NO_ASSIGN) )
			{
				result = pop();
				/*Additional check for scenarios where user 
				  just preses enter and there is nothing to pop
				 */
				if(error==NO_ERROR)
					printf("\t%.8g\n", recent_print = result);
			}
			/*Assume next line appripriate to print*/
			error=NO_ERROR;
			varopType=NO_ASSIGN;
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
/*This function pushes an element to the top of stack*/
void push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else
	{
		printf("error: stack full, can't push %g\n", f);
		error = ERROR;
	}
}

/*Dpop()*/
/*This function pops the top element from stack*/
double pop(void)
{
	if(sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		error = ERROR;
		return 0.0;
	}
}

/*Header files*/
#include<ctype.h>

/*Function prototypes*/
int getch(void);
void ungetch(int);
/*Added for Ex 4-7*/
void ungets(const char s[]);

/*External variables*/
int i=0;

/*Dgetop()*/
/*This function does this:
  1. If an operator found, return the operator
  2. Else if an operand found, store the operand in s[]
     and return appropriate value to indicate it
*/
int getop(char s[], char *line)
{
	/*Variables*/
	int j, k=0, c, d;

	/****Line counter '' is used now*/
	/*i=0;*/

	/*thi = is a1 2 3line -*/
	while((c=line[i]) == ' ' || c == '\t')
		++i;
	/*s[1]='\0';*/
		/*;*/
	/*--i;*/

	/*Return if a primitive operator found*/
	if(c=='+' || c=='*' || c=='/' || c=='%')
	{
		++i;
		return c;
	}

	/*Return if stack operation command found*/
	else if(c=='!' || c=='@' || c=='#' || c=='$')
	{
		if(isblank(line[i+1]) || line[i+1]=='\n')
		{
			/*ungetch(d);*/
			++i;
			return c;
		}
		else
			/*ungetch(d);*/
			;
	}

	/*If a number*/
	else if(isdigit(c) || c=='.' || c=='-')
	{
		/*Prepare to collect the number*/
		j=0;
		/*Find out minus operator or negative number*/
		if(c=='-')
		{
			/*minus*/
			if(!isdigit(c=line[i+1]) && c!='.')
			{
				++i;
				return '-';
			}
			/*negative number*/
			else
			{
				/*Store the sign*/
				s[0] = '-';
				++j;
				++i;
			}
		}
		/*Collect the number*/
		if(isdigit(c))
			/*Collect the integer part*/
			while(isdigit(s[j++] = c = line[i]))
				++i;
		if(c=='.')
		{
			++i;
			/*Collect the fraction part*/
			while(isdigit(s[j++] = c = line[i]))
				++i;
		}
		s[j]='\0';

		/****Why was this here before??*/
		/*if(c != EOF)*/

		/*Indicate a number in return*/
		return NUMBER;
	}

	/*If a char, look for var expression or a math function*/
	/*__________________why check for '\0'??*/
	else if((isalpha(c) && c!='\0') || c=='^')
	{
		/*Variable expression*/
		if(isblank(c=line[i+1]) || c=='=' || c=='\n')
		{
			/*Prepare to store the variable expression*/
			j=0;
			s[j++]=line[i++];

			/*Ignore blanks after variable name*/
			while(isblank(c=line[i]))
				i++;

			/*If assignment operator (possibly after some blanks) */
			if(c=='=')
			{
				s[j++]=c;
				++i;
			}

			/*If not assignment operator after the variable*/
			/*This is means variable is just used - nothing to do more - return*/
			else
			{
				s[j]='\0';
				return VARIABLE;
			}

			/*If an assignment operator, collect the RHS*/
			/*Ignore blanks*/
			while(isblank(c=line[i]))
				++i;

			/*Collect the RHS*/
			while(!isblank(c=line[i]) && c!='\n')
			{
				s[j++] = line[i];
				++i;
			}
			s[j]='\0';

			/*Indicate a vriable in return*/
			return VARIABLE;
		}

		/*If it was not a variable then treat it as a math library function*/
		/*Prepare to collect the library math function*/
		j=0;

		/*Collect the math operator, one char at a time*/
		while(!isblank(c = line[i]) && c!='\n' && c!=EOF)
		{
			s[j++] = line[i];
			++i;
		}
		s[j]='\0';

		/*___________________*/
		/*Why was this here??*/
		/*if(c != EOF)*/

		/*Indicate a library math function in return*/
		return MATH;
	}
	/*If a newline*/
	else if(c=='\n');
	{
		i=0;
		return NEWLINE;
	}
	/*If not primitive math operator*/
	/*If not a number*/
	/*If not start of a string: (var or math func)*/
	/*If not a newline*/
	/*else*/
		return c;
}

/*Constants*/
#define BUFSIZE 1

/*External variables*/
/*Buffer fot getch() and ungetch()*/
/*Ex 4-9 modifiction: Buffer modified to be an int type
  so that an EOF can be correctly stored in the buffer
*/
int buf[BUFSIZE];
/*Next free position in buffer*/
int bufp=0;

/*getch() function definition*/
/*This function gets a (possibly pushed back) character*/
/*Modified for Ex 4-9 - Now it cn handle pushed back EOF*/
int getch(void)
{
	return (bufp==1) ? buf[--bufp] : getchar();
}

/*ungetch() function definition*/
/*This function pushes character back on input*/
/*Modified for Ex 4-9 - Now it cn handle pushed back EOF*/
void ungetch(int c)
{
	if(bufp > 0)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/*Header files*/
#include<string.h>

/*ungets() function definition*/
/*This function will push back an 
  entire string onto input
*/
void ungets(const char s[])
{
	int i;
	/*Push the last element to buffer first
	  then continue untill first element
	*/
	i = strlen(s);
	--i;
	while(i>=0)
		ungetch(s[i--]);
}

/*Dstackop()*/
/*This function handles stack operation commands*/
void stackop(int command)
{
	/*Automatic variables*/
	double dupl, temp;
	
	/*Check the command*/
	/*Different cases for different commands*/
	switch(command)
	{
		/*Print top of the stack*/
		case '!':
			if(sp>0)
				printf("Top of stack: %.8g\n", val[sp-1]);
			else
			{
				printf("error: stack empty\n");
				error = ERROR;
			}
			break;
		/*Duplicate top of the stack*/
		case '@':
			if(sp>0)
			{
				dupl = val[sp-1];
				push(dupl);
			}
			else
			{
				printf("error: stack empty\n");
				error = ERROR;
			}
			break;
		/*Swap top two elements of stack*/
		case '#':
			if(sp>1)
			{
				temp = val[sp-1];
				val[sp-1] = val[sp-2];
				val[sp-2] = temp;
			}
			else
			{
				printf("error: not enough element to swap\n");
				error = ERROR;
			}
			break;
		/*Clear the stack*/
		case '$':
			sp = 0;
			break;
		/*Negative case*/
		/*If this prints then there is some bug(s)*/
		default:
			printf("error: unknow stack command %c\n", command);
			error = ERROR;
	}
}

/*lmath() function definition*/
/*This function handles math functions from library*/
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
	else if(s[0]=='s' && s[1]=='i' && s[2]=='n' && s[3]=='h' && s[4]=='\0')
		push(sinh(pop()));
	/*cosh*/
	else if(s[0]=='c' && s[1]=='o' && s[2]=='s' && s[3]=='h' && s[4]=='\0')
		push(cosh(pop()));
	/*tanh*/
	else if(s[0]=='t' && s[1]=='a' && s[2]=='n' && s[3]=='h' && s[4]=='\0')
		push(tanh(pop()));
	/*exp*/
	else if(s[0]=='e' && s[1]=='x' && s[2]=='p' && s[3]=='\0')
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
		/*To be implemented: Issue because a pointer is needed by modf*/
		;
	/*fmod*/
	else if(s[0]=='f' && s[1]=='m' && s[2]=='o' && s[3]=='d' && s[4]=='\0')
	{
		op2=pop();
		push(fmod(pop(), op2));
	}
	else
	{
		printf("error: unknown math command: %s\n", s);
		error = ERROR;
	}
}

/*External vriables*/
/*To support variables in the calculator*/
double v1=0,v2=0,v3=0,v4=0,v5=0,v6=0,v7=0,v8=0,v9=0,v10=0,v11=0,v12=0,v13=0,
	   v14=0,v15=0,v16=0,v17=0,v18=0,v19=0,v20=0,v21=0,v22=0,v23=0,v24=0,v25=0,v26=0;

/*Function prototypes*/
double rhsvar(const char s[]);

/*varop() function definition*/
/*This funciton deals with the variables*/
/*Both variable assignmentn and variable use*/
/*Returns YES_ASSIGN if assignment was done*/
/*Returns NO_ASSIGN if NO assignment was done*/
int varop(const char s[])
{
	/*Automatic variables*/
	int opType;

	/*If not a variable assignment*/
	/*This means the variable is used in some-*/
	/*+expression like 10 v + w -*/
	/*_______________________________________________*/
	/***STRANGE** isalpha(s[0]) is true when s[0]='^'*/
	if((isalpha(s[0]) || s[0]=='^') && s[1]=='\0')
	{
		switch(s[0])
		{
			case 'a':
				push(v1);
				break;
			case 'b':
				push(v2);
				break;
			case 'c':
				push(v3);
				break;
			case 'd':
				push(v4);
				break;
			case 'e':
				push(v5);
				break;
			case 'f':
				push(v6);
				break;
			case 'g':
				push(v7);
				break;
			case 'h':
				push(v8);
				break;
			case 'i':
				push(v9);
				break;
			case 'j':
				push(v10);
				break;
			case 'k':
				push(v11);
				break;
			case 'l':
				push(v12);
				break;
			case 'm':
				push(v13);
				break;
			case 'n':
				push(v14);
				break;
			case 'o':
				push(v15);
				break;
			case 'p':
				push(v16);
				break;
			case 'q':
				push(v17);
				break;
			case 'r':
				push(v18);
				break;
			case 's':
				push(v19);
				break;
			case 't':
				push(v20);
				break;
			case 'u':
				push(v21);
				break;
			case 'v':
				push(v22);
				break;
			case 'w':
				push(v23);
				break;
			case 'x':
				push(v24);
				break;
			case 'y':
				push(v25);
				break;
			case 'z':
				push(v26);
				break;
			/*Recently printed value*/
			case '^':
				push(recent_print);
				break;
			default:
				printf("error: unknown variable: %s\n", s);
				error = ERROR;
				break;
		}
		opType = NO_ASSIGN;
	}

	/*Else if variable is used for assigment such as:
	  a=b
	*/
	else
	{
		/*Assign to appropriate variable*/
		switch(s[0])
		{
			case 'a':
				v1 = rhsvar(s);
				break;
			case 'b':
				v2 = rhsvar(s);
				break;
			case 'c':
				v3 = rhsvar(s);
				break;
			case 'd':
				v4 = rhsvar(s);
				break;
			case 'e':
				v5 = rhsvar(s);
				break;
			case 'f':
				v6 = rhsvar(s);
				break;
			case 'g':
				v7 = rhsvar(s);
				break;
			case 'h':
				v8 = rhsvar(s);
				break;
			case 'i':
				v9 = rhsvar(s);
				break;
			case 'j':
				v10 = rhsvar(s);
				break;
			case 'k':
				v11 = rhsvar(s);
				break;
			case 'l':
				v12 = rhsvar(s);
				break;
			case 'm':
				v13 = rhsvar(s);
				break;
			case 'n':
				v14 = rhsvar(s);
				break;
			case 'o':
				v15 = rhsvar(s);
				break;
			case 'p':
				v16 = rhsvar(s);
				break;
			case 'q':
				v17 = rhsvar(s);
				break;
			case 'r':
				v18 = rhsvar(s);
				break;
			case 's':
				v19 = rhsvar(s);
				break;
			case 't':
				v20 = rhsvar(s);
				break;
			case 'u':
				v21 = rhsvar(s);
				break;
			case 'v':
				v22 = rhsvar(s);
				break;
			case 'w':
				v23 = rhsvar(s);
				break;
			case 'x':
				v24 = rhsvar(s);
				break;
			case 'y':
				v25 = rhsvar(s);
				break;
			case 'z':
				v26 = rhsvar(s);
				break;
			default:
				printf("error: unknown variable used: %s\n",s);
				error = ERROR;
				break;
		}
		opType = YES_ASSIGN;
	}
	return opType;
}

/*rhsvar() function definition*/
/*This function returns the value of RHS*/
double rhsvar(const char s[])
{
	/*Automatic variables*/
	int i, j, c;
	char tempstr[MAXOP];
	
	/*Skip the LHS and '='*/
	i=0;
	while((c=s[i++]) != '=' && c != '\0')
		;

	/*Skip the blanks after '=' and before RHS*/
	while(isblank(s[i++]))
		;

	/*Positon i to first char of RHS*/
	--i;

	/*If RHS is a number*/
	/*Caveat: A standalone blank ('.' or '-.') 
	  is treated as '0.0'
	*/
	if(isdigit(s[i]) || s[i]=='-' || s[i]=='.')
	{
		/*Get the number in a temporary string*/
		for(j=0; s[i] != '\0'; ++i, ++j)
			tempstr[j] = s[i];
		tempstr[j] = '\0';

		/*Return the number*/
		return atof(tempstr);
	}

	/*Else if RHS is NOT a number,
	  treat it as a variable
	*/
	else
	{
		/*Get the variable in a temporary string*/
		for(j=0; s[i] != '\0'; ++i, ++j)
			tempstr[j] = s[i];
		tempstr[j] = '\0';

		/*If the RHS is not a single-*/
		/*+character variable*/
		if(strlen(tempstr) != 1)
		{
			printf("error: unknown variable %s\n", tempstr);
			error = ERROR;
			/*Caveat: If an error occurs while variable 
			          assignemt, then the variable will 
					  be assigned 0.0
		    */
			return 0.0;
		}

		/*If RHS a single character variable*/
		else
		{
			switch(tempstr[0])
			{
				case 'a':
					return v1;
					break;
				case 'b':
					return v2;
					break;
				case 'c':
					return v3;
					break;
				case 'd':
					return v4;
					break;
				case 'e':
					return v5;
					break;
				case 'f':
					return v6;
					break;
				case 'g':
					return v7;
					break;
				case 'h':
					return v8;
					break;
				case 'i':
					return v9;
					break;
				case 'j':
					return v10;
					break;
				case 'k':
					return v11;
					break;
				case 'l':
					return v12;
					break;
				case 'm':
					return v13;
					break;
				case 'n':
					return v14;
					break;
				case 'o':
					return v15;
					break;
				case 'p':
					return v16;
					break;
				case 'q':
					return v17;
					break;
				case 'r':
					return v18;
					break;
				case 's':
					return v19;
					break;
				case 't':
					return v20;
					break;
				case 'u':
					return v21;
					break;
				case 'v':
					return v22;
					break;
				case 'w':
					return v23;
					break;
				case 'x':
					return v24;
					break;
				case 'y':
					return v25;
					break;
				case 'z':
					return v26;
					break;
				/*Recently printed value*/
				case '^':
					return recent_print;
					break;
				default:
					printf("error: unknown variable: %s\n", s);
					error = ERROR;
					/*Caveat: If an error occurs while variable 
							  assignemt, then the variable will 
							  be assigned 0.0
					*/
					return 0.0;
					break;
			}
		}
	}
}

/*___*/
/*EOF*/
