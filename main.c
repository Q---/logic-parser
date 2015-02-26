#include <stdio.h>

void infixToRPN(char*, unsigned int*);

float evalRPN(char*, float*);

int main()
{
	char code[1024] = "C*(B+C)"; // Holds variable conversion stuff
	float parameters[512] = {1.0, 2.0, 3.0, 2.0, 5.1};
	unsigned int length = 0;
	
	infixToRPN(code, &length);

	float ANS = evalRPN(code, parameters);
	
	int i;
	for (i = 0; i < length; i++)
		printf("%c", code[i]);
	printf("\n");
	
	
	printf("%f\n",ANS);
	
	
	return 0;
}


// Simple implementation of the shunting-yard algorithm, for converting infix expressions to RPN.
// Converts expression in-place.

void infixToRPN(char* O, unsigned int* len)
{
	int O_i = -1;
	
	int S[1024]; // Holds operator stuff
	int S_i = -1;
	
	int prec[3]= {1, 1, 2};
	int asso[3] = {0, 0, 0};
	
	int i = 0;
	for (i = 0; O[i]; i++)
	{
		char T = O[i]; // token
		
		if (T >= 'A' && T <= 'Z' ) // If is a letter...
		{
			O[++O_i] = T; // Add to queue
		}
		else
		{
			int Ti;
			switch (T)
			{
				case '+':
					Ti = 0;
					break;
				case '-':
					Ti = 1;
					break;
				case '*':
					Ti = 2;
					break;
				case '(':
					Ti = 3;
					break;
				case ')':
					Ti = 4;
					break;
			}
			
			if (Ti <= 2) // If is operator
			{
				while ( S_i > -1 && S[S_i] < 3 && ( (asso[S[S_i]] && prec[Ti] < prec[S[S_i]])  || (!asso[S[S_i]] && prec[Ti] <= prec[S[S_i]]) ) )
				{
					O[++O_i] = S[S_i--]; // Pop operator stack onto queue (mage-class idiom)
				}
				S[++S_i] = T; // Add to stack
			}
			else if (Ti == 3) // If is left parenthesis
			{
				S[++S_i] = Ti;
			}
			else if (Ti == 4) // It is right parenthesis
			{
				while (S[S_i] != 3 && S_i > -1)
				{
					O[++O_i] = S[S_i--];
				}
				if (S[S_i] == 3)
					S_i--;
				else
					; // MISSING LEFT PARENTHESIS
			}
		}
	}
	while (S_i > -1)
	{
		if (S[S_i] >= 3)
			; // MISSING RIGHT PARENTHESIS
		O[++O_i] = S[S_i--];
	}
	
	O[++O_i] = '\0'; // Cap it off with a null
	*len = O_i;
	
	return;
}

// Simple RPN expression evaluator, based on a stack machine.

float evalRPN(char* code, float* parameters)
{
	float S[1024];
	int S_i = -1;
	
	int i;
	int T;
	for (i = 0; i < code[i]; i++)
	{
		T = code[i];
		if (T >= 'A' && T <= 'Z')
		{
			S[++S_i] = parameters[T - 'A'];
		}
		else
		{
			switch (T)
			{
				case '+':
					S_i--;
					S[S_i] = S[S_i] + S[S_i+1];
					break;
				case '-':
					S_i--;
					S[S_i] = S[S_i] - S[S_i+1];
					break;
				case '*':
					S_i--;
					S[S_i] = S[S_i] * S[S_i+1];
					break;
			}
		}
	}
	
	return S[0];
}


