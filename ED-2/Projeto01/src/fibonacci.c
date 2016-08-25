#include <stdio.h>
#include <stdlib.h>

int fib(int val)
{
	if(0 == val || 1 == val)
	{
		return val;
	}
	else
	{
		return fib(val - 1) + fib(val - 2);
	}
}

int main2(void)
{
	setbuf(stdout, NULL);
	int val = 0;
	printf("informe o valor para ser calculado o Fibonacci: ");
	fflush(stdin);
	scanf("%d", &val);

	printf("%d", fib(val));
	return 0;
}
