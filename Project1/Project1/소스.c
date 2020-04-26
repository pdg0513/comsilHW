#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;
char expr[1111];
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

precedence getToken(char* symbol, int* n);
void postfix(void);
void printToken(precedence gtoken, char*, int);
precedence pop(precedence* stack, int* top);
void push(precedence token, precedence* stack, int* top);

int main()
{
	scanf("%s", expr);
	postfix();
	printf("%s\n", expr);
	return 0;
}


void postfix()
{
	precedence token;
	char symbol;
	precedence stack[100];
	char str[1111];
	int strn = 0;
	int tokenn = 0;
	int top = 0;
	stack[0] = eos;
	while (1)
	{
		token = getToken(&symbol, &tokenn);
		if (token == eos) break;

		if (token == operand)
		{
			str[strn] = symbol;
			strn++;
		}
		else if (token == rparen)
		{
			while (stack[top] != lparen)
			{
				printToken(pop(stack, &top), str, strn);
				strn++;
			}
			pop(stack, &top);
		}
		else
		{
			while (isp[stack[top]] >= icp[token])
			{
				printToken(pop(stack, &top), str, strn);
				strn++;
			}
			push(token, stack, &top);
		}
	}

	while (1)
	{
		token = pop(stack, &top);
		printToken(token, str, strn);
		strn++;
		if (token == eos) break;
	}

	strcpy(expr, str);


}

precedence pop(precedence* stack, int* top)
{
	if ((*top) == -1)
	{
		printf("stack is empty!");
	}
	return stack[(*top)--];
}

void push(precedence token, precedence* stack, int* top)
{
	*top = *top + 1;
	stack[*top] = token;
}

void printToken(precedence gtoken, char* str, int strn)
{
	switch (gtoken)
	{
	case rparen: str[strn] = ')'; break;
	case plus: str[strn] = '+'; break;
	case minus: str[strn] = '-'; break;
	case divide: str[strn] = '/'; break;
	case times: str[strn] = '*'; break;
	case mod: str[strn] = '%'; break;
	case eos: str[strn] = '\0'; break;
	default: return;
	}
}

precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}
