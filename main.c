
// Simple implementation of the shunting-yard algorithm, for converting infix expressions to RPN.

#include <stdio.h>

int main()
{
	char* I = "(A+B)+C*(D-E)";
	
	int O[512]; // Holds variable conversion stuff
	int O_i = -1;
	
	int S[512]; // Holds operator stuff
	int S_i = -1;
	
	int prec[3]= {1, 1, 2};
	int asso[3] = {0, 0, 0};
	
	int i = 0;
	for (i = 0; I[i]; i++)
	{
		char T = I[i]; // token
		
		if (T > 0x40 && T < 0x133) // If is a letter...
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
	
	for (i = 0; i <= O_i; i++)
		printf("%c", O[i]);
	printf("\n");
	
	
	return 0;
}